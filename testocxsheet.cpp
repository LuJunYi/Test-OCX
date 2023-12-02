// testocxsheet.cpp : implementation file of registered dialog
//

#include "stdafx.h"
#include "resource.h"
#include "TestocxSheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
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
// CTestocxSheet

IMPLEMENT_DYNAMIC(CTestocxSheet, CPropertySheet)

CTestocxSheet::CTestocxSheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	AddPage(&m_Page0);
	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);
  AddPage(&m_Page4);
  AddPage(&m_Page5);
  AddPage(&m_Page6);
  AddPage(&m_Page7);
  AddPage(&m_Page8);
  AddPage(&m_Page9);
  AddPage(&m_Page10);
  AddPage(&m_Page11);

  SetActivePage(0);

  // Reference to the LSV2 object
  m_Page1.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page2.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page3.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page4.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page5.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page6.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page7.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page8.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page9.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page10.m_pLSV2 = &m_Page0.m_LSV2;
  m_Page11.m_pLSV2 = &m_Page0.m_LSV2;


  m_psh.dwFlags |= PSH_NOAPPLYNOW;
  m_psh.dwFlags &= ~PSH_HASHELP;
  m_Page0.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page1.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page2.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page3.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page4.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page5.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page6.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page7.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page8.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page9.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page10.m_psp.dwFlags &= ~PSP_HASHELP;
  m_Page11.m_psp.dwFlags &= ~PSP_HASHELP;

  // reference to the event list
  m_Page0.m_pEventList = &m_Page2.m_Events;
}


CTestocxSheet::~CTestocxSheet()
{
}



BEGIN_MESSAGE_MAP(CTestocxSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CTestocxSheet)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTestocxSheet message handlers



BOOL CTestocxSheet::OnInitDialog() 
{
  GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
  GetDlgItem(IDOK)->EnableWindow(FALSE);
  GetDlgItem(IDCANCEL)->SetWindowText("&Exit");

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	m_hIcon = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
  SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

  // OnInitDialog() must be called before EnablePage()
  // or GetTabControl() will fail.
  BOOL bReturn = CPropertySheet::OnInitDialog();

  // disable pages as long as no connection is established
  EnablePage (1, FALSE);
  EnablePage (2, FALSE);
  EnablePage (3, FALSE);
  EnablePage (4, FALSE);
  EnablePage (5, FALSE);
  EnablePage (6, FALSE);
  EnablePage (7, FALSE);
  EnablePage (8, FALSE);
  EnablePage (9, FALSE);
  EnablePage (10, FALSE);
  EnablePage (11, FALSE);
  return bReturn;
}


void CTestocxSheet::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
  	CPropertySheet::OnSysCommand(nID, lParam);
}


void CTestocxSheet::EnablePage (int nPage, BOOL bEnable)
{
   // if we want to enable the page
   if (bEnable)
   {
       // remove the index from the map
       m_DisabledPages.RemoveKey (nPage);
       // take out " - Disabled" from tab label
       CTabCtrl* pTab = GetTabControl();
       ASSERT (pTab);
       TC_ITEM ti;
       char szText[100];
       ti.mask = TCIF_TEXT;
       ti.pszText = szText;
       ti.cchTextMax = 100;
       VERIFY (pTab->GetItem (nPage, &ti));
       char * pFound = strstr (szText, " - Disabled");
       if (pFound)
       {
           *pFound = '\0';
           VERIFY (pTab->SetItem (nPage, &ti));
       }
   }
   // if we want to disable it
   else
   {
       // add the index to the map
       m_DisabledPages.SetAt (nPage, nPage);
       // add " - Disabled" to tab label
       CTabCtrl* pTab = GetTabControl();
       ASSERT (pTab);
       TC_ITEM ti;
       char szText[100];
       ti.mask = TCIF_TEXT;
       ti.pszText = szText;
       ti.cchTextMax = 100;
       VERIFY (pTab->GetItem (nPage, &ti));
       strcat (szText, " - Disabled");
       VERIFY (pTab->SetItem (nPage, &ti));
   }
}


BOOL CTestocxSheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
   NMHDR* pnmh = (NMHDR*)lParam;
   // tab is about to change
   if (TCN_SELCHANGING == pnmh->code)
       // save the current page index
       m_nLastActive = GetActiveIndex ();
   // tab has been changed
   else if (TCN_SELCHANGE == pnmh->code)
   {
       // get the current page index
       int nCurrentPage = GetActiveIndex ();
       // if current page is in our map of disabled pages
       if (m_DisabledPages.Lookup (nCurrentPage, nCurrentPage))
       // activate the previous page
       PostMessage (PSM_SETCURSEL, m_nLastActive);
   }
   return CPropertySheet::OnNotify(wParam, lParam, pResult);
}


int CTestocxSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	EnableStackedTabs(FALSE);
	
	return 0;
}


BOOL CTestocxSheet::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
  {
    if (pMsg->wParam == 27)  // ESC
      return (TRUE);         // ignorieren
  }

	return CPropertySheet::PreTranslateMessage(pMsg);
}

void CTestocxSheet::EnablePages()
{
    EnablePage(1, TRUE);
    EnablePage(2, TRUE);
    EnablePage(3, TRUE);
    EnablePage(4, TRUE);
    EnablePage(5, TRUE);
    EnablePage(6, TRUE);
    EnablePage(7, TRUE);
    EnablePage(8, TRUE);
    EnablePage(9, TRUE);
    EnablePage(10, TRUE);
    EnablePage(11, TRUE);
}


BOOL CTestocxSheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == IDCANCEL)
  {
    if (m_Page0.m_LSV2.TestConnection(0))
    {
      // If there is currently a background transfer running
      if (m_Page0.m_LSV2.BreakTransfer())
      {
         MessageBox("Active background transfer stopped");
         return TRUE;
      }
      else
        m_Page0.m_LSV2.DisConnect();
    }

  }

	return CPropertySheet::OnCommand(wParam, lParam);
}
