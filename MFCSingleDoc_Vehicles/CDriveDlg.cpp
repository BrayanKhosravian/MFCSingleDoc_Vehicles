// CDriveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleDoc_Vehicles.h"
#include "CDriveDlg.h"
#include "afxdialogex.h"
// #include "boost/lexical_cast/try_lexical_convert.hpp"
// #include "boost/convert/lexical_cast.hpp"

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

bool CDriveDlg::isValid()
{
	CString message;
	if(m_Distance.IsEmpty())
	{
		message += L"Entry cant be empty! \n";
		AfxMessageBox(message);
		return false;
	}
	/*
	if(!boost::lexical_cast<float>(m_Distance))
	{
		
		message += L"Entry needs to be a floating point type! \n";
		AfxMessageBox(message);
		return false;
	}
	*/
	else return true;
}

void CDriveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Distance, m_Distance);
}


BEGIN_MESSAGE_MAP(CDriveDlg, CDialogEx)
END_MESSAGE_MAP()


// CDriveDlg message handlers
