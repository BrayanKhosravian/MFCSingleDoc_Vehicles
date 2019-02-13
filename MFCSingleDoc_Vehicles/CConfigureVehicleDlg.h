#pragma once
#include <tuple>


// CConfigureVehicleDlg dialog

class CConfigureVehicleDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigureVehicleDlg)

public:
	CConfigureVehicleDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CConfigureVehicleDlg();
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ConfigureVehicle };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_ID;
	CString m_Name;
	CString m_MaxFuelCapacity;
	CString m_FuelUsage;
	CString m_FuelRemaining;
	CString m_DrivenDistance;
	
	CString m_Power;
	CString m_ServiceInterval;

	BOOL m_IsFuelRemaining;
	BOOL m_IsServiceNeeded;
};
