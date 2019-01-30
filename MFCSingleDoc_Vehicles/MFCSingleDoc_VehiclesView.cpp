
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
	//ON_COMMAND(ID_TOOLS_ADDVEHICLE, &CMFCSingleDocVehiclesView::OnToolsAddvehicle)
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

//
//void CMFCSingleDocVehiclesView::OnToolsAddvehicle()
//{
//	CConfigureVehicleDlg addVehicleDlg;
//	if(addVehicleDlg.DoModal() == IDOK)
//	{
//
//		// InsertVehicleToListView(L"test",L"1",L"2", L"3", L"4", L"5");
//	}
//}
