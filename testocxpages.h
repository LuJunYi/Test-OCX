// TestocxPages.h : header file
//

#ifndef __TESTOCXPAGES_H__
#define __TESTOCXPAGES_H__

#include <iostream>
#include <fstream>
#include <string>
#include <list>

//{{AFX_INCLUDES()
#include "lsv2ctl3.h"
//}}AFX_INCLUDES

/////////////////////////////////////////////////////////////////////////////
// CTestConnection dialog

class CTestConnection : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestConnection)

// Construction
public:
	CTestConnection();
	~CTestConnection();

// Dialog Data
	//{{AFX_DATA(CTestConnection)
	enum { IDD = IDD_CONNECT };
	CButton	m_ConnectionControl;
	CButton	m_Connect;
	CLSV2ctl3	m_LSV2;
	CString	m_Address;
	CString	m_ProtocolFile;
	int		m_nLanguage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestConnection)
	public:
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
  CEdit *m_pEventList;

// Implementation
protected:
	void Connect(BOOL DoReconnect);

	virtual LRESULT OnDisconnect(WPARAM wparma, LPARAM lparam);  // User defined message
	// Generated message map functions
	//{{AFX_MSG(CTestConnection)
	afx_msg void OnConnect();
	afx_msg void OnConnectionLost();
	afx_msg void OnInfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnVersion();
	afx_msg void OnProperties();
	afx_msg void OnTransferCompleted(long TransferResult);
	afx_msg void OnMsgErrorReceived(long ErrorNumber);
	afx_msg void OnEventReceived(LPCTSTR EventString);
	afx_msg void OnPLCStatusReceived(long Status);
	afx_msg void OnPLCMsgReceived(LPCTSTR Message);
	afx_msg void OnTest();
	afx_msg void OnReconnect();
  DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CTestDnc dialog

class CTestDnc : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestDnc)

// Construction
public:
	CTestDnc();
	~CTestDnc();

// Dialog Data
	//{{AFX_DATA(CTestDnc)
	enum { IDD = IDD_DNC };
	CEdit	m_ConverterPath;
	CButton	m_Converter;
	CStatic	m_Status;
	CButton	m_Connect;
	CButton	m_Start;
	CString	m_FileName;
	int		m_Command;
	CString	m_Address;
	//}}AFX_DATA

public:
	void StartAgain();
	BOOL m_RepeatStart;
	CLSV2ctl3	*m_pLSV2;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestDnc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestDnc)
	afx_msg void OnPaint();
	afx_msg void OnStart();
	afx_msg void OnSelchangeCommand();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStatus();
	afx_msg void OnConverter();
	afx_msg void OnChangeConverterpath();
	afx_msg void OnAbort();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CTestEvents dialog

class CTestEvents : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestEvents)

// Construction
public:
	CTestEvents();
	~CTestEvents();

// Dialog Data
	//{{AFX_DATA(CTestEvents)
	enum { IDD = IDD_EVENTS };
	CEdit	m_Events;
	CComboBox	m_ClassCombo;
	int		m_Mode;
	int		m_Class;
	int		m_Sender;
	int		m_Priority;
	CString	m_TypeString;
	int		m_EventId;
	//}}AFX_DATA

public:
	CLSV2ctl3	*m_pLSV2;



// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestEvents)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestEvents)
	afx_msg void OnSelchangeClass();
	afx_msg void OnApplyFilter();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CTestTable dialog

class CTestTable : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestTable)

// Construction
public:
	CTestTable();
	~CTestTable();

// Dialog Data
	//{{AFX_DATA(CTestTable)
	enum { IDD = IDD_TABLE };
	CButton	m_First;
	CString	m_SQLString;
	CString	m_FileName;
	DWORD	m_StartLine;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestTable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


public:
	CLSV2ctl3	*m_pLSV2;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestTable)
	afx_msg void OnChangeFilename();
	afx_msg void OnChangeSQLstring();
	afx_msg void OnFirst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CTestMessage dialog

class CTestMessage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestMessage)

// Construction
public:
	CTestMessage();
	~CTestMessage();

// Dialog Data
	//{{AFX_DATA(CTestMessage)
	enum { IDD = IDD_MESSAGE };
	CString	m_ChatLine;
	UINT	m_ChatLeft;
	UINT	m_ChatTop;
	UINT	m_ChatColumns;
	UINT	m_ChatRows;
	int		m_ChatFont;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestMessage)
	afx_msg void OnChatAdd();
	afx_msg void OnChatClear();
	afx_msg void OnChatClose();
	afx_msg void OnChatOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CLSV2ctl3	*m_pLSV2;
};


/////////////////////////////////////////////////////////////////////////////
// CTestPlcCommunication dialog

class CTestPlcCommunication : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestPlcCommunication)

// Construction
public:
	CTestPlcCommunication();
	~CTestPlcCommunication();

// Dialog Data
	//{{AFX_DATA(CTestPlcCommunication)
	enum { IDD = IDD_PLC_COMMUNICATION };
	CEdit	m_Status;
	CButton	m_Transmit_String;
	CButton	m_Transmit_DWord;
	CEdit	m_PLC_DWord;
	CEdit	m_PLC_String;
	CEdit	m_Received_String;
	CEdit	m_Received_DWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestPlcCommunication)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestPlcCommunication)
	afx_msg void OnTransmit();
	afx_msg void OnClear();
	afx_msg void OnChangePlcString();
	afx_msg void OnTransmitString();
	afx_msg void OnChangePlcDword();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CLSV2ctl3* m_pLSV2;

	std::list<std::string> m_listOptiData;

private:
	std::string getCurTime();

private:
	UINT_PTR m_nRedID = 0;
	std::ofstream m_outFile;
};


/////////////////////////////////////////////////////////////////////////////
// CTestDncInfo dialog

class CTestDncInfo : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestDncInfo)

// Construction
public:
	CTestDncInfo();
	~CTestDncInfo();

// Dialog Data
	//{{AFX_DATA(CTestDncInfo)
	enum { IDD = IDD_DNCINFO };
	CButton	m_Start;
	CStatic	m_Status;
	int		m_Command;
	int		m_Parameter;
	//}}AFX_DATA

public:
	void StartAgain();
	BOOL m_RepeatStart;
	CLSV2ctl3	*m_pLSV2;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestDncInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_Cmd;
	// Generated message map functions
	//{{AFX_MSG(CTestDncInfo)
	afx_msg void OnPaint();
	afx_msg void OnStart();
	afx_msg void OnSelchangeCommand();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CTestDncInfo dialog

class CTestMachineConstants : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestMachineConstants)

// Construction
public:
	CTestMachineConstants();
	~CTestMachineConstants();

// Dialog Data
	//{{AFX_DATA(CTestMachineConstants)
	enum { IDD = IDD_MACHINE_CONSTANTS };
	CString	m_ConstantNames;
	CString	m_ConstantValues;
	int		m_nExecutionMode;
	//}}AFX_DATA

public:
	CLSV2ctl3	*m_pLSV2;



// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestMachineConstants)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestMachineConstants)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetConstant();
	afx_msg void OnGetConstant();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CTestFileTime dialog

class CTestFileTime : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestFileTime)

// Construction
public:
	CTestFileTime();
	~CTestFileTime();

// Dialog Data
	//{{AFX_DATA(CTestFileTime)
	enum { IDD = IDD_FILE_TIME };
	CString	m_FileName;
	CString	m_Time;
	int		m_CurrentTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestFileTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


public:
	CLSV2ctl3	*m_pLSV2;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestFileTime)
	afx_msg void OnSetTime();
	afx_msg void OnCurrentTime();
	afx_msg void OnSpecificTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CTestPreset dialog

class CTestPreset : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestPreset)

// Construction
public:
	CTestPreset();
	~CTestPreset();

// Dialog Data
	//{{AFX_DATA(CTestPreset)
	enum { IDD = IDD_PRESET };
	CButton	m_btnSetPreset;
	int		m_SetImmediate;
	CString	m_strMachineCoordinates;
	CString	m_strWorkpieceCoordinates;
	CString	m_strBaseRotation;
	long	m_TableEntry;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestPreset)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


public:
	void EnablePresetButton();
	CLSV2ctl3	*m_pLSV2;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestPreset)
	afx_msg void OnSetPreset();
	afx_msg void OnChangeMc();
	afx_msg void OnChangeWc();
	afx_msg void OnChangeTableEntry();
	afx_msg void OnImmediate2();
	afx_msg void OnImmediate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CTestFileTransfer dialog

class CTestFileTransfer : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestFileTransfer)

// Construction
public:
	CTestFileTransfer();
	~CTestFileTransfer();

// Dialog Data
	//{{AFX_DATA(CTestFileTransfer)
	enum { IDD = IDD_FILE_TRANSFER };
	CStatic	m_lblStatus;
	CString	m_strBinTypes;
	CString	m_strPCFileName;
	CString	m_strNCFileName;
	BOOL	m_bShowProgressDlg;
	BOOL	m_bBackgroundTransfer;
	int		m_nMode;
	BOOL	m_bOverwrite;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestFileTransfer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	CLSV2ctl3	*m_pLSV2;

  // Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestFileTransfer)
	afx_msg void OnTransmit();
	afx_msg void OnReceive();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CTestBackup dialog

class CTestBackup : public CPropertyPage
{
  DECLARE_DYNCREATE(CTestBackup)
    
    // Construction
public:
  CTestBackup();
  ~CTestBackup();
  
  // Dialog Data
  //{{AFX_DATA(CTestBackup)
	enum { IDD = IDD_BACKUP };
	CEdit	m_ScanFolder;
  CString	m_strLstFileName;
  CString	m_strBckFileName;
	BOOL	m_bShowProgressDlg;
	CString	m_strScanFolder;
	int		m_nScanMode;
	CString	m_strBckLstFileName;
	//}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CTestBackup)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

public:
  CLSV2ctl3	*m_pLSV2;

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CTestBackup)
  afx_msg void OnRestore();
	afx_msg void OnScan();
	afx_msg void OnBackup();
	afx_msg void OnScanMode();
	afx_msg void OnScanMode2();
	afx_msg void OnScanMode3();
	afx_msg void OnScanMode4();
	afx_msg void OnChangeBckfile();
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
    
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.





#endif // __TESTOCXPAGES_H__
