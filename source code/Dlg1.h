#if !defined(AFX_DLG1_H__D47896D6_CE31_45DB_B3C6_A63FB49571F1__INCLUDED_)
#define AFX_DLG1_H__D47896D6_CE31_45DB_B3C6_A63FB49571F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg1.h : header file
//
#define MAX 100
/////////////////////////////////////////////////////////////////////////////
// CDlg1 dialog

class CDlg1 : public CDialog
{
	// Construction
public:
	CDlg1(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDlg1)
	enum { IDD = IDD_DIALOG1 };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	void scan(FILE *fin);
	void trans_simple();

	void first_rev(int i, int m);		//!
	void first_comp(int i, int m);		//<= < > >=
	void first_noe(int i, int m);		//== !=
	void first_logand(int i, int m);		//&&
	void first_logor(int i, int m);		//||

	void first_jj(int j, int m);
	void first_cc(int i, int m);
	void change(int e);
	void change_double(int e);
		
		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CDlg1)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlg1)
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG1_H__D47896D6_CE31_45DB_B3C6_A63FB49571F1__INCLUDED_)
