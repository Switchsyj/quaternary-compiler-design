#if !defined(AFX_DLG4_H__3F9F7FD9_AF7D_4BC4_8E49_983CEF7F0618__INCLUDED_)
#define AFX_DLG4_H__3F9F7FD9_AF7D_4BC4_8E49_983CEF7F0618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg4.h : header file
//
#include <cstdio>
#include <string.h>
#include <cstring>
#include <string>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CDlg4 dialog

class CDlg4 : public CDialog
{
// Construction
public:
	CDlg4(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg4)
	enum { IDD = IDD_DIALOG4 };
	CListCtrl	m_list;
		// NOTE: the ClassWizard will add data members here
	void analyse_show();		//展示词法分析结果
	void stack_show();		//展示栈

	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg4)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg4)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG4_H__3F9F7FD9_AF7D_4BC4_8E49_983CEF7F0618__INCLUDED_)
