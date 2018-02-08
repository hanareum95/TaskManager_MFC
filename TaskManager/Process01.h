// Process01.h : main header file for the PROCESS01 application
//

#if !defined(AFX_PROCESS01_H__AA1937F0_3DD1_4B2C_8719_F3F90FA8DDD7__INCLUDED_)
#define AFX_PROCESS01_H__AA1937F0_3DD1_4B2C_8719_F3F90FA8DDD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProcess01App:
// See Process01.cpp for the implementation of this class
//

class CProcess01App : public CWinApp
{
public:
	CProcess01App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcess01App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProcess01App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESS01_H__AA1937F0_3DD1_4B2C_8719_F3F90FA8DDD7__INCLUDED_)
