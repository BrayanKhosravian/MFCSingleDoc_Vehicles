#pragma once


// CDriveDlg dialog

class CDriveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDriveDlg)

public:
	CDriveDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDriveDlg();
	bool isValid();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DriveDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Distance;
};
