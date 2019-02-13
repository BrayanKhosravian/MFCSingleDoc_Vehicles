
// MFCSingleDoc_VehiclesView.h : interface of the CMFCSingleDocVehiclesView class
//

#pragma once


class CMFCSingleDocVehiclesView : public CListView
{
protected: // create from serialization only
	CMFCSingleDocVehiclesView() noexcept;
	DECLARE_DYNCREATE(CMFCSingleDocVehiclesView)

// Attributes
public:
	CMFCSingleDocVehiclesDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMFCSingleDocVehiclesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnPrint(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
public:
	void ShowSelectedItemInList(CString id, CString name, CString maxFuelCapacity, CString fuelUsage,
								CString fuelRemaining, CString drivenDistance, CString power, 
								CString serviceInterval, CString isServiceNeeded, CString isFuelRemaining);
	void DeleteAllItems();
	void DeleteListView();

private:
	CListCtrl& m_listCtrl = GetListCtrl();

	//virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
};

#ifndef _DEBUG  // debug version in MFCSingleDoc_VehiclesView.cpp
inline CMFCSingleDocVehiclesDoc* CMFCSingleDocVehiclesView::GetDocument() const
   { return reinterpret_cast<CMFCSingleDocVehiclesDoc*>(m_pDocument); }
#endif

