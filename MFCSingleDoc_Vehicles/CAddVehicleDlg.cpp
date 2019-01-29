// CAddVehicleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleDoc_Vehicles.h"
#include "CAddVehicleDlg.h"
#include "afxdialogex.h"


// CAddVehicleDlg dialog

IMPLEMENT_DYNAMIC(CAddVehicleDlg, CDialog)

CAddVehicleDlg::CAddVehicleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_AddVehicle, pParent)
	, m_ID(_T(""))
	, m_Name(_T(""))
	, m_MaxFuelCapacity(_T(""))
	, m_FuelUsage(_T(""))
	, m_FuelRemaining(_T(""))
	, m_DrivenDistance(_T(""))
{

}

CAddVehicleDlg::~CAddVehicleDlg()
{
}

void CAddVehicleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_ID);
	DDX_Text(pDX, IDC_EDIT_Name, m_Name);
	DDX_Text(pDX, IDC_EDIT_MaxFuelCapacity, m_MaxFuelCapacity);
	DDX_Text(pDX, IDC_EDIT_FuelUsage, m_FuelUsage);
	DDX_Text(pDX, IDC_EDIT_FuelRemaining, m_FuelRemaining);
	DDX_Text(pDX, IDC_EDIT_DrivenDistance, m_DrivenDistance);
}


BEGIN_MESSAGE_MAP(CAddVehicleDlg, CDialog)
END_MESSAGE_MAP()


// CAddVehicleDlg message handlers
