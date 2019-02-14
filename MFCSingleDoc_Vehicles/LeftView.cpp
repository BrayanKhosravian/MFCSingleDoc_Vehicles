
// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "MFCSingleDoc_Vehicles.h"

#include "MFCSingleDoc_VehiclesDoc.h"
#include "LeftView.h"

#include "CConfigureVehicleDlg.h"
#include "MainFrm.h"
#include "MFCSingleDoc_VehiclesView.h"
#include "CDriveDlg.h"
#include "CServiceDlg.h"
#include "CRefuelDlg.h"

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
	ON_COMMAND(ID_VEHICLEMENU_DRIVE, &CLeftView::OnVehiclemenuDrive)
	ON_COMMAND(ID_VEHICLEMENU_SERVICE, &CLeftView::OnVehiclemenuService)
	ON_COMMAND(ID_VEHICLEMENU_REFUEL, &CLeftView::OnVehiclemenuRefuel)
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

	// m_hItem = m_treeCtrl.InsertItem(L"Vehicle List",2,2, TVI_ROOT);
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

void CLeftView::InsertVehicleToListView(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance, CString power, CString serviceInterval, CString isServiceNeeded, CString isFuelRemaining)
{
	//HICON image = m_ImageList.ExtractIconW(0);
	m_hItem = m_treeCtrl.GetRootItem();
	if (m_hItem == NULL) this->createRootItem();

	m_hCar = m_treeCtrl.InsertItem(L"ID: "			+ id, 0, 0, m_hItem);
	m_treeCtrl.InsertItem(L"Name: "					+ name, 2, 2, m_hCar);
	m_treeCtrl.InsertItem(L"Max fuel capacity: "	+ maxFuelCapacity,2,2, m_hCar);
	m_treeCtrl.InsertItem(L"Fuel usage: "			+ fuelUsage,2,2, m_hCar);
	m_treeCtrl.InsertItem(L"Fuel remaining: "		+ fuelRemaining, 2,2, m_hCar);
	m_treeCtrl.InsertItem(L"Driven distance: "		+ drivenDistance,2,2, m_hCar);
	m_treeCtrl.InsertItem(L"Power: "				+ power, 2, 2, m_hCar);
	m_treeCtrl.InsertItem(L"Service interval: "		+ serviceInterval, 2, 2, m_hCar);
	m_treeCtrl.InsertItem(L"Is service needed? " + isServiceNeeded, 2, 2, m_hCar);
	m_treeCtrl.InsertItem(L"Is fuel remaining? " + isFuelRemaining, 2, 2, m_hCar);



	// auto document = GetDocument();
	// document->AddVehicleToSerialList(id, name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance);
}

void CLeftView::InsertVehicleToListView(CVehicle* vehicle)
{
	CString id, name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance, power, serviceInterval, isServiceNeeded, isFuelRemaining;

	id.Format(L"%d", vehicle->getId());
	name = vehicle->getName();
	maxFuelCapacity.Format(L"%d",vehicle->getMaxFuelCapacity());
	fuelUsage.Format(L"%f", vehicle->getFuelUsage());
	fuelRemaining.Format(L"%f", vehicle->getFuelRemaining());
	drivenDistance.Format(L"%f", vehicle->getDrivenDistance());
	power.Format(L"%d", vehicle->getPower());
	serviceInterval.Format(L"%d", vehicle->getServiceInterval());
	isServiceNeeded = vehicle->getIsServiceNeeded() ? "TRUE" : "FALSE";
	isFuelRemaining = vehicle->getIsFuelRemaining() ? "TRUE" : "FALSE";

	this->InsertVehicleToListView(id, name,maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance, power, serviceInterval, isServiceNeeded, isFuelRemaining);
}

void CLeftView::CreatTreeFromSerialCollection(CVehicleCollection& vehicles)
{
	this->deleteAllChildItems();
	for (size_t i = 0; i < vehicles.GetSize(); i++)
	{
		this->InsertVehicleToListView(vehicles.GetVehicleWithIndex(i));
	}
}

long CLeftView::GetIdFromSelectedItem()
{
	CString idStr = m_treeCtrl.GetItemText(m_selectedItem);
	idStr.Replace(L"ID: ", L"");

	long id = _wtol(idStr);
	return id;
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
	if (m_selectedItem != NULL)
	{
		auto idStr = m_treeCtrl.GetItemText(m_selectedItem);
		idStr.Replace(L"ID: ", L"");
		long id = _wtol(idStr);

		GetDocument()->DeleteVehicleWithId(id);
		m_treeCtrl.DeleteItem(m_selectedItem);

	}
	auto mainFrame = AfxGetApp()->m_pMainWnd;
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	auto rightView = pMainWnd->GetRightPane();

	rightView->DeleteAllItems();

}


void CLeftView::OnVehiclemenuEdit()
{
	CConfigureVehicleDlg configureVehicleDialog;
	CString idStr, name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance, power, serviceInterval, isServiceNeeded, isFuelRemaining;

	idStr = m_treeCtrl.GetItemText(m_selectedItem);
	idStr.Replace(L"ID: ", L"");

	auto firstChild = m_treeCtrl.GetNextItem(m_selectedItem, TVGN_CHILD);
	name = m_treeCtrl.GetItemText(firstChild);
	name.Replace(L"Name: ", L"");

	auto nextChild = m_treeCtrl.GetNextSiblingItem(firstChild);
	maxFuelCapacity = m_treeCtrl.GetItemText(nextChild);
	maxFuelCapacity.Replace(L"Max fuel capacity: ", L"");

	nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
	fuelUsage = m_treeCtrl.GetItemText(nextChild);
	fuelUsage.Replace(L"Fuel usage: ", L"");

	nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
	fuelRemaining = m_treeCtrl.GetItemText(nextChild);
	fuelRemaining.Replace(L"Fuel remaining: ", L"");

	nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
	drivenDistance = m_treeCtrl.GetItemText(nextChild);
	drivenDistance.Replace(L"Driven distance: ", L"");

	nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
	power = m_treeCtrl.GetItemText(nextChild);
	power.Replace(L"Power: ", L"");

	nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
	serviceInterval = m_treeCtrl.GetItemText(nextChild);
	serviceInterval.Replace(L"Service interval: ", L"");

	nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
	isServiceNeeded = m_treeCtrl.GetItemText(nextChild);
	isServiceNeeded.Replace(L"Is service needed? ", L"");

	nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
	isFuelRemaining = m_treeCtrl.GetItemText(nextChild);
	isFuelRemaining.Replace(L"Is fuel remaining? ", L"");

	configureVehicleDialog.m_Name = name;
	configureVehicleDialog.m_ID = idStr;
	configureVehicleDialog.m_MaxFuelCapacity = maxFuelCapacity;
	configureVehicleDialog.m_FuelUsage = fuelUsage;
	configureVehicleDialog.m_FuelRemaining = fuelRemaining;
	configureVehicleDialog.m_DrivenDistance = drivenDistance;
	configureVehicleDialog.m_Power = power;
	configureVehicleDialog.m_ServiceInterval = serviceInterval;
	if (isServiceNeeded.Find(L"TRUE")) configureVehicleDialog.m_IsServiceNeeded = true;
	else configureVehicleDialog.m_IsServiceNeeded = false;
	if (isFuelRemaining.Find(L"TRUE")) configureVehicleDialog.m_IsFuelRemaining = true;
	else configureVehicleDialog.m_IsFuelRemaining = false;

	if(configureVehicleDialog.DoModal() == IDOK)
	{
		m_treeCtrl.DeleteItem(m_selectedItem);
		idStr = configureVehicleDialog.m_ID;
		name = configureVehicleDialog.m_Name;
		maxFuelCapacity = configureVehicleDialog.m_MaxFuelCapacity;
		fuelUsage = configureVehicleDialog.m_FuelUsage;
		fuelRemaining = configureVehicleDialog.m_FuelRemaining;
		drivenDistance = configureVehicleDialog.m_DrivenDistance;
		power = configureVehicleDialog.m_Power;
		serviceInterval = configureVehicleDialog.m_ServiceInterval;

		isServiceNeeded = configureVehicleDialog.m_IsServiceNeeded ? L"TRUE" : L"FALSE";
		if (_wtof(fuelRemaining) <= 0) isFuelRemaining = L"TRUE";
		else isFuelRemaining = L"FALSE";

		this->InsertVehicleToListView(idStr, name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance, power, serviceInterval, isServiceNeeded, isFuelRemaining);

		long id = _wtol(idStr);
		GetDocument()->EditVehicleWithId(id, name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance, power, serviceInterval);

		auto mainFrame = AfxGetApp()->m_pMainWnd;
		CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
		auto rightView = pMainWnd->GetRightPane();
		rightView->ShowSelectedItemInList(idStr, name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance, power, serviceInterval, isServiceNeeded, isFuelRemaining);
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

		CString name, id, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance, power, serviceInterval, isServiceNeeded, isFuelRemaining;

		id = m_treeCtrl.GetItemText(m_selectedItem);
		id.Replace(L"ID: ", L"");

		auto firstChild = m_treeCtrl.GetNextItem(m_selectedItem, TVGN_CHILD);
		name = m_treeCtrl.GetItemText(firstChild);
		name.Replace(L"Name: ", L"");

		auto nextChild = m_treeCtrl.GetNextSiblingItem(firstChild);
		maxFuelCapacity = m_treeCtrl.GetItemText(nextChild);
		maxFuelCapacity.Replace(L"Max fuel capacity: ", L"");

		nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
		fuelUsage = m_treeCtrl.GetItemText(nextChild);
		fuelUsage.Replace(L"Fuel usage: ", L"");

		nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
		fuelRemaining = m_treeCtrl.GetItemText(nextChild);
		fuelRemaining.Replace(L"Fuel remaining: ", L"");

		nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
		drivenDistance = m_treeCtrl.GetItemText(nextChild);
		drivenDistance.Replace(L"Driven distance: ", L"");

		nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
		power = m_treeCtrl.GetItemText(nextChild);
		power.Replace(L"Power: ", L"");

		nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
		serviceInterval = m_treeCtrl.GetItemText(nextChild);
		serviceInterval.Replace(L"Service interval: ", L"");

		nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
		isServiceNeeded = m_treeCtrl.GetItemText(nextChild);
		isServiceNeeded.Replace(L"Is service needed? ", L"");

		nextChild = m_treeCtrl.GetNextSiblingItem(nextChild);
		isFuelRemaining = m_treeCtrl.GetItemText(nextChild);
		isFuelRemaining.Replace(L"Is fuel remaining? ", L"");

		auto mainFrame = AfxGetApp()->m_pMainWnd;
		CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
		auto rightView = pMainWnd->GetRightPane();
		rightView->ShowSelectedItemInList(id,name,maxFuelCapacity,fuelUsage,fuelRemaining,drivenDistance, power, serviceInterval,isServiceNeeded, isFuelRemaining);

	}

	CTreeView::OnLButtonDown(nFlags, point);

}

void CLeftView::deleteAllItems()
{
	m_treeCtrl.DeleteAllItems();
}

void CLeftView::deleteAllChildItems()
{
	if (!m_treeCtrl.GetRootItem()) return;
	// Delete all of the children of hmyItem.
	if (m_treeCtrl.ItemHasChildren(m_hItem))
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = m_treeCtrl.GetChildItem(m_hItem);

		while (hChildItem != NULL)
		{
			hNextItem = m_treeCtrl.GetNextItem(hChildItem, TVGN_NEXT);
			m_treeCtrl.DeleteItem(hChildItem);
			hChildItem = hNextItem;
		}
	}

}

void CLeftView::createRootItem()
{
	m_hItem = m_treeCtrl.InsertItem(L"Vehicle List", 2, 2, TVI_ROOT);
}


void CLeftView::updateVehicleCollectionInDoc(CVehicleCollection& vehicles)
{
	// refresh vehicle collection
	this->CreatTreeFromSerialCollection(vehicles);
	GetDocument()->SetVehicleCollection(std::move(vehicles));
}

void CLeftView::deleteRightViewItems()
{
	// delete rightview items because unselected the item
	auto mainFrame = (CMainFrame*)AfxGetMainWnd();
	auto rightPane = mainFrame->GetRightPane();
	rightPane->DeleteAllItems();
}

void CLeftView::OnVehiclemenuDrive()
{
	gotoWrongInput:
	CDriveDlg driveDlg;
	if(driveDlg.DoModal() == IDOK)
	{
		if (!driveDlg.isValid()) goto gotoWrongInput;

		long id = this->GetIdFromSelectedItem();
		auto vehicles = GetDocument()->GetVehicleColltection();
		vehicles.GetVehicleWithId(id)->doDrive(_wtof(driveDlg.m_Distance));

		this->updateVehicleCollectionInDoc(vehicles);
		this->deleteRightViewItems();
	}
}


void CLeftView::OnVehiclemenuService()
{
	CServiceDlg serviceDlg;
	if(serviceDlg.DoModal() == IDOK)
	{
		long id = this->GetIdFromSelectedItem();
		auto vehicles = GetDocument()->GetVehicleColltection();
		vehicles.GetVehicleWithId(id)->doService();

		this->updateVehicleCollectionInDoc(vehicles);
		this->deleteRightViewItems();
	}
}


void CLeftView::OnVehiclemenuRefuel()
{
	CRefuelDlg refuelDlg;
	if(refuelDlg.DoModal() == IDOK)
	{
		long id = this->GetIdFromSelectedItem();
		auto vehicles = GetDocument()->GetVehicleColltection();
		vehicles.GetVehicleWithId(id)->doRefuel(_wtof(refuelDlg.m_Refuel));

		this->updateVehicleCollectionInDoc(vehicles);
		this->deleteRightViewItems();
	}
}
