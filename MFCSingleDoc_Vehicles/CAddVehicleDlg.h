#pragma once


// CAddVehicleDlg dialog

class CAddVehicleDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddVehicleDlg)

public:
	CAddVehicleDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddVehicleDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddVehicle };
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
};
