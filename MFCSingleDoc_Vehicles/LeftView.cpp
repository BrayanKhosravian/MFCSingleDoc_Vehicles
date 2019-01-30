
// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "MFCSingleDoc_Vehicles.h"

#include "MFCSingleDoc_VehiclesDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	
	ON_NOTIFY_REFLECT(NM_RCLICK, &CLeftView::OnNMRClick)
	ON_COMMAND(ID_VEHICLEMENU_DELETE, &CLeftView::OnVehiclemenuDelete)
	ON_COMMAND(ID_VEHICLEMENU_EDIT, &CLeftView::OnVehiclemenuEdit)
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


// custom implementations

void CLeftView::InsertVehicleToListView(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance)
{
	m_hCar = m_tree.InsertItem(L"ID: " + id		+ " Name: " + name, m_hItem);
	m_tree.InsertItem(L"Max fuel capacitiy: "	+ maxFuelCapacity, m_hCar);
	m_tree.InsertItem(L"Fuel usage: "			+ fuelUsage, m_hCar);
	m_tree.InsertItem(L"Fuel remaining: "		+ fuelRemaining, m_hCar);
	m_tree.InsertItem(L"Driven distance: "		+ drivenDistance, m_hCar);
}


void CLeftView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint ptMouse, ptPopup;
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	POINT sMouse;
	UINT uFlags;

	// Get the mouse position relative to the tree view.
	::GetCursorPos(&sMouse);
	ptMouse = sMouse;
	ptPopup = ptMouse;
	ScreenToClient(&ptMouse);

	// Find the item it is over (ignore if not over label or bitmap), and 
	// select it as if we had clicked it with the left mouse button.
	m_selectedItem = treeCtrl.HitTest(ptMouse, &uFlags);

	// check if root item is selected item // it it is root item return
	HTREEITEM rootItem = treeCtrl.GetRootItem();
	if (rootItem == m_selectedItem) return;

	if (m_selectedItem != NULL && (uFlags & TVHT_ONITEM))
	{
		treeCtrl.SelectItem(m_selectedItem);

		// Id is not included its not a child of root // returns
		if (treeCtrl.GetItemText(m_selectedItem).Find(L"ID")) 
		{
			AfxMessageBox(L"Select a root entry!");
			return;
		}
		
		//if you want to popup menu this below: 
		CMenu menu;
		// menu.LoadMenu(IDR_MAINFRAME);
		menu.LoadMenu(IDR_VehicleMenu);
		CMenu* pMenu = menu.GetSubMenu(0);
		// Display the popup menu. pMenu is the menu to use, pWnd is the 
		// window to receive the WM_COMMAND messages from the menu.
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, ptPopup.x,
			ptPopup.y, this, 0);
	}

	*pResult = 0;
}

void CLeftView::OnVehiclemenuDelete()
{
	if(m_selectedItem != NULL) m_tree.DeleteItem(m_selectedItem);
}


void CLeftView::OnVehiclemenuEdit()
{
	// TODO: Add your command handler code here
}
