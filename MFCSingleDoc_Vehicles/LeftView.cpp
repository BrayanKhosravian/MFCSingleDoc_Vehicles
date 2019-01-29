
// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "MFCSingleDoc_Vehicles.h"

#include "MFCSingleDoc_VehiclesDoc.h"
#include "LeftView.h"
#include "CAddVehicleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_COMMAND(ID_TOOLS_ADDVEHICLE, &CLeftView::OnToolsAddvehicle)
END_MESSAGE_MAP()


// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	
	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
	
	m_hItem = m_tree.InsertItem(L"Car List", TVI_ROOT);
	
}


// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}


CMFCSingleDocVehiclesDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSingleDocVehiclesDoc)));
	return (CMFCSingleDocVehiclesDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView message handlers
 
void CLeftView::OnToolsAddvehicle()
{
	CAddVehicleDlg addVehicleDlg;
	if (addVehicleDlg.DoModal() == IDOK)
	{
		m_ID = addVehicleDlg.m_ID;
		m_Name = addVehicleDlg.m_Name;
		m_MaxFuelCapacity = addVehicleDlg.m_MaxFuelCapacity;
		m_FuelUsage = addVehicleDlg.m_FuelUsage;
		m_FuelRemaining = addVehicleDlg.m_FuelRemaining;
		m_DrivenDistance = addVehicleDlg.m_DrivenDistance;

		InsertVehicleToListView(m_ID, m_Name, m_MaxFuelCapacity, m_FuelUsage, m_FuelRemaining, m_DrivenDistance);
	}
}

void CLeftView::InsertVehicleToListView(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance)
{
	m_hCar = m_tree.InsertItem(L"ID: " + id		+ " Name: " + name, m_hItem);
	m_tree.InsertItem(L"Max fuel capacitiy: "	+ maxFuelCapacity, m_hCar);
	m_tree.InsertItem(L"Fuel usage: "			+ fuelUsage, m_hCar);
	m_tree.InsertItem(L"Fuel remaining: "		+ fuelRemaining, m_hCar);
	m_tree.InsertItem(L"Driven distance: "		+ drivenDistance, m_hCar);
}
