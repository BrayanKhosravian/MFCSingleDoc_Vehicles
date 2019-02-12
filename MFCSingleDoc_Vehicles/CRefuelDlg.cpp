// CRefuelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleDoc_Vehicles.h"
#include "CRefuelDlg.h"
#include "afxdialogex.h"


// CRefuelDlg dialog

IMPLEMENT_DYNAMIC(CRefuelDlg, CDialogEx)

CRefuelDlg::CRefuelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RefuelDlg, pParent)
	, m_Refuel(_T(""))
{

}

CRefuelDlg::~CRefuelDlg()
{
}

void CRefuelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Refuel, m_Refuel);
}


BEGIN_MESSAGE_MAP(CRefuelDlg, CDialogEx)
END_MESSAGE_MAP()


// CRefuelDlg message handlers
