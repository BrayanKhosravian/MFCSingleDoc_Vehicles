#pragma once


// CServiceDlg dialog

class CServiceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServiceDlg)

public:
	CServiceDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CServiceDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ServiceDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
