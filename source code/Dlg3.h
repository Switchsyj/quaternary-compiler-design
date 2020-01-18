#if !defined(AFX_DLG3_H__412A587D_86D7_456F_BD54_C7BF45B71DCE__INCLUDED_)
#define AFX_DLG3_H__412A587D_86D7_456F_BD54_C7BF45B71DCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg3 dialog

class CDlg3 : public CDialog
{
// Construction
public:
	CDlg3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg3)
	enum { IDD = IDD_DIALOG3 };
	CListCtrl	m_list;
	//}}AFX_DATA

	void analyse_word();
	void produce_obj(char c[],int count);
	void LR();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg3)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG3_H__412A587D_86D7_456F_BD54_C7BF45B71DCE__INCLUDED_)
