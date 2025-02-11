// TestocxPages.cpp : implementation file
//

#include "stdafx.h"
#include <afxdlgs.h>

#include "resource.h"
#include "TestocxPages.h"
#include "TestocxSheet.h"

//#include "HexToDec.h"

#define WM_DISCONNECT WM_USER+33

// #define SPECIALTEST


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTestConnection, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestDnc, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestEvents, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestTable, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestMessage, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestPlcCommunication, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestDncInfo, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestMachineConstants, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestFileTime, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestPreset, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestFileTransfer, CPropertyPage)
IMPLEMENT_DYNCREATE(CTestBackup, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CTestConnection property page

CTestConnection::CTestConnection() : CPropertyPage(CTestConnection::IDD)
{
	//{{AFX_DATA_INIT(CTestConnection)
	m_Address = _T("10.10.11.70");
	//m_Address = _T("localhost");
	m_ProtocolFile = _T("c:\\temp\\testocx.txt -v2");
	m_nLanguage = 0;
	//}}AFX_DATA_INIT


	m_psp.dwFlags &= ~PSH_HASHELP;
}

CTestConnection::~CTestConnection()
{
}

void CTestConnection::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestConnection)
	DDX_Control(pDX, IDC_CONNECTIONCONTROL, m_ConnectionControl);
	DDX_Control(pDX, IDC_CONNECT, m_Connect);
	DDX_Control(pDX, IDC_LSV2, m_LSV2);
	DDX_Text(pDX, IDC_ADDRESS, m_Address);
	DDX_Text(pDX, IDC_PROTOCOL_FILE, m_ProtocolFile);
	DDX_CBIndex(pDX, IDC_LANGUAGE, m_nLanguage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestConnection, CPropertyPage)
	ON_MESSAGE(WM_DISCONNECT, OnDisconnect)
	//{{AFX_MSG_MAP(CTestConnection)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	ON_BN_CLICKED(IDC_VERSION, OnVersion)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_RECONNECT, OnReconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// CTestConnection message handlers

LRESULT CTestConnection::OnDisconnect(WPARAM wparma, LPARAM lparam)
{
	BOOL ok;

	if (!m_LSV2.TestConnection(4))
		m_LSV2.SetCaption("Cleaning up closed connection...");
	else
		m_LSV2.SetCaption("Disconnecting...");

	ok = m_LSV2.DisConnect();
	if (ok)
	{
		m_Connect.SetWindowText("&Connect");
		m_ConnectionControl.EnableWindow(FALSE);
		m_LSV2.SetCaption("No connection");
	}
	else
	{
		CString strMsg = "Disconnect error: " + m_LSV2.GetLastErrorString();
		MessageBox(strMsg);
		m_LSV2.SetCaption("Connected with " + m_LSV2.GetVersionTNC() + "; Disconnect failed");
	}

	return TRUE;
}




void CTestConnection::OnReconnect()
{
	BOOL bReconnect = TRUE;

	Connect(bReconnect);

}


void CTestConnection::OnConnect()
{
	CWaitCursor WaitCursor;

	UpdateData();

	CString strButton;
	m_Connect.GetWindowText(strButton);


	if (strButton != "&Connect")
		OnDisconnect(1, 1);
	else
	{
		BOOL bReconnect = FALSE;
		Connect(bReconnect);
	}
}


void CTestConnection::Connect(BOOL DoReconnect)
{
	BOOL ok = FALSE;

	UpdateData();

	m_LSV2.SetProtocolFile(m_ProtocolFile);
	m_LSV2.SetDialogLanguage(m_nLanguage);

	if (m_Address.Left(3) == "COM")
	{
		m_LSV2.SetMedium(0);                     // 0: Serial
		m_LSV2.SetPort(m_Address);
	}
	else
	{
		m_LSV2.SetMedium(1);                     // 1: Ethernet
		m_LSV2.SetIPAddress(m_Address);
	}

	m_LSV2.SetProgressDialogVisible(1);
	m_LSV2.SetHostFunction(TRUE);

	if (DoReconnect)
		ok = m_LSV2.ReConnect();
	else
		ok = m_LSV2.Connect();

	if (ok)
	{
		if (m_ConnectionControl.GetCheck() != 0)
			m_LSV2.TestConnection(3);  // Activate Keep alive packets

		CString strSik = m_LSV2.GetVersionSIK();
		CString strControl = m_LSV2.GetVersionTNC();

		m_LSV2.SetCaption("Connected with " + strControl + "; SIK: " + strSik);

		m_Connect.SetWindowText("&Disconnect");
		m_ConnectionControl.EnableWindow(FALSE);

		CTestocxSheet* pSheet = (CTestocxSheet*)GetParent();
		pSheet->EnablePages();
	}
	else
		m_LSV2.SetCaption(m_LSV2.GetLastErrorString());
}




BEGIN_EVENTSINK_MAP(CTestConnection, CPropertyPage)
	//{{AFX_EVENTSINK_MAP(CTestConnection)
	ON_EVENT(CTestConnection, IDC_LSV2, 9 /* ConnectionLost */, OnConnectionLost, VTS_NONE)
	ON_EVENT(CTestConnection, IDC_LSV2, 3 /* TransferCompleted */, OnTransferCompleted, VTS_I4)
	ON_EVENT(CTestConnection, IDC_LSV2, 6 /* MsgErrorReceived */, OnMsgErrorReceived, VTS_I4)
	ON_EVENT(CTestConnection, IDC_LSV2, 7 /* EventReceived */, OnEventReceived, VTS_BSTR)
	ON_EVENT(CTestConnection, IDC_LSV2, 1 /* PLCStatusReceived */, OnPLCStatusReceived, VTS_I4)
	ON_EVENT(CTestConnection, IDC_LSV2, 2 /* PLCMsgReceived */, OnPLCMsgReceived, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


BOOL CTestConnection::OnKillActive()
{
	if (!m_LSV2.TestConnection(0))
	{
		MessageBox("Please connect first!");
		return FALSE;
	}

	return CPropertyPage::OnKillActive();
}


void CTestConnection::OnInfo()
{
	m_LSV2.AboutBox();
}

BOOL CTestConnection::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTestConnection::OnVersion()
{
	MessageBox(CString("OCX Version: " + m_LSV2.GetVersionOCX()), NULL, MB_ICONINFORMATION);
}



// LSV2 Event-Handler

void CTestConnection::OnConnectionLost()
{
	((CTestocxSheet*)GetParent())->SetActivePage(0);

	m_LSV2.SetCaption("Lost connection. Disconnecting...");

	// Do not disconnect in the event handler directly!
	PostMessage(WM_DISCONNECT);
}


void CTestConnection::OnMsgErrorReceived(long ErrorNumber)
{
	char Message[80];

	sprintf(Message, "X_ER Error: 0x%X", ErrorNumber);

	if (((CTestocxSheet*)GetParent())->m_Page1.m_hWnd)
		((CTestocxSheet*)GetParent())->m_Page1.m_Status.SetWindowText(Message);
	else if (((CTestocxSheet*)GetParent())->m_Page5.m_hWnd)
		((CTestocxSheet*)GetParent())->m_Page5.m_Status.SetWindowText(Message);

	MessageBeep(0xFFFFFFFF);
}

void CTestConnection::OnEventReceived(LPCTSTR EventString)
{
	int Len;
	// An Ende anh鋘gen
	Len = m_pEventList->GetWindowTextLength();
	m_pEventList->SetSel(Len, Len);
	m_pEventList->ReplaceSel(EventString);
	MessageBeep(0xFFFFFFFF);

#ifdef RESTARTTEST
	if (!strnicmp(EventString, "STIB: OFF", 9))
	{
		CTestDnc* pPage1;

		pPage1 = &((CTestocxSheet*)GetParent())->m_Page1;
		if (pPage1->m_RepeatStart)
			pPage1->StartAgain();
	}
#endif
}

void CTestConnection::OnPLCStatusReceived(long Status)
{
	char Message[80];

	sprintf(Message, "0x%08X", Status);

	((CTestocxSheet*)GetParent())->m_Page5.m_Received_DWord.SetWindowText(Message);
	MessageBeep(0xFFFFFFFF);
}

void CTestConnection::OnPLCMsgReceived(LPCTSTR Message)
{
	((CTestocxSheet*)GetParent())->m_Page5.m_Received_String.SetWindowText(Message);
	MessageBeep(0xFFFFFFFF);
}


void CTestConnection::OnTransferCompleted(long TransferResult)
{
	CTestocxSheet* pSheet = (CTestocxSheet*)GetParent();
	ASSERT(pSheet);

	CString strStatus;
	strStatus.Format("Background transfer completed. Result %lX", TransferResult);
	pSheet->m_Page10.m_lblStatus.SetWindowText(strStatus);
}


void CTestConnection::OnTest()
{
	if (!m_LSV2.TestConnection(2))
	{
		MessageBox("Please connect first!");
		return;
	}

	if (m_LSV2.TestConnection(3))
	{
		MessageBox("Connection test with keep alive activated!");
		return;
	}

	/*
	  m_LSV2.TransmitChatText("Hallo");
	  m_LSV2.TransmitChatText("@Close");

	  m_LSV2.SetHostFunction(FALSE);

	  m_LSV2.TransmitSysCommand(1);

	  m_LSV2.DisConnect();
	*/

}


/////////////////////////////////////////////////////////////////////////////
// CTestDnc property page
/////////////////////////////////////////////////////////////////////////////

CTestDnc::CTestDnc() : CPropertyPage(CTestDnc::IDD)
{
	//{{AFX_DATA_INIT(CTestDnc)
	m_Command = 3;
	m_FileName = _T("TEST.H");
	//}}AFX_DATA_INIT
}

CTestDnc::~CTestDnc()
{
}

void CTestDnc::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDnc)
	DDX_Control(pDX, IDC_CONVERTERPATH, m_ConverterPath);
	DDX_Control(pDX, IDC_CONVERTER, m_Converter);
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_Control(pDX, IDC_START, m_Start);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	DDX_CBIndex(pDX, IDC_COMMAND, m_Command);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDnc, CPropertyPage)
	//{{AFX_MSG_MAP(CTestDnc)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_CBN_SELCHANGE(IDC_COMMAND, OnSelchangeCommand)
	ON_BN_CLICKED(IDC_BTN_STATUS, OnBtnStatus)
	ON_BN_CLICKED(IDC_CONVERTER, OnConverter)
	ON_EN_CHANGE(IDC_CONVERTERPATH, OnChangeConverterpath)
	ON_BN_CLICKED(IDC_ABORT, OnAbort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CTestDnc::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// Do not call CPropertyPage::OnPaint() for painting messages
}

BEGIN_EVENTSINK_MAP(CTestDnc, CPropertyPage)
	//{{AFX_EVENTSINK_MAP(CTestDnc)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CTestDnc::OnStart()
{
	BOOL ok;

	CString TargetName;

	UpdateData();

	if (m_Command == 6)
	{
		m_Command = 2;
#ifdef RESTARTTEST
		m_RepeatStart = TRUE;
#else
		MessageBox("Test not enabled");
		return;
#endif
	}

	TargetName = m_FileName.Mid(m_FileName.ReverseFind('\\') + 1);

	if (m_Command == 0)
	{
		m_pLSV2->SetCanOverwrite(1);
		m_pLSV2->SetBackgroundTransfer(TRUE);
		ok = m_pLSV2->TransmitFile(m_FileName, TargetName);
		if (ok)
		{
			m_Status.SetWindowText("Transmission started");

			m_Command = 2;
			UpdateData(FALSE);
		}
		else
			m_Status.SetWindowText(m_pLSV2->GetLastErrorString());
	}
	else
	{
		ok = m_pLSV2->RunProgram(m_FileName, m_Command);
		if (!ok)
			m_Status.SetWindowText(m_pLSV2->GetLastErrorString());
		else
			m_Status.SetWindowText("Command sent");

	}

}


void CTestDnc::OnSelchangeCommand()
{
	UpdateData();

	GetDlgItem(IDC_FILENAME)->EnableWindow(m_Command <= 3 || m_Command >= 6);

}

BOOL CTestDnc::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	OnSelchangeCommand(); // Enable/Disable initialisieren

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTestDnc::OnBtnStatus()
{
	CString StatusInfo;
	StatusInfo.Format("%d Bytes transmitted", m_pLSV2->GetTransferProgress());
	m_Status.SetWindowText(StatusInfo);
}


void CTestDnc::OnConverter()
{
	if (m_Converter.GetCheck())
	{
		CString Path;
		char* pBuffer;

		m_ConverterPath.ShowWindow(SW_SHOW);

		pBuffer = Path.GetBuffer(100);
		GetCurrentDirectory(100, pBuffer);
		Path.ReleaseBuffer();
		Path += "\\" + m_pLSV2->GetIPAddress();;

		m_ConverterPath.SetWindowText(Path);
		m_pLSV2->SetOnlineConverterPath(Path);
	}
	else
	{
		m_pLSV2->SetOnlineConverterPath("");
		m_ConverterPath.ShowWindow(SW_HIDE);
	}


}

void CTestDnc::OnChangeConverterpath()
{
	CString Path;

	m_ConverterPath.GetWindowText(Path);
	m_pLSV2->SetOnlineConverterPath(Path);
}

void CTestDnc::OnAbort()
{
	BOOL ok;

	// Mode 11:bricht gerade laufende (Datei-)躡ertragung ab
	// Mode 12:bricht gerade h鋘gende 躡ertragung ab

	if (!m_pLSV2->TestConnection(12))
		ok = m_pLSV2->TestConnection(11);

	if (!ok)
		MessageBeep(0xFFFFFFFF);

}

void CTestDnc::StartAgain()
{
	Sleep(30);

	OnStart();

#ifdef SPECIALTEST
	CString MemData;
	MemData = m_pLSV2->ReceiveMemBlock(1, 0, 1);
#endif
}



/////////////////////////////////////////////////////////////////////////////
// CTestEvents property page
/////////////////////////////////////////////////////////////////////////////

CTestEvents::CTestEvents() : CPropertyPage(CTestEvents::IDD)
{
	//{{AFX_DATA_INIT(CTestEvents)
	m_Mode = 1;
	m_Class = 0;
	m_Sender = 0;
	m_Priority = 0;
	m_TypeString = _T("");
	m_EventId = 0;
	//}}AFX_DATA_INIT
}

CTestEvents::~CTestEvents()
{
}

void CTestEvents::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestEvents)
	DDX_Control(pDX, IDC_EVENTS, m_Events);
	DDX_Control(pDX, IDC_CLASS, m_ClassCombo);
	DDX_Radio(pDX, IDC_FCLEAR, m_Mode);
	DDX_CBIndex(pDX, IDC_CLASS, m_Class);
	DDX_CBIndex(pDX, IDC_SENDER, m_Sender);
	DDX_CBIndex(pDX, IDC_PRIORITY, m_Priority);
	DDX_Text(pDX, IDC_EVNAME, m_TypeString);
	DDX_CBIndex(pDX, IDC_EVID, m_EventId);
	//}}AFX_DATA_MAP
}


BOOL CTestEvents::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	OnSelchangeClass();  // Controls Enable/Disable

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



BEGIN_MESSAGE_MAP(CTestEvents, CPropertyPage)
	//{{AFX_MSG_MAP(CTestEvents)
	ON_CBN_SELCHANGE(IDC_CLASS, OnSelchangeClass)
	ON_BN_CLICKED(IDC_APPLY, OnApplyFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CTestEvents::OnApplyFilter()
{
	BOOL ok;

	UpdateData();

#ifdef SPECIALTEST
	CString MemData;
#endif

	m_Class += 1;
	if (m_Class > 4)
		m_Class += 0x10 - 4;

	m_EventId += 1;

	ok = m_pLSV2->SetEventMask((short)m_Mode, (short)m_Class, (short)m_EventId, (short)m_Sender, (short)m_Priority, m_TypeString);

	if (ok)
		m_Events.SetWindowText("Filter installed\r\n");
	else
		m_Events.SetWindowText(m_pLSV2->GetLastErrorString());

#ifdef SPECIALTEST
	for (int i = 0; i < 1000; i++)
		MemData = m_pLSV2->ReceiveMemBlock(1, 0, 1);

#endif
}




/////////////////////////////////////////////////////////////////////////////
// CTestTable property page

CTestTable::CTestTable() : CPropertyPage(CTestTable::IDD)
{
	//{{AFX_DATA_INIT(CTestTable)
	m_SQLString = _T("WHERE R >= 1");
	m_FileName = _T("TNC:\\TOOL.T");
	m_StartLine = 0;
	//}}AFX_DATA_INIT
}

CTestTable::~CTestTable()
{
}

void CTestTable::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestTable)
	DDX_Control(pDX, IDC_FIRST, m_First);
	DDX_Text(pDX, IDC_SQLSTRING, m_SQLString);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_STARTLINE, m_StartLine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestTable, CPropertyPage)
	//{{AFX_MSG_MAP(CTestTable)
	ON_EN_CHANGE(IDC_FILENAME, OnChangeFilename)
	ON_EN_CHANGE(IDC_SQLSTRING, OnChangeSQLstring)
	ON_BN_CLICKED(IDC_FIRST, OnFirst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



#ifdef _TEST
if (ok)
{
	m_LSV2.SetCaption(m_LSV2.ReceiveMemBlock(0, 100, 7));


	m_LSV2.TransmitMemBlock(0, 100, "0 1 0 1 0 1 0");

	m_LSV2.SetCaption(m_LSV2.ReceiveMemBlock(0, 100, 7));

	m_Connect.EnableWindow(FALSE);
	m_Start.EnableWindow();
}
else
m_LSV2.SetCaption(m_LSV2.GetLastErrorString());
#endif

void CTestEvents::OnSelchangeClass()
{
	UpdateData();

	GetDlgItem(IDC_EVID)->EnableWindow(m_Class == 3);

	GetDlgItem(IDC_SENDER)->EnableWindow(m_Class > 3);
	GetDlgItem(IDC_PRIORITY)->EnableWindow(m_Class == 5);

	GetDlgItem(IDC_EVNAME)->EnableWindow(m_Class == 6);
}




void CTestTable::OnChangeFilename()
{
	UpdateData();

	if (m_FileName.IsEmpty() || m_SQLString.IsEmpty())
		m_First.EnableWindow(FALSE);
	else
		m_First.EnableWindow(TRUE);
}

void CTestTable::OnChangeSQLstring()
{
	UpdateData();

	if (m_FileName.IsEmpty() || m_SQLString.IsEmpty())
		m_First.EnableWindow(FALSE);
	else
		m_First.EnableWindow(TRUE);
}

void CTestTable::OnFirst()
{
	CString TableLine;

	UpdateData();

	TableLine = m_pLSV2->ReceiveTableLine(m_FileName, m_SQLString, m_StartLine);

	if (TableLine.IsEmpty())
		TableLine = "<No line found or error>";

	GetDlgItem(IDC_TABLELINE)->SetWindowText(TableLine);
}


/////////////////////////////////////////////////////////////////////////////
// CTestMessage property page

CTestMessage::CTestMessage() : CPropertyPage(CTestMessage::IDD)
{
	//{{AFX_DATA_INIT(CTestMessage)
	m_ChatLine = _T("");
	m_ChatLeft = 0;
	m_ChatTop = 0;
	m_ChatColumns = 60;
	m_ChatRows = 10;
	m_ChatFont = 0;
	//}}AFX_DATA_INIT
}

CTestMessage::~CTestMessage()
{
}

void CTestMessage::DoDataExchange(CDataExchange * pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestMessage)
	DDX_Text(pDX, IDC_CHAT_LINE, m_ChatLine);
	DDV_MaxChars(pDX, m_ChatLine, 80);
	DDX_Text(pDX, IDC_LEFT, m_ChatLeft);
	DDV_MinMaxUInt(pDX, m_ChatLeft, 0, 640);
	DDX_Text(pDX, IDC_TOP, m_ChatTop);
	DDV_MinMaxUInt(pDX, m_ChatTop, 0, 480);
	DDX_Text(pDX, IDC_COLUMNS, m_ChatColumns);
	DDV_MinMaxUInt(pDX, m_ChatColumns, 0, 1000);
	DDX_Text(pDX, IDC_ROWS, m_ChatRows);
	DDV_MinMaxUInt(pDX, m_ChatRows, 0, 1000);
	DDX_CBIndex(pDX, IDC_CHAT_FONT, m_ChatFont);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestMessage, CPropertyPage)
	//{{AFX_MSG_MAP(CTestMessage)
	ON_BN_CLICKED(IDC_CHAT_ADD, OnChatAdd)
	ON_BN_CLICKED(IDC_CHAT_CLEAR, OnChatClear)
	ON_BN_CLICKED(IDC_CHAT_CLOSE, OnChatClose)
	ON_BN_CLICKED(IDC_CHAT_OPEN, OnChatOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMessage message handlers

void CTestMessage::OnChatAdd()
{
	BOOL ok;

	UpdateData();

	ok = m_pLSV2->TransmitChatText(m_ChatLine);

	if (!ok)
		MessageBeep(0xFFFFFFFF);
}


void CTestMessage::OnChatClear()
{
	BOOL ok;

	ok = m_pLSV2->TransmitChatText("@CLEAR");

	if (!ok)
		MessageBeep(0xFFFFFFFF);
}

void CTestMessage::OnChatClose()
{
	BOOL ok;

	ok = m_pLSV2->TransmitChatText("@CLOSE");

	if (!ok)
		MessageBeep(0xFFFFFFFF);
}


void CTestMessage::OnChatOpen()
{
	BOOL ok;

	UpdateData();

	// Font: 1: klein, 2: mittel
	// Flags: 0 (nicht definiert)
	ok = m_pLSV2->OpenChatWindow(m_ChatLeft, m_ChatTop, m_ChatColumns, m_ChatRows, m_ChatFont + 1, 0, m_ChatLine);

	if (!ok)
		MessageBeep(0xFFFFFFFF);

}



/////////////////////////////////////////////////////////////////////////////
// CTestPlcCommunication property page
/////////////////////////////////////////////////////////////////////////////


CTestPlcCommunication::CTestPlcCommunication() : CPropertyPage(CTestPlcCommunication::IDD)
{
	//{{AFX_DATA_INIT(CTestPlcCommunication)
	//}}AFX_DATA_INIT
}

CTestPlcCommunication::~CTestPlcCommunication()
{
}

void CTestPlcCommunication::DoDataExchange(CDataExchange * pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPlcCommunication)
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_Control(pDX, IDC_TRANSMIT_STRING, m_Transmit_String);
	DDX_Control(pDX, IDC_TRANSMIT, m_Transmit_DWord);
	DDX_Control(pDX, IDC_PLC_DWORD, m_PLC_DWord);
	DDX_Control(pDX, IDC_PLC_STRING, m_PLC_String);
	DDX_Control(pDX, IDC_RECEIVED_STRING, m_Received_String);
	DDX_Control(pDX, IDC_RECEIVED_DWORD, m_Received_DWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestPlcCommunication, CPropertyPage)
	//{{AFX_MSG_MAP(CTestPlcCommunication)
	ON_BN_CLICKED(IDC_TRANSMIT, OnTransmit)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_EN_CHANGE(IDC_PLC_STRING, OnChangePlcString)
	ON_BN_CLICKED(IDC_TRANSMIT_STRING, OnTransmitString)
	ON_EN_CHANGE(IDC_PLC_DWORD, OnChangePlcDword)
	//ON_WM_TIMER()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

#include <windows.h>
#include <mmsystem.h>
#include <iostream>

#pragma comment(lib, "winmm.lib")


void CTestPlcCommunication::OnClear()
{
	m_Received_String.SetWindowText("");
	m_Received_DWord.SetWindowText("");
}

void CTestPlcCommunication::OnChangePlcDword()
{
	CString Str;
	m_PLC_DWord.GetWindowText(Str);
	m_Transmit_DWord.EnableWindow(!Str.IsEmpty());
}

void CTestPlcCommunication::OnChangePlcString()
{
	CString Str;
	m_PLC_String.GetWindowText(Str);
	m_Transmit_String.EnableWindow(!Str.IsEmpty());
}

std::string CTestPlcCommunication::getCurTime()
{
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format(_T("%Y-%m-%d_%H:%M:%S"));

	CT2CA pszConvertedAnsiString(strTime);
	return std::string(pszConvertedAnsiString);
}

//void CTestPlcCommunication::TimerProc(UINT uID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
//{
//	//std::cout << "高精度定时器触发！" << std::endl;
//	CString strValue;
//
//	m_PLC_DWord.GetWindowText(strValue);
//	char* p = strValue.GetBuffer(80);
//
//	long lVal;
//	if (sscanf(p, "0x%X", &lVal) == 1 ||
//		sscanf(p, "$%X", &lVal) == 1 ||
//		sscanf(p, "%ld", &lVal) == 1)
//	{
//		// 记录起始时间点
//		//auto start = std::chrono::high_resolution_clock::now();
//		CString data = m_pLSV2->ReceiveMemBlock(7, lVal, 1);
//		// 记录结束时间点
//		//auto end = std::chrono::high_resolution_clock::now();
//
//		// 计算耗时（以毫秒为单位）
//		//std::chrono::duration<double, std::milli> duration = end - start;
//
//		//double ddd = duration.count();
//
//		//std::cout << "函数执行时间: " << ddd << " 毫秒" << std::endl;
//
//		m_pLSV2->SetCaption(data);
//
//		data = "$" + data;
//		char* p2 = data.GetBuffer(80);
//
//		long lVal2;
//		if (sscanf(p2, "0x%X", &lVal2) == 1 ||
//			sscanf(p2, "$%X", &lVal2) == 1 ||
//			sscanf(p2, "%ld", &lVal2) == 1)
//		{
//			//double value = double(lVal2);
//			m_listOptiData.push_back(getCurTime() + "," + std::to_string(lVal2));
//			//m_Received_DWord.SetWindowText(CString(std::to_string(lVal2).c_str()));
//		}
//	}
//}

void CALLBACK TimerProc(UINT uID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	CTestPlcCommunication* pThis = reinterpret_cast<CTestPlcCommunication*>(dwUser);
	if (pThis)
	{
		pThis->OnTimer();
	}
}

void CTestPlcCommunication::OnTransmit()
{
	if (m_nRedID == 0)//判断定时器有没有启动
	{
		m_listOptiData.clear();
		//ActBlockNum,
		m_outFile << "time,Current" << std::endl;

		timeBeginPeriod(1); // 设置最小时间间隔为 1ms
		//m_nRedID = SetTimer(1, 2, NULL);//启动定时器
        

        m_nRedID = timeSetEvent(5, 1, TimerProc, reinterpret_cast<DWORD_PTR>(this), TIME_PERIODIC); // 5ms 定时

		if (m_nRedID == 0) 
		{
			timeEndPeriod(1); // 还原系统时间精度
			std::cerr << "定时器创建失败！" << std::endl;
			return;
		}
	}
	else
	{
		//KillTimer(m_nRedID);//关闭定时器

		timeKillEvent(m_nRedID); // 关闭定时器
		timeEndPeriod(1); // 还原系统时间精度

		m_nRedID = 0;

		char path[MAX_PATH];
		GetModuleFileName(NULL, path, MAX_PATH);

		// 移除文件名，仅保留目录部分
		std::string directory(path);
		int pos = directory.find_last_of('\\'); // 查找最后一个 '\'
		if (pos != -1) {
			directory = directory.substr(0, pos); // 截取目录部分
		}

		std::string dir(path);
		std::string filename = directory + "\\opti_current.csv";

		// 创建一个输出文件流对象
		m_outFile = std::ofstream(filename);
		// 检查文件是否成功打开
		if (m_outFile.fail())
		{
			std::cerr << "无法打开文件: " << filename << std::endl;
			return;
		}

		for (std::string value : m_listOptiData)
		{
			m_outFile << value << std::endl;
		}

		m_listOptiData.clear();

		m_outFile.close();// 关闭文件流
	}
	/*return;*/

	/*
	if (false)
	{
		//// 写入字符串到文件
		//outFile << "这是第一行文本。" << std::endl;
		//outFile << "这是第二行文本。" << std::endl;
		//outFile << "这是第三行文本。" << std::endl;

		//CString strValue;

		//m_PLC_DWord.GetWindowText(strValue);
		//char* p = strValue.GetBuffer(80);

		//long lVal;
		//if (sscanf(p, "0x%X", &lVal) == 1 ||
		//	sscanf(p, "$%X", &lVal) == 1 ||
		//	sscanf(p, "%ld", &lVal) == 1)
		//{

		//	CString data = m_pLSV2->ReceiveMemBlock(7, lVal, 1);
		//	m_pLSV2->SetCaption(data);
		//	data = "$" + data;

		//	char* p2 = data.GetBuffer(80);

		//	long lVal2;
		//	if (sscanf(p2, "0x%X", &lVal2) == 1 ||
		//		sscanf(p2, "$%X", &lVal2) == 1 ||
		//		sscanf(p2, "%ld", &lVal2) == 1)
		//	{
		//		//std::stoi(aHex, 0, 16);
		//		//HexToDec::Hex_Conversion_Dec(std::string(p2));
		//		double cccccv = double(lVal2) / 10000;
		//		m_Received_DWord.SetWindowText(CString(std::to_string(cccccv).c_str()));
		//	}
		//	else
		//	{
		//		m_Received_DWord.SetWindowText(data);
		//	}
		//}



		//m_pLSV2->TransmitMemBlock(0, 8072, "0 1 0 1 0 1 0");
		//m_pLSV2->SetCaption (m_pLSV2->ReceiveMemBlock(0, 8072, 7));
		//m_Connect.EnableWindow(FALSE);
		//m_Start.EnableWindow();
	}
	else
	{
		CString strValue;

		m_PLC_DWord.GetWindowText(strValue);
		char* p = strValue.GetBuffer(80);

		long lVal;
		if (sscanf(p, "0x%X", &lVal) == 1 ||
			sscanf(p, "$%X", &lVal) == 1 ||
			sscanf(p, "%ld", &lVal) == 1)
		{
			BOOL ok = m_pLSV2->TransmitPlcCommand(lVal);
			if (!ok)
				MessageBeep(0xFFFFFFFF);
		}
		else
			MessageBox("Invalid format for DWORD. Use 0xXXXXXXXX or decimal number");
	}
	*/
}

void CTestPlcCommunication::OnTransmitString()
{
	CString Str;
	m_PLC_String.GetWindowText(Str);

	BOOL ok = m_pLSV2->TransmitPlcString(Str);
	if (!ok)
		MessageBeep(0xFFFFFFFF);
}
#include <chrono>

void CTestPlcCommunication::OnTimer()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strValue;

	m_PLC_DWord.GetWindowText(strValue);
	char* p = strValue.GetBuffer(80);

	long lVal;
	if (sscanf(p, "0x%X", &lVal) == 1 ||
		sscanf(p, "$%X", &lVal) == 1 ||
		sscanf(p, "%ld", &lVal) == 1)
	{
		// 记录起始时间点
		//auto start = std::chrono::high_resolution_clock::now();
		CString data = m_pLSV2->ReceiveMemBlock(7, lVal, 1);
		// 记录结束时间点
		//auto end = std::chrono::high_resolution_clock::now();

		// 计算耗时（以毫秒为单位）
		//std::chrono::duration<double, std::milli> duration = end - start;

		//double ddd = duration.count();

		//std::cout << "函数执行时间: " << ddd << " 毫秒" << std::endl;

		m_pLSV2->SetCaption(data);

		data = "$" + data;
		char* p2 = data.GetBuffer(80);

		long lVal2;
		if (sscanf(p2, "0x%X", &lVal2) == 1 ||
			sscanf(p2, "$%X", &lVal2) == 1 ||
			sscanf(p2, "%ld", &lVal2) == 1)
		{
			//double value = double(lVal2);
			m_listOptiData.push_back(getCurTime() + "," + std::to_string(lVal2));
			//m_Received_DWord.SetWindowText(CString(std::to_string(lVal2).c_str()));
		}
	}

	//CPropertyPage::OnTimer(nIDEvent);
}


/////////////////////////////////////////////////////////////////////////////
// CTestDncInfo property page

CTestDncInfo::CTestDncInfo() : CPropertyPage(CTestDncInfo::IDD)
{
	//{{AFX_DATA_INIT(CTestDncInfo)
	m_Command = 0;
	m_Parameter = 0;
	//}}AFX_DATA_INIT
}

CTestDncInfo::~CTestDncInfo()
{
}

void CTestDncInfo::DoDataExchange(CDataExchange * pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDncInfo)
	DDX_Control(pDX, IDC_START, m_Start);
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_CBIndex(pDX, IDC_COMMAND, m_Command);
	DDX_Text(pDX, IDC_PARAMETER, m_Parameter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDncInfo, CPropertyPage)
	//{{AFX_MSG_MAP(CTestDncInfo)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_CBN_SELCHANGE(IDC_COMMAND, OnSelchangeCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CTestDncInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// Do not call CPropertyPage::OnPaint() for painting messages
}

BEGIN_EVENTSINK_MAP(CTestDncInfo, CPropertyPage)
	//{{AFX_EVENTSINK_MAP(CTestDncInfo)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CTestDncInfo::OnStart()
{
	UpdateData();

	m_Status.SetWindowText(m_pLSV2->ReceiveDNCInfo(m_Cmd, m_Parameter));
}


void CTestDncInfo::OnSelchangeCommand()
{
	CString strCommand;

	GetDlgItem(IDC_COMMAND)->GetWindowText(strCommand);
	m_Cmd = atoi(strCommand);

	GetDlgItem(IDC_PARAMETER)->EnableWindow(m_Cmd == 10);
	GetDlgItem(IDC_LBL_PARA)->EnableWindow(m_Cmd == 10);
}

BOOL CTestDncInfo::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	OnSelchangeCommand(); // Enable/Disable initialisieren

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTestDncInfo::StartAgain()
{
	Sleep(30);

	OnStart();
}



/////////////////////////////////////////////////////////////////////////////
// CTestMachineConstants property page

CTestMachineConstants::CTestMachineConstants() : CPropertyPage(CTestMachineConstants::IDD)
{
	//{{AFX_DATA_INIT(CTestMachineConstants)
	m_ConstantNames = _T("100.1");
	m_ConstantValues = _T("");
	m_nExecutionMode = 0;
	//}}AFX_DATA_INIT
}

CTestMachineConstants::~CTestMachineConstants()
{
}


BOOL CTestMachineConstants::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTestMachineConstants::DoDataExchange(CDataExchange * pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestMachineConstants)
	DDX_Text(pDX, IDC_CONSTANT_NAMES, m_ConstantNames);
	DDX_Text(pDX, IDC_CONSTANT_VALUES, m_ConstantValues);
	DDX_CBIndex(pDX, IDC_EXECUTION_MODE, m_nExecutionMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestMachineConstants, CPropertyPage)
	//{{AFX_MSG_MAP(CTestMachineConstants)
	ON_BN_CLICKED(IDC_SET_CONSTANT, OnSetConstant)
	ON_BN_CLICKED(IDC_GET_CONSTANT, OnGetConstant)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CTestMachineConstants::OnSetConstant()
{
	BOOL ok;
	UpdateData();

	ok = m_pLSV2->TransmitMachineConstants(m_ConstantNames, m_ConstantValues, m_nExecutionMode);
	if (!ok)
		MessageBox(m_pLSV2->GetLastErrorString());
}




void CTestMachineConstants::OnGetConstant()
{
	UpdateData();

	m_ConstantValues = m_pLSV2->ReceiveMachineConstants(m_ConstantNames);

	if (m_ConstantValues.IsEmpty() &&  // echter Leerstring oder Fehler
		m_pLSV2->GetLastError() != 0)
		MessageBox(m_pLSV2->GetLastErrorString());
	else
		UpdateData(FALSE);
}




/////////////////////////////////////////////////////////////////////////////
// CTestFileTime property page

CTestFileTime::CTestFileTime() : CPropertyPage(CTestFileTime::IDD)
{
	//{{AFX_DATA_INIT(CTestFileTime)
	m_FileName = _T("TNC:\\TEST.A");
	m_Time = _T("24.12.2004 12:00:00");
	m_CurrentTime = 0;
	//}}AFX_DATA_INIT
}

CTestFileTime::~CTestFileTime()
{
}

void CTestFileTime::DoDataExchange(CDataExchange * pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestFileTime)
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_TIME, m_Time);
	DDX_Radio(pDX, IDC_CURRENT_TIME, m_CurrentTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestFileTime, CPropertyPage)
	//{{AFX_MSG_MAP(CTestFileTime)
	ON_BN_CLICKED(IDC_SET_TIME, OnSetTime)
	ON_BN_CLICKED(IDC_CURRENT_TIME, OnCurrentTime)
	ON_BN_CLICKED(IDC_SPECIFIC_TIME, OnSpecificTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CTestFileTime::OnCurrentTime()
{
	GetDlgItem(IDC_TIME)->EnableWindow(FALSE);
}

void CTestFileTime::OnSpecificTime()
{
	GetDlgItem(IDC_TIME)->EnableWindow(TRUE);
}



void CTestFileTime::OnSetTime()
{
	UpdateData();

	COleDateTime Time;



	if (m_CurrentTime != 0)
	{
		int nYear, nMonth, nDay, nHour, nMin, nSec;

		if (sscanf(m_Time, "%d.%d.%d %d:%d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin, &nSec) != 6)
		{
			MessageBox("Enter time in format dd.mm.yyyy hh:mm:ss");
			return;
		}
		else
		{
			COleDateTime SetTime(nYear, nMonth, nDay, nHour, nMin, nSec);
			Time = SetTime;
		}
	}

	if (!m_pLSV2->SetFileTime(m_FileName, Time))
		MessageBox(m_pLSV2->GetLastErrorString());

}



/////////////////////////////////////////////////////////////////////////////
// CTestPreset property page

CTestPreset::CTestPreset() : CPropertyPage(CTestPreset::IDD)
{
	//{{AFX_DATA_INIT(CTestPreset)
	m_SetImmediate = 0;
	m_strMachineCoordinates = _T("10;10;10");
	m_strWorkpieceCoordinates = _T("0;0;0");
	m_strBaseRotation = _T("0");
	m_TableEntry = 1;
	//}}AFX_DATA_INIT
}

CTestPreset::~CTestPreset()
{
}

void CTestPreset::DoDataExchange(CDataExchange * pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPreset)
	DDX_Control(pDX, IDC_SET_PRESET, m_btnSetPreset);
	DDX_Radio(pDX, IDC_IMMEDIATE, m_SetImmediate);
	DDX_Text(pDX, IDC_MC, m_strMachineCoordinates);
	DDX_Text(pDX, IDC_WC, m_strWorkpieceCoordinates);
	DDX_Text(pDX, IDC_BASE_ROT, m_strBaseRotation);
	DDX_Text(pDX, IDC_TABLE_ENTRY, m_TableEntry);
	DDV_MinMaxLong(pDX, m_TableEntry, 1, 99999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestPreset, CPropertyPage)
	//{{AFX_MSG_MAP(CTestPreset)
	ON_BN_CLICKED(IDC_SET_PRESET, OnSetPreset)
	ON_EN_CHANGE(IDC_MC, OnChangeMc)
	ON_EN_CHANGE(IDC_WC, OnChangeWc)
	ON_EN_CHANGE(IDC_TABLE_ENTRY, OnChangeTableEntry)
	ON_BN_CLICKED(IDC_IMMEDIATE2, OnImmediate2)
	ON_BN_CLICKED(IDC_IMMEDIATE, OnImmediate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CTestPreset::OnSetPreset()
{
	UpdateData();

	if (m_SetImmediate == 1)
		m_TableEntry = -1;

	BOOL ok;
	ok = m_pLSV2->SetPreset(m_TableEntry, m_strMachineCoordinates, m_strWorkpieceCoordinates, m_strBaseRotation);
	if (!ok)
		MessageBox(m_pLSV2->GetLastErrorString());
}

void CTestPreset::OnChangeMc()
{
	EnablePresetButton();
}

void CTestPreset::OnChangeWc()
{
	EnablePresetButton();
}

void CTestPreset::OnChangeTableEntry()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
}

void CTestPreset::EnablePresetButton()
{
	UpdateData();
	m_btnSetPreset.EnableWindow(!m_strWorkpieceCoordinates.IsEmpty() &&
		!m_strMachineCoordinates.IsEmpty() &&
		!m_strBaseRotation.IsEmpty());
}

void CTestPreset::OnImmediate2()
{
	GetDlgItem(IDC_TABLE_ENTRY)->EnableWindow(FALSE);
}

void CTestPreset::OnImmediate()
{
	GetDlgItem(IDC_TABLE_ENTRY)->EnableWindow(TRUE);
}


/////////////////////////////////////////////////////////////////////////////
// CTestFileTransfer property page

CTestFileTransfer::CTestFileTransfer() : CPropertyPage(CTestFileTransfer::IDD)
{
	//{{AFX_DATA_INIT(CTestFileTransfer)
	m_strPCFileName = _T("c:\\temp\\test.a");
	m_strNCFileName = _T("TNC:\\TEST.A");
	m_bShowProgressDlg = FALSE;
	m_bBackgroundTransfer = FALSE;
	m_nMode = -1;
	m_bOverwrite = FALSE;
	//}}AFX_DATA_INIT
}


CTestFileTransfer::~CTestFileTransfer()
{
}


void CTestFileTransfer::DoDataExchange(CDataExchange * pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestFileTransfer)
	DDX_Control(pDX, IDC_STATUS, m_lblStatus);
	DDX_Text(pDX, IDC_BIN_TYPES, m_strBinTypes);
	DDX_Text(pDX, IDC_PC_NAME, m_strPCFileName);
	DDX_Text(pDX, IDC_NC_NAME, m_strNCFileName);
	DDX_Check(pDX, IDC_PROGRESSDLG, m_bShowProgressDlg);
	DDX_Check(pDX, IDC_BACKGROUNDTRANSFER, m_bBackgroundTransfer);
	DDX_Radio(pDX, IDC_MODETEXT, m_nMode);
	DDX_Check(pDX, IDC_OVERWRITE, m_bOverwrite);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestFileTransfer, CPropertyPage)
	//{{AFX_MSG_MAP(CTestFileTransfer)
	ON_BN_CLICKED(IDC_TRANSMIT_AUTO, OnTransmit)
	ON_BN_CLICKED(IDC_RECEIVE_AUTO, OnReceive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CTestFileTransfer::OnTransmit()
{
	CWaitCursor* pWait = NULL;

	UpdateData();

	m_pLSV2->SetBinaryFileTypes(m_strBinTypes);

	switch (m_nMode)
	{
	case 0: m_pLSV2->SetTransferMode(0); break;        // Text
	case 1: m_pLSV2->SetTransferMode(1); break;        // Binary
	case 2: m_pLSV2->SetTransferMode(10); break;       // Auto select
	case 3: m_pLSV2->SetTransferMode(5); break;        // Merge mode
	}

	m_pLSV2->SetProgressDialogVisible(m_bShowProgressDlg ? 1 : 0);  // en-/disable transfer dialog
	m_pLSV2->SetBackgroundTransfer(m_bBackgroundTransfer);      // en-/disable background file transfer
	m_pLSV2->SetCanOverwrite(m_bOverwrite ? 1 : 0);

	if (!m_bShowProgressDlg && !m_bBackgroundTransfer)
		pWait = new CWaitCursor;

	BOOL ok = m_pLSV2->TransmitFile(m_strPCFileName, m_strNCFileName);

	if (pWait)
		delete pWait;

	if (!ok)
		MessageBox(m_pLSV2->GetLastErrorString());
	else
	{
		if (m_bBackgroundTransfer)
			m_lblStatus.SetWindowText("Background transfer active...");
	}
}


void CTestFileTransfer::OnReceive()
{
	CWaitCursor* pWait = NULL;

	UpdateData();

	m_pLSV2->SetBinaryFileTypes(m_strBinTypes);
	switch (m_nMode)
	{
	case 0: m_pLSV2->SetTransferMode(0); break;        // Text
	case 1: m_pLSV2->SetTransferMode(1); break;        // Binary
	case 2: m_pLSV2->SetTransferMode(10); break;        // Auto select
	case 3: MessageBox("Only transmit file is allowed in merge mode"); return;
	}

	m_pLSV2->SetProgressDialogVisible(m_bShowProgressDlg ? 1 : 0);        // en/disable transfer dialog
	m_pLSV2->SetBackgroundTransfer(m_bBackgroundTransfer);      // en-/disable background file transfer
	m_pLSV2->SetCanOverwrite(m_bOverwrite ? 1 : 0);

	if (!m_bShowProgressDlg && !m_bBackgroundTransfer)
		pWait = new CWaitCursor;

	BOOL ok = m_pLSV2->ReceiveFile(m_strNCFileName, m_strPCFileName);

	if (pWait)
		delete pWait;

	if (!ok)
		MessageBox(m_pLSV2->GetLastErrorString());
	else
	{
		if (m_bBackgroundTransfer)
			m_lblStatus.SetWindowText("Background transfer active...");
	}
}


BOOL CTestFileTransfer::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_strBinTypes = m_pLSV2->GetBinaryFileTypes();

	m_nMode = 0;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



/////////////////////////////////////////////////////////////////////////////
// CTestBackup property page

CTestBackup::CTestBackup() : CPropertyPage(CTestBackup::IDD)
{
	//{{AFX_DATA_INIT(CTestBackup)
	m_strLstFileName = _T("C:\\temp\\scan.lst");
	m_strScanFolder = _T("TNC:\\DEMO");
	m_nScanMode = 0;
	m_strBckFileName = _T("C:\\temp\\test.bck");
	m_strBckLstFileName = _T("C:\\temp\\test.lst");
	m_bShowProgressDlg = FALSE;
	//}}AFX_DATA_INIT
}

CTestBackup::~CTestBackup()
{
}

void CTestBackup::DoDataExchange(CDataExchange * pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestBackup)
	DDX_Control(pDX, IDC_SCANFOLDER, m_ScanFolder);
	DDX_Text(pDX, IDC_LSTFILE, m_strLstFileName);
	DDX_Text(pDX, IDC_BCKFILE, m_strBckFileName);
	DDX_Check(pDX, IDC_PROGRESSDLG, m_bShowProgressDlg);
	DDX_Text(pDX, IDC_SCANFOLDER, m_strScanFolder);
	DDX_Radio(pDX, IDC_SCAN_MODE, m_nScanMode);
	DDX_Text(pDX, IDC_BCKLSTFILE, m_strBckLstFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestBackup, CPropertyPage)
	//{{AFX_MSG_MAP(CTestBackup)
	ON_BN_CLICKED(IDC_SCAN, OnScan)
	ON_BN_CLICKED(IDC_BACKUP, OnBackup)
	ON_BN_CLICKED(IDC_RESTORE, OnRestore)
	ON_BN_CLICKED(IDC_SCAN_MODE, OnScanMode)
	ON_BN_CLICKED(IDC_SCAN_MODE2, OnScanMode2)
	ON_BN_CLICKED(IDC_SCAN_MODE3, OnScanMode3)
	ON_BN_CLICKED(IDC_SCAN_MODE4, OnScanMode4)
	ON_EN_CHANGE(IDC_BCKFILE, OnChangeBckfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestBackup message handlers

void CTestBackup::OnScan()
{
	CWaitCursor* pWait = NULL;

	UpdateData();

	m_pLSV2->SetProgressDialogVisible(m_bShowProgressDlg ? 1 : 0);  // en-/disable transfer dialog

	if (!m_bShowProgressDlg)
		pWait = new CWaitCursor;

	BOOL ok = m_pLSV2->Backup(m_nScanMode, m_strLstFileName, m_strScanFolder);

	if (pWait)
		delete pWait;

	if (!ok)
		MessageBox(m_pLSV2->GetLastErrorString());
}


void CTestBackup::OnBackup()
{
	CWaitCursor* pWait = NULL;

	UpdateData();

	m_pLSV2->SetProgressDialogVisible(m_bShowProgressDlg ? 1 : 0);  // en-/disable transfer dialog

	if (!m_bShowProgressDlg)
		pWait = new CWaitCursor;

	BOOL ok = m_pLSV2->Backup(4, m_strBckFileName, m_strLstFileName);

	if (pWait)
		delete pWait;

	if (!ok)
		MessageBox(m_pLSV2->GetLastErrorString());
}


void CTestBackup::OnRestore()
{
	CWaitCursor* pWait = NULL;

	UpdateData();

	m_pLSV2->SetProgressDialogVisible(m_bShowProgressDlg ? 1 : 0);  // en-/disable transfer dialog

	if (!m_bShowProgressDlg)
		pWait = new CWaitCursor;

	BOOL ok = m_pLSV2->Restore(0, m_strBckFileName, m_strBckLstFileName);

	if (pWait)
		delete pWait;

	if (!ok)
	{
		// If the user aborted the function in confirmation dialog, then there is no message needed
		if (m_pLSV2->GetLastError() != 0x20001719)
			MessageBox(m_pLSV2->GetLastErrorString());
	}
}


//////////////////////
// some dialog logic...

void CTestBackup::OnScanMode()
{
	m_ScanFolder.EnableWindow();
}

void CTestBackup::OnScanMode2()
{
	m_ScanFolder.EnableWindow();
}

void CTestBackup::OnScanMode3()
{
	m_ScanFolder.EnableWindow(FALSE);
}

void CTestBackup::OnScanMode4()
{
	m_ScanFolder.EnableWindow(FALSE);
}

void CTestBackup::OnChangeBckfile()
{
	UpdateData();
	CString strExt = m_strBckFileName.Right(4);
	strExt.MakeLower();
	if (strExt == ".bck")
	{
		m_strBckLstFileName = m_strBckFileName.Left(m_strBckFileName.GetLength() - 4) + ".lst";
		UpdateData(FALSE);
	}
}

