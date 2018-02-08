// Process01Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Process01.h"
#include "Process01Dlg.h"
 
#include <tlhelp32.h> //프로세스 정보

#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

using namespace std;

#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcess01Dlg dialog

CProcess01Dlg::CProcess01Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcess01Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcess01Dlg)
	m_debug = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcess01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcess01Dlg)
	DDX_Control(pDX, IDC_LIST2, m_ctrlList);
	DDX_Text(pDX, IDC_EDIT1, m_debug);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProcess01Dlg, CDialog)
	//{{AFX_MSG_MAP(CProcess01Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcess01Dlg message handlers

BOOL CProcess01Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	//insert column
	m_ctrlList.InsertColumn(0, _T("PID"), LVCFMT_CENTER, 70);
	m_ctrlList.InsertColumn(1, _T("Process name"), LVCFMT_CENTER, 120);
	m_ctrlList.InsertColumn(2, _T("Parent PID"), LVCFMT_CENTER, 80);
	m_ctrlList.InsertColumn(3, _T("Threads"), LVCFMT_CENTER, 70);
	m_ctrlList.InsertColumn(4, _T("CPU"), LVCFMT_CENTER, 60);

	m_ctrlList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT); 

	//thread 
	CWinThread *pThread;
	m_eThreadWork = THREAD_RUNNING;
	pThread = AfxBeginThread(addItem, this);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CProcess01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProcess01Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProcess01Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

UINT CProcess01Dlg::addItem(LPVOID pParam)
{
	char c[10];
	map<int, ProcessInfo> processMap;
	CProcess01Dlg* ptr = (CProcess01Dlg*) pParam;
	
	while(ptr->m_eThreadWork == THREAD_RUNNING)
	{
		//ptr->m_ctrlList.DeleteAllItems();
		
		//Process info
		HANDLE hSnapshot;
		PROCESSENTRY32 processEntry;
		
		int nProcessNum = 0;
		CString str;
		

		hSnapshot =CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		processEntry.dwSize = sizeof(PROCESSENTRY32);
		
		//to use findItem()
		LVFINDINFO lv;
		lv.flags = LVFI_PARTIAL|LVFI_STRING;
		int nFindIndex = 0;
		
		if(Process32First(hSnapshot, &processEntry))
		{
			do
			{
				ProcessInfo info(processEntry.szExeFile,
					processEntry.th32ProcessID,
					processEntry.th32ParentProcessID,
					processEntry.cntThreads,
					processEntry.cntUsage);
								
				//list에 없음 -> insert
				if( processMap.find(info.GetPID()) == processMap.end() )
				{
					
					processMap.insert(pair<int, ProcessInfo>(processEntry.th32ProcessID, info));
					
					//Item add
					
					//PID
					ptr->m_ctrlList.InsertItem(nProcessNum, itoa(info.GetPID(),c,10));
					
					//Process name
					ptr->m_ctrlList.SetItemText(nProcessNum, 1, _T(info.GetPName().c_str()));
					
					//Parent PID
					ptr->m_ctrlList.SetItemText(nProcessNum, 2, _T( itoa(info.GetParentPID(),c,10)));
					
					//Thread
					ptr->m_ctrlList.SetItemText(nProcessNum, 3, _T( itoa(info.GetThreadNum(),c,10)));
					
					//cntUsage
					ptr->m_ctrlList.SetItemText(nProcessNum, 4, _T( itoa(info.GetCPU(),c,10)));
					
					nProcessNum++;			
					str.Format("%d",ptr->m_ctrlList.GetItemCount());
					ptr->GetDlgItem(IDC_EDIT1)->SetWindowText(str+"*");
				}
				//list에 있음 -> update
				else
				{
					processMap.insert(pair<int, ProcessInfo>(processEntry.th32ProcessID, info));
					
					str.Format("%d",ptr->m_ctrlList.GetItemCount());
					ptr->GetDlgItem(IDC_EDIT1)->SetWindowText(str);
				}
			}while(Process32Next(hSnapshot, &processEntry));
		}
		Sleep(3000);
	}
	
	return 0;
}

void CProcess01Dlg::OnContextMenu( CWnd *pWnd, CPoint point)
{
	CMenu popup;
	CMenu *MyMenu;
	CPoint pt;
	GetCursorPos(&pt);
	popup.LoadMenu(IDR_MENU1);
	MyMenu = popup.GetSubMenu(0);
	MyMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}
