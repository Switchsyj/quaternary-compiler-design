// CompilerDesignDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CompilerDesign.h"
#include "CompilerDesignDlg.h"

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
// CCompilerDesignDlg dialog

CCompilerDesignDlg::CCompilerDesignDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompilerDesignDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompilerDesignDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCompilerDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompilerDesignDlg)
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCompilerDesignDlg, CDialog)
	//{{AFX_MSG_MAP(CCompilerDesignDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompilerDesignDlg message handlers

BOOL CCompilerDesignDlg::OnInitDialog()
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
	m_tabCtrl.InsertItem(0, "算术表达式");
	m_tabCtrl.InsertItem(1, "for语句");
	m_tabCtrl.InsertItem(2, "while语句");
	m_tabCtrl.InsertItem(3, "if-else复合语句");

	page1.Create(IDD_DIALOG1, &m_tabCtrl);
	page2.Create(IDD_DIALOG2, &m_tabCtrl);
	page3.Create(IDD_DIALOG3, &m_tabCtrl);
	page4.Create(IDD_DIALOG4, &m_tabCtrl);

	CRect rc;
	m_tabCtrl.GetClientRect(&rc);
	//调整子对话框在父窗口中的位置
	rc.top += 22;
	rc.bottom -= 3;
	rc.left += 2;
	rc.right -= 3;
	
	//设置子对话框尺寸并移动到指定位置
	page1.MoveWindow(&rc);
	page2.MoveWindow(&rc);
	page3.MoveWindow(&rc);
	page4.MoveWindow(&rc);

	page1.ShowWindow(true);
	page2.ShowWindow(false);
	page3.ShowWindow(false);
	page4.ShowWindow(false);

	m_tabCtrl.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCompilerDesignDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCompilerDesignDlg::OnPaint() 
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
HCURSOR CCompilerDesignDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCompilerDesignDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int CurSel = m_tabCtrl.GetCurSel();
	
	switch (CurSel)
	{
	case 0:
		page1.ShowWindow(true);
		page2.ShowWindow(false);
		page3.ShowWindow(false);
		page4.ShowWindow(false);
		break;
	case 1:
		page1.ShowWindow(false);
		page2.ShowWindow(true);
		page3.ShowWindow(false);
		page4.ShowWindow(false);
		break;
	case 2:
		page1.ShowWindow(false);
		page2.ShowWindow(false);
		page3.ShowWindow(true);
		page4.ShowWindow(false);
		break;
	case 3:
		page1.ShowWindow(false);
		page2.ShowWindow(false);
		page3.ShowWindow(false);
		page4.ShowWindow(true);
		break;
	}
	
	
	*pResult = 0;
}
