
// LeftView.h : interface of the CLeftView class
//


#pragma once

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
	afx_msg void OnToolsAddvehicle();

public:
	void InsertVehicleToListView(CString id, CString name, CString maxFuelCapacity, CString fuelUsage,
								 CString fuelRemaining, CString drivenDistance);

private:
	CTreeCtrl& m_tree = GetTreeCtrl();
	HTREEITEM m_hItem;
	HTREEITEM m_hCar;
	CString m_ID;
	CString m_Name;
	CString m_MaxFuelCapacity;
	CString m_FuelUsage;
	CString m_FuelRemaining;
	CString m_DrivenDistance;

};


#ifndef _DEBUG  // debug version in LeftView.cpp
inline CMFCSingleDocVehiclesDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CMFCSingleDocVehiclesDoc*>(m_pDocument); }
#endif

