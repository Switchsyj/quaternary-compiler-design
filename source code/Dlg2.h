#if !defined(AFX_DLG2_H__CDBE7876_3CBA_4054_998E_CCDA3088DBB1__INCLUDED_)
#define AFX_DLG2_H__CDBE7876_3CBA_4054_998E_CCDA3088DBB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg2 dialog

class CDlg2 : public CDialog
{
// Construction
public:
	CDlg2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg2)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	void work();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg2)
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG2_H__CDBE7876_3CBA_4054_998E_CCDA3088DBB1__INCLUDED_)
