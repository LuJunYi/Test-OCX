#if !defined(AFX_LSV2CTL3_H__A5414A94_FEF2_4B8F_8B8A_F4F887FB82D1__INCLUDED_)
#define AFX_LSV2CTL3_H__A5414A94_FEF2_4B8F_8B8A_F4F887FB82D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CLSV2ctl3 wrapper class

class CLSV2ctl3 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CLSV2ctl3)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xf9ee051d, 0xc65d, 0x4480, { 0x8e, 0x35, 0x76, 0xf1, 0xf, 0xab, 0x15, 0xc6 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	CString GetCaption();
	void SetCaption(LPCTSTR);
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);
	COleFont GetFont();
	void SetFont(LPDISPATCH);
	short GetBorderStyle();
	void SetBorderStyle(short);
	CString Get_Port();
	void Set_Port(LPCTSTR);
	CString GetPort();
	void SetPort(LPCTSTR);
	BOOL GetAutoBaudRate();
	void SetAutoBaudRate(BOOL);
	BOOL GetBackgroundTransfer();
	void SetBackgroundTransfer(BOOL);
	long GetBaudRate();
	void SetBaudRate(long);
	CString GetBinaryFileTypes();
	void SetBinaryFileTypes(LPCTSTR);
	short GetCanOverwrite();
	void SetCanOverwrite(short);
	long GetDialogLanguage();
	void SetDialogLanguage(long);
	CString GetDirMask();
	void SetDirMask(LPCTSTR);
	CString GetIPAddress();
	void SetIPAddress(LPCTSTR);
	CString GetLoginPasswordPLC();
	void SetLoginPasswordPLC(LPCTSTR);
	CString GetLoginPasswordSYS();
	void SetLoginPasswordSYS(LPCTSTR);
	CString GetLoginPasswordTNC();
	void SetLoginPasswordTNC(LPCTSTR);
	CString GetOnlineConverterPath();
	void SetOnlineConverterPath(LPCTSTR);
	short GetProgressDialogVisible();
	void SetProgressDialogVisible(short);
	CString GetProtocolFile();
	void SetProtocolFile(LPCTSTR);
	long GetTransferMode();
	void SetTransferMode(long);
	CString GetBackgroundErrorString();
	void SetBackgroundErrorString(LPCTSTR);
	BOOL GetFileServerFunction();
	void SetFileServerFunction(BOOL);
	BOOL GetHostFunction();
	void SetHostFunction(BOOL);
	long GetLastError();
	void SetLastError(long);
	CString GetLastErrorString();
	void SetLastErrorString(LPCTSTR);
	short GetMedium();
	void SetMedium(short);
	BOOL GetTNCKeyLock();
	void SetTNCKeyLock(BOOL);
	BOOL GetTNCPrivateTree();
	void SetTNCPrivateTree(BOOL);
	long GetTransferProgress();
	void SetTransferProgress(long);
	long GetTransferState();
	void SetTransferState(long);
	CString GetVersionNC();
	void SetVersionNC(LPCTSTR);
	CString GetVersionOCX();
	void SetVersionOCX(LPCTSTR);
	CString GetVersionOPT();
	void SetVersionOPT(LPCTSTR);
	CString GetVersionPLC();
	void SetVersionPLC(LPCTSTR);
	CString GetVersionSIK();
	void SetVersionSIK(LPCTSTR);
	CString GetVersionTNC();
	void SetVersionTNC(LPCTSTR);

// Operations
public:
	BOOL ActivateProgram(LPCTSTR ProgramName);
	BOOL Backup(short Mode, LPCTSTR FileName, LPCTSTR Source);
	BOOL BreakTransfer();
	BOOL ChangeDir(LPCTSTR PathName);
	BOOL Connect();
	BOOL CopyFile(LPCTSTR FileName, LPCTSTR NewFileName);
	BOOL DeleteDir(LPCTSTR PathName);
	BOOL DeleteFile(LPCTSTR FileName);
	BOOL DisConnect();
	BOOL Extract(short Mode, LPCTSTR FileName, LPCTSTR Source, LPCTSTR Target);
	CString GetDirData(short Type);
	CString GetFileData(LPCTSTR FileName, short Type);
	BOOL Login(LPCTSTR KeyWord);
	BOOL Logout(LPCTSTR KeyWord);
	BOOL MakeDir(LPCTSTR PathName);
	BOOL OpenChatWindow(short Left, short Top, short Columns, short Rows, short Font, short Flags, LPCTSTR Caption);
	BOOL ProtectFile(LPCTSTR FileName, short Type);
	CString ReceiveDNCInfo(short Type, long InfoPara);
	long ReceiveDSPData(short Channel, LPCTSTR ParaString, short* DataBuffer);
	long ReceiveDSPDataRaw(short Channel, LPCTSTR ParaString, short* DataBuffer);
	BOOL ReceiveFile(LPCTSTR FileName, LPCTSTR NewFileName);
	BOOL ReceiveLogFile(LPCTSTR FileName, DATE StartDate, DATE EndDate);
	CString ReceiveMachineConstants(LPCTSTR Names);
	CString ReceiveMemBlock(short Type, short Address, short Count);
	BOOL ReceiveScreen(LPCTSTR FileName);
	CString ReceiveTableLine(LPCTSTR FileName, LPCTSTR SQLQuery, long StartLine);
	BOOL ReConnect();
	BOOL RenameFile(LPCTSTR FileName, LPCTSTR NewFileName);
	BOOL Restore(short Mode, LPCTSTR FileName, LPCTSTR Selection);
	BOOL RunProgram(LPCTSTR ProgramName, short RunMode);
	BOOL SetEventMask(short Mode, short Class, short EventId, short Sender, short Priority, LPCTSTR Type);
	BOOL SetFileTime(LPCTSTR FileName, DATE FileTime);
	BOOL SetOverride(short Type, long Value);
	BOOL SetPreset(long PresetEntry, LPCTSTR PositionMC, LPCTSTR PositionWC, LPCTSTR BaseRotation);
	BOOL TestConnection(short Mode);
	BOOL TransmitChatText(LPCTSTR Text);
	BOOL TransmitDSPString(short Channel, LPCTSTR CommandString);
	BOOL TransmitFile(LPCTSTR FileName, LPCTSTR NewFileName);
	BOOL TransmitGraphicsCommand(short Command, short ServerPort);
	BOOL TransmitKeycode(long Keycode);
	BOOL TransmitMachineConstants(LPCTSTR Names, LPCTSTR Values, long ExecutionFlags);
	BOOL TransmitMemBlock(short Type, short Address, LPCTSTR MemTable);
	BOOL TransmitPlcCommand(long Command);
	BOOL TransmitPlcString(LPCTSTR DataString);
	BOOL TransmitSysCommand(long Command);
	void LogInformation(LPCTSTR InfoString);
	void AboutBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSV2CTL3_H__A5414A94_FEF2_4B8F_8B8A_F4F887FB82D1__INCLUDED_)
