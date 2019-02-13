// CConfigureVehicleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleDoc_Vehicles.h"
#include "afxdialogex.h"
#include "CConfigureVehicleDlg.h"


// CConfigureVehicleDlg dialog

IMPLEMENT_DYNAMIC(CConfigureVehicleDlg, CDialog)

CConfigureVehicleDlg::CConfigureVehicleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ConfigureVehicle, pParent)
	, m_ID(_T(""))
	, m_Name(_T(""))
	, m_MaxFuelCapacity(_T(""))
	, m_FuelUsage(_T(""))
	, m_FuelRemaining(_T(""))
	, m_DrivenDistance(_T(""))
	, m_Power(_T(""))
	, m_ServiceInterval(_T(""))
	, m_IsFuelRemaining(FALSE)
	, m_IsServiceNeeded(FALSE)
{

}

CConfigureVehicleDlg::~CConfigureVehicleDlg()
{
}



void CConfigureVehicleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_ID);
	DDX_Text(pDX, IDC_EDIT_Name, m_Name);
	DDX_Text(pDX, IDC_EDIT_MaxFuelCapacity, m_MaxFuelCapacity);
	DDX_Text(pDX, IDC_EDIT_FuelUsage, m_FuelUsage);
	DDX_Text(pDX, IDC_EDIT_FuelRemaining, m_FuelRemaining);
	DDX_Text(pDX, IDC_EDIT_DrivenDistance, m_DrivenDistance);
	DDX_Text(pDX, IDC_EDIT_Power, m_Power);
	DDX_Text(pDX, IDC_EDIT_ServiceInterval, m_ServiceInterval);
	DDX_Check(pDX, IDC_CHECK_IsFuelRemaining, m_IsFuelRemaining);
	DDX_Check(pDX, IDC_CHECK_IsServiceNeeded, m_IsServiceNeeded);
}


BEGIN_MESSAGE_MAP(CConfigureVehicleDlg, CDialog)
END_MESSAGE_MAP()


// CConfigureVehicleDlg message handlers
