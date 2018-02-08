// Process01Dlg.h : header file
//

#if !defined(AFX_PROCESS01DLG_H__9BA9F253_FCAE_4D12_B392_F62EEF4D5876__INCLUDED_)
#define AFX_PROCESS01DLG_H__9BA9F253_FCAE_4D12_B392_F62EEF4D5876__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProcess01Dlg dialog

#include <map>
#include "processInfo.h"
using namespace std;

class CProcess01Dlg : public CDialog
{
// Construction
public:
	CProcess01Dlg(CWnd* pParent = NULL);	// standard constructor
	
	enum ThreadWorkingType
	{
		THREAD_STOP = 0,
		THREAD_RUNNING = 1,
		THREAD_PAUSE = 2
	};
	ThreadWorkingType m_eThreadWork;
	
	//map<int, ProcessInfo> processMap;
	static UINT addItem(LPVOID pParam); //add item (listcontrol)

	// Dialog Data
	//{{AFX_DATA(CProcess01Dlg)
	enum { IDD = IDD_PROCESS01_DIALOG };
	CListCtrl	m_ctrlList;
	CString	m_debug;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcess01Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProcess01Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESS01DLG_H__9BA9F253_FCAE_4D12_B392_F62EEF4D5876__INCLUDED_)
