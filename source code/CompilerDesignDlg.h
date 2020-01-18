// CompilerDesignDlg.h : header file
//

#if !defined(AFX_COMPILERDESIGNDLG_H__CC27D5AE_9F1A_4A69_BC91_854AE52BB760__INCLUDED_)
#define AFX_COMPILERDESIGNDLG_H__CC27D5AE_9F1A_4A69_BC91_854AE52BB760__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dlg1.h"
#include "Dlg2.h"
#include "Dlg3.h"
#include "Dlg4.h"

/////////////////////////////////////////////////////////////////////////////
// CCompilerDesignDlg dialog

class CCompilerDesignDlg : public CDialog
{
// Construction
public:
	CCompilerDesignDlg(CWnd* pParent = NULL);	// standard constructor
	CDlg1 page1;
	CDlg2 page2;
	CDlg3 page3;
	CDlg4 page4;
// Dialog Data
	//{{AFX_DATA(CCompilerDesignDlg)
	enum { IDD = IDD_COMPILERDESIGN_DIALOG };
	CTabCtrl	m_tabCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompilerDesignDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCompilerDesignDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPILERDESIGNDLG_H__CC27D5AE_9F1A_4A69_BC91_854AE52BB760__INCLUDED_)
