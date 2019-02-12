// CDriveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleDoc_Vehicles.h"
#include "CDriveDlg.h"
#include "afxdialogex.h"


// CDriveDlg dialog

IMPLEMENT_DYNAMIC(CDriveDlg, CDialogEx)

CDriveDlg::CDriveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DriveDlg, pParent)
	, m_Distance(_T(""))
{

}

CDriveDlg::~CDriveDlg()
{
}

void CDriveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Distance, m_Distance);
}


BEGIN_MESSAGE_MAP(CDriveDlg, CDialogEx)
END_MESSAGE_MAP()


// CDriveDlg message handlers
