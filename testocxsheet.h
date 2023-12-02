// TestocxSheet.h : header file
//
// This class defines custom modal property sheet 
// CTestocxSheet
 
#ifndef __TESTOCXSHEET_H__
#define __TESTOCXSHEET_H__

#include "TestocxPages.h"

// We need to include this file so we can use CMap
   #include <afxtempl.h>


/////////////////////////////////////////////////////////////////////////////
// CTestocxSheet

class CTestocxSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CTestocxSheet)

// Construction
public:
	CTestocxSheet(CWnd* pParentWnd = NULL);

// Attributes
public:
	CTestConnection m_Page0;
	
  CTestDnc m_Page1;
	CTestEvents m_Page2;
	CTestTable m_Page3;
	CTestMessage m_Page4;
	CTestPlcCommunication m_Page5;
  CTestDncInfo m_Page6;
	CTestMachineConstants m_Page7;
	CTestFileTime m_Page8;
	CTestPreset m_Page9;
	CTestFileTransfer m_Page10;
  CTestBackup m_Page11;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestocxSheet)
	public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestocxSheet();

protected:
	HICON m_hIcon;


protected:
   // we save the current page in TCN_SELCHANGING
   int m_nLastActive;
   // list of indexes of disabled pages
   CMap <int, int&, int, int&> m_DisabledPages;
   void EnablePage (int nPage, BOOL bEnable = TRUE);

public:
 	 void EnablePages();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CTestocxSheet)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __TESTOCXSHEET1_H__
