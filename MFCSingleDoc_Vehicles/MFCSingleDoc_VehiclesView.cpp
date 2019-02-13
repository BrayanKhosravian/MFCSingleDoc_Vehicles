
// MFCSingleDoc_VehiclesView.cpp : implementation of the CMFCSingleDocVehiclesView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCSingleDoc_Vehicles.h"
#endif

#include "MFCSingleDoc_VehiclesDoc.h"
#include "MFCSingleDoc_VehiclesView.h"
#include "CConfigureVehicleDlg.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSingleDocVehiclesView

IMPLEMENT_DYNCREATE(CMFCSingleDocVehiclesView, CListView)

BEGIN_MESSAGE_MAP(CMFCSingleDocVehiclesView, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_MESSAGE(WM_PRINT, OnPrint)
END_MESSAGE_MAP()

// CMFCSingleDocVehiclesView construction/destruction

CMFCSingleDocVehiclesView::CMFCSingleDocVehiclesView() noexcept
{
	// TODO: add construction code here

}

CMFCSingleDocVehiclesView::~CMFCSingleDocVehiclesView()
{
}

BOOL CMFCSingleDocVehiclesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CMFCSingleDocVehiclesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// set styles
	m_listCtrl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES);
	
	// Insert columns
	m_listCtrl.InsertColumn(0, L"ID", LVCFMT_LEFT, -1, 0);
	m_listCtrl.InsertColumn(1, L"Name", LVCFMT_LEFT, -1, 1);
	m_listCtrl.InsertColumn(2, L"Max fuel capacity", LVCFMT_LEFT, -1, 2);
	m_listCtrl.InsertColumn(3, L"Fuel usage", LVCFMT_LEFT, -1, 3);
	m_listCtrl.InsertColumn(4, L"Fuel remaining", LVCFMT_LEFT, -1, 4);
	m_listCtrl.InsertColumn(5, L"Driven distance", LVCFMT_LEFT, -1, 5);
	m_listCtrl.InsertColumn(6, L"Power", LVCFMT_LEFT, -1, 6);
	m_listCtrl.InsertColumn(7, L"Service interval", LVCFMT_LEFT, -1, 7);
	m_listCtrl.InsertColumn(8, L"Is service needed?", LVCFMT_LEFT, -4, 8);
	m_listCtrl.InsertColumn(9, L"Is fuel remaining?", LVCFMT_LEFT, -4, 9);

	// set with
	m_listCtrl.SetColumnWidth(0, 80);
	m_listCtrl.SetColumnWidth(1, 80);
	m_listCtrl.SetColumnWidth(2, 120);
	m_listCtrl.SetColumnWidth(3, 120);
	m_listCtrl.SetColumnWidth(4, 120);
	m_listCtrl.SetColumnWidth(5, 120);
	m_listCtrl.SetColumnWidth(6, 120);
	m_listCtrl.SetColumnWidth(7, 120);
	m_listCtrl.SetColumnWidth(8, 40);
	m_listCtrl.SetColumnWidth(9, 40);

	
	
	/*// Insert second row
	index = m_listCtrl.InsertItem(LVIF_TEXT, 1, L"2", 0, 0, 0, NULL);
	m_listCtrl.SetItem(index, 1, LVIF_TEXT, L"2", 0, 0, 0, NULL);

	index = m_listCtrl.InsertItem(LVIF_TEXT, 2, L"3", 0, 0, 0, NULL);
	m_listCtrl.SetItem(index, 1, LVIF_TEXT, L"3", 0, 0, 0, NULL);

	// Set column widths (an optional nice touch)
	m_listCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE);
	m_listCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE);
	*/
	

	//listCtrl.SetItemCount(500);
	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

void CMFCSingleDocVehiclesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCSingleDocVehiclesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

LRESULT CMFCSingleDocVehiclesView::OnPrint(WPARAM wp, LPARAM lp)
{
	CDC* dc = CDC::FromHandle((HDC)wp);

	return Default();
}

void CMFCSingleDocVehiclesView::ShowSelectedItemInList(CString id, CString name, CString maxFuelCapacity, 
													   CString fuelUsage, CString fuelRemaining, 
													   CString drivenDistance, CString power, CString serviceInterval, CString isServiceNeeded, CString isFuelRemaning)
{
	m_listCtrl.DeleteAllItems();

	// insert item
	int index;
	index = m_listCtrl.InsertItem(LVIF_TEXT, 0, id, 0, 0, 0, NULL);				// ID
	m_listCtrl.SetItem(index, 1, LVIF_TEXT, name, 0, 0, 0, NULL);				// name
	m_listCtrl.SetItem(index, 2, LVIF_TEXT, maxFuelCapacity, 0, 0, 0, NULL);	// max fuel capacity
	m_listCtrl.SetItem(index, 3, LVIF_TEXT, fuelUsage, 0, 0, 0, NULL);			// fuel usage
	m_listCtrl.SetItem(index, 4, LVIF_TEXT, fuelRemaining, 0, 0, 0, NULL);		// fuel remaining
	m_listCtrl.SetItem(index, 5, LVIF_TEXT, drivenDistance, 0, 0, 0, NULL);		// driven distance
	m_listCtrl.SetItem(index, 6, LVIF_TEXT, power, 0, 0, 0, NULL);				// power
	m_listCtrl.SetItem(index, 7, LVIF_TEXT, serviceInterval, 0, 0, 0, NULL);	// service intervall
	m_listCtrl.SetItem(index, 8, LVIF_TEXT, isServiceNeeded, 0, 0, 0, NULL);
	m_listCtrl.SetItem(index, 9, LVIF_TEXT, isFuelRemaning, 0, 0, 0, NULL);
}

void CMFCSingleDocVehiclesView::DeleteAllItems()
{
	m_listCtrl.DeleteAllItems();
}

void CMFCSingleDocVehiclesView::DeleteListView()
{
	this->DeleteAllItems();
	int nColumnCount = m_listCtrl.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_listCtrl.DeleteColumn(0);
	}
}


// CMFCSingleDocVehiclesView diagnostics

#ifdef _DEBUG
void CMFCSingleDocVehiclesView::AssertValid() const
{
	CListView::AssertValid();
}

void CMFCSingleDocVehiclesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMFCSingleDocVehiclesDoc* CMFCSingleDocVehiclesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSingleDocVehiclesDoc)));
	return (CMFCSingleDocVehiclesDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCSingleDocVehiclesView message handlers
void CMFCSingleDocVehiclesView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
	CListView::OnStyleChanged(nStyleType, lpStyleStruct);
}





