
// LeftView.h : interface of the CLeftView class
//


#pragma once
#include "CVehicle.h"
#include "CVehicleCollection.h"

class CMFCSingleDocVehiclesDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CMFCSingleDocVehiclesDoc* GetDocument();
	//CLeftView();

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	
// Custom Implementations
public:

public:
	void InsertVehicleToListView(CString id, CString name, CString maxFuelCapacity, CString fuelUsage,
								 CString fuelRemaining, CString drivenDistance, CString power, CString serviceInterval);
	void InsertVehicleToListView(CVehicle* vehicle);
	void CreatTreeFromSerialCollection(CVehicleCollection& vehicles);

private:
	void SaveDataToFields();

	CTreeCtrl& m_treeCtrl = GetTreeCtrl();
	HTREEITEM m_hItem;
	HTREEITEM m_hCar;
	HTREEITEM m_selectedItem;
	CImageList m_ImageList;

	CString m_ID;
	CString m_Name;
	CString m_MaxFuelCapacity;
	CString m_FuelUsage;
	CString m_FuelRemaining;
	CString m_DrivenDistance;


public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVehiclemenuDelete();
	afx_msg void OnVehiclemenuEdit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void deleteAllItems();
	void deleteAllChildItems();
	void createRootItem();
};


#ifndef _DEBUG  // debug version in LeftView.cpp
inline CMFCSingleDocVehiclesDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CMFCSingleDocVehiclesDoc*>(m_pDocument); }
#endif

