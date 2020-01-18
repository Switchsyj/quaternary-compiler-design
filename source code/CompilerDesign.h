// CompilerDesign.h : main header file for the COMPILERDESIGN application
//

#if !defined(AFX_COMPILERDESIGN_H__6E3E6C07_5313_4DDA_AC11_912DAE30584B__INCLUDED_)
#define AFX_COMPILERDESIGN_H__6E3E6C07_5313_4DDA_AC11_912DAE30584B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCompilerDesignApp:
// See CompilerDesign.cpp for the implementation of this class
//

class CCompilerDesignApp : public CWinApp
{
public:
	CCompilerDesignApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompilerDesignApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCompilerDesignApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPILERDESIGN_H__6E3E6C07_5313_4DDA_AC11_912DAE30584B__INCLUDED_)
