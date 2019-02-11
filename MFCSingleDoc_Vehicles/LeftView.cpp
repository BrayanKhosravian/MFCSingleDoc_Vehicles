
// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "MFCSingleDoc_Vehicles.h"

#include "MFCSingleDoc_VehiclesDoc.h"
#include "LeftView.h"

#include "CConfigureVehicleDlg.h"
#include "MainFrm.h"
#include "MFCSingleDoc_VehiclesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	
	ON_NOTIFY_REFLECT(NM_RCLICK, &CLeftView::OnNMRClick)
	ON_COMMAND(ID_VEHICLEMENU_DELETE, &CLeftView::OnVehiclemenuDelete)
	ON_COMMAND(ID_VEHICLEMENU_EDIT, &CLeftView::OnVehiclemenuEdit)
	ON_WM_LBUTTONDOWN()
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

	if(m_ImageList == NULL)
	{
		m_ImageList.Create(16, 16, ILC_MASK, 0, 4);
		m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
		m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
		m_treeCtrl.SetImageList(&m_ImageList, TVSIL_NORMAL);
	}
	
	m_hItem = m_treeCtrl.InsertItem(L"Vehicle List",2,2, TVI_ROOT);
	// this->InsertVehicleToListView(L"1", L"Mustang", L"0", L"0", L"0", L"0"); // debug

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
	//HICON image = m_ImageList.ExtractIconW(0);
	
	m_hCar = m_treeCtrl.InsertItem(L"ID: " + id		+ " Name: " + name,0,0 ,m_hItem);
	m_treeCtrl.InsertItem(L"Max fuel capacity: "	+ maxFuelCapacity,2,2, m_hCar);
	m_treeCtrl.InsertItem(L"Fuel usage: "			+ fuelUsage,2,2, m_hCar);
	m_treeCtrl.InsertItem(L"Fuel remaining: "		+ fuelRemaining, 2,2, m_hCar);
	m_treeCtrl.InsertItem(L"Driven distance: "		+ drivenDistance,2,2, m_hCar);

	auto document = GetDocument();
	document->AddVehicleToSerialList(id, name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance);
}


void CLeftView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint ptMouse, ptPopup;
	POINT sMouse;
	UINT uFlags;

	// Get the mouse position relative to the tree view.
	::GetCursorPos(&sMouse);
	ptMouse = sMouse;
	ptPopup = ptMouse;
	ScreenToClient(&ptMouse);

	// Find the item it is over (ignore if not over label or bitmap), and 
	// select it as if we had clicked it with the left mouse button.
	m_selectedItem = m_treeCtrl.HitTest(ptMouse, &uFlags);

	// check if root item is selected item // it it is root item return
	HTREEITEM rootItem = m_treeCtrl.GetRootItem();
	if (rootItem == m_selectedItem) { pResult = 0;  return; }

	if (m_selectedItem != NULL && (uFlags & TVHT_ONITEM))
	{
		m_treeCtrl.SelectItem(m_selectedItem);

		// Id is not included its not a child of root // returns
		if (m_treeCtrl.GetItemText(m_selectedItem).Find(L"ID")) 
		{
			AfxMessageBox(L"Select a root entry!");
			*pResult = 0;
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
	if(m_selectedItem != NULL) m_treeCtrl.DeleteItem(m_selectedItem);

	auto mainFrame = AfxGetApp()->m_pMainWnd;
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	auto rightView = pMainWnd->GetRightPane();

	rightView->DeleteAllItems();

}


void CLeftView::OnVehiclemenuEdit()
{
	CConfigureVehicleDlg configureVehicleDialog;
	CString name, id, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance;

	CString nameAndID = m_treeCtrl.GetItemText(m_selectedItem);
	int pos = nameAndID.Find(L"Name: ");
	name = nameAndID.Mid(pos+6);
	nameAndID.Delete(pos, nameAndID.GetLength() - pos);
	nameAndID.Delete(0, 4);
	id = nameAndID;

	auto firstChild = m_treeCtrl.GetNextItem(m_selectedItem, TVGN_CHILD);
	maxFuelCapacity = m_treeCtrl.GetItemText(firstChild);
	maxFuelCapacity.Replace(L"Max fuel capacity:", L"");

	auto nextChild = m_treeCtrl.GetNextSiblingItem(firstChild);
	fuelUsage = m_treeCtrl.GetItemText(nextChild);
	fuelUsage.Replace(L"Fuel usage: ", L"");

	nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
	fuelRemaining = m_treeCtrl.GetItemText(nextChild);
	fuelRemaining.Replace(L"Fuel remaining: ", L"");

	nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
	drivenDistance = m_treeCtrl.GetItemText(nextChild);
	drivenDistance.Replace(L"Driven distance: ", L"");

	configureVehicleDialog.m_Name = name;
	configureVehicleDialog.m_ID = id;
	configureVehicleDialog.m_MaxFuelCapacity = maxFuelCapacity;
	configureVehicleDialog.m_FuelUsage = fuelUsage;
	configureVehicleDialog.m_FuelRemaining = fuelRemaining;
	configureVehicleDialog.m_DrivenDistance = drivenDistance;

	if(configureVehicleDialog.DoModal() == IDOK)
	{
		m_treeCtrl.DeleteItem(m_selectedItem);
		id = configureVehicleDialog.m_ID;
		name = configureVehicleDialog.m_Name;
		maxFuelCapacity = configureVehicleDialog.m_MaxFuelCapacity;
		fuelUsage = configureVehicleDialog.m_FuelUsage;
		fuelRemaining = configureVehicleDialog.m_FuelRemaining;
		drivenDistance = configureVehicleDialog.m_DrivenDistance;
		this->InsertVehicleToListView(id, name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance);

		auto mainFrame = AfxGetApp()->m_pMainWnd;
		CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
		auto rightView = pMainWnd->GetRightPane();
		rightView->ShowSelectedItemInList(id, name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance);
	}
}


void CLeftView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPoint ptMouse, ptPopup;
	POINT sMouse;
	UINT uFlags;

	// Get the mouse position relative to the tree view.
	::GetCursorPos(&sMouse);
	ptMouse = sMouse;
	ptPopup = ptMouse;
	ScreenToClient(&ptMouse);

	// Find the item it is over (ignore if not over label or bitmap), and 
	// select it as if we had clicked it with the left mouse button.
	m_selectedItem = m_treeCtrl.HitTest(ptMouse, &uFlags);

	// check if root item is selected item // it it is root item return
	HTREEITEM rootItem = m_treeCtrl.GetRootItem();
	if (rootItem == m_selectedItem) { return; }

	if (m_selectedItem != NULL && (uFlags & TVHT_ONITEM))
	{
		m_treeCtrl.SelectItem(m_selectedItem);

		// Id is not included its not a child of root // returns
		if (m_treeCtrl.GetItemText(m_selectedItem).Find(L"ID")) { return; }

		CString name, id, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance;

		CString nameAndID = m_treeCtrl.GetItemText(m_selectedItem);
		int pos = nameAndID.Find(L"Name: ");
		name = nameAndID.Mid(pos + 6);
		nameAndID.Delete(pos, nameAndID.GetLength() - pos);
		nameAndID.Delete(0, 4);
		id = nameAndID;

		auto firstChild = m_treeCtrl.GetNextItem(m_selectedItem, TVGN_CHILD);
		maxFuelCapacity = m_treeCtrl.GetItemText(firstChild);
		maxFuelCapacity.Replace(L"Max fuel capacity:", L"");

		auto nextChild = m_treeCtrl.GetNextSiblingItem(firstChild);
		fuelUsage = m_treeCtrl.GetItemText(nextChild);
		fuelUsage.Replace(L"Fuel usage: ", L"");

		nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
		fuelRemaining = m_treeCtrl.GetItemText(nextChild);
		fuelRemaining.Replace(L"Fuel remaining: ", L"");

		nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
		drivenDistance = m_treeCtrl.GetItemText(nextChild);
		drivenDistance.Replace(L"Driven distance: ", L"");

		auto mainFrame = AfxGetApp()->m_pMainWnd;
		CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
		auto rightView = pMainWnd->GetRightPane();
		rightView->ShowSelectedItemInList(id,name,maxFuelCapacity,fuelUsage,fuelRemaining,drivenDistance);

	}

	CTreeView::OnLButtonDown(nFlags, point);

}

void CLeftView::clearLeftView()
{
	m_treeCtrl.DeleteAllItems();
}
