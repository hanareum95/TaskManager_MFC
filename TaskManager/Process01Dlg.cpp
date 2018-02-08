// Process01Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Process01.h"
#include "Process01Dlg.h"
 
#include <tlhelp32.h> //프로세스 정보

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
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
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcess01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcess01Dlg)
	DDX_Control(pDX, IDC_LIST2, m_ctrlList);
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
	m_ctrlList.InsertColumn(0, _T("Process name"), LVCFMT_CENTER, 120);
	m_ctrlList.InsertColumn(1, _T("PID"), LVCFMT_CENTER, 70);
	m_ctrlList.InsertColumn(2, _T("Parent PID"), LVCFMT_CENTER, 80);
	m_ctrlList.InsertColumn(3, _T("Threads"), LVCFMT_CENTER, 70);
	m_ctrlList.InsertColumn(4, _T("CPU"), LVCFMT_CENTER, 60);

	m_ctrlList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT); 

	//addItem();
	CWinThread *pThread = ::AfxBeginThread(addItem, this);
	pThread->ResumeThread();

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
	//Process info
	HANDLE hSnapshot;
	PROCESSENTRY32 processEntry;
	
	int nProcessNum = 0;

	hSnapshot =CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	CProcess01Dlg* ptr = (CProcess01Dlg*) pParam;
	
	if(Process32First(hSnapshot, &processEntry))
	{
		do
		{
		//Item add

			char c[10];
		
			//Process name
			ptr->m_ctrlList.InsertItem(nProcessNum, processEntry.szExeFile);

			//PID
			ptr->m_ctrlList.SetItemText(nProcessNum, 1, _T( itoa(processEntry.th32ProcessID,c,10)));

			//Parent PID
			ptr->m_ctrlList.SetItemText(nProcessNum, 2, _T( itoa(processEntry.th32ParentProcessID,c,10)));

			//Thread
			ptr->m_ctrlList.SetItemText(nProcessNum, 3, _T( itoa(processEntry.cntThreads,c,10)));

			//cntUsage
			ptr->m_ctrlList.SetItemText(nProcessNum, 4, _T( itoa(processEntry.cntUsage,c,10)));

			nProcessNum++;

			::Sleep(10);

		}while(Process32Next(hSnapshot, &processEntry));
	}

	return 0;
}