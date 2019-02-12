#pragma once


// CRefuelDlg dialog

class CRefuelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRefuelDlg)

public:
	CRefuelDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRefuelDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RefuelDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Refuel;
};
