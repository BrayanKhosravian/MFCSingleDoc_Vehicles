
// MFCSingleDoc_VehiclesDoc.cpp : implementation of the CMFCSingleDocVehiclesDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCSingleDoc_Vehicles.h"
#endif

#include "MFCSingleDoc_VehiclesDoc.h"

#include <propkey.h>
#include "LeftView.h"
#include "MainFrm.h"
#include "MFCSingleDoc_VehiclesView.h"
#include "CFileManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCSingleDocVehiclesDoc

IMPLEMENT_DYNCREATE(CMFCSingleDocVehiclesDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCSingleDocVehiclesDoc, CDocument)
	
END_MESSAGE_MAP()


// CMFCSingleDocVehiclesDoc construction/destruction

CMFCSingleDocVehiclesDoc::CMFCSingleDocVehiclesDoc() noexcept
{
	// TODO: add one-time construction code here

}

CMFCSingleDocVehiclesDoc::~CMFCSingleDocVehiclesDoc()
{
}

BOOL CMFCSingleDocVehiclesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	auto mainframe = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if(mainframe != NULL)
	{
		auto leftPain = mainframe->GetLeftPane();
		leftPain->clearLeftView();

		auto rightPane = mainframe->GetRightPane();
		rightPane->DeleteListView();
		
	}
	
	return TRUE;
}




// CMFCSingleDocVehiclesDoc serialization

void CMFCSingleDocVehiclesDoc::Serialize(CArchive& ar)
{
	CFileManager fileManager;

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		fileManager.WriteVehiclesToFile(*m_serialList, ar.m_strFileName);

		/*
		m_objectCount = m_serialList->GetSize();
		ar << m_objectCount;

		for(size_t i = 0; i < m_serialList->GetSize(); i++)
		{
			auto position = m_serialList->FindIndex(i);
			m_serialList->GetAt(position)->Serialize(ar);

		}
		*/

	}
	else
	{
		// TODO: add loading code here
		this->OnNewDocument();
		m_serialList->RemoveAll();

		ar >> m_objectCount;

		for (size_t i = 0; i < m_objectCount; i++)
		{
			CVehicle* vehicle = new CVehicle();
			vehicle->Serialize(ar);
			m_serialList->AddTail(vehicle);
			
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCSingleDocVehiclesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCSingleDocVehiclesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCSingleDocVehiclesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}


#endif // SHARED_HANDLERS

// CMFCSingleDocVehiclesDoc diagnostics

#ifdef _DEBUG
void CMFCSingleDocVehiclesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCSingleDocVehiclesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


void CMFCSingleDocVehiclesDoc::AddVehicleToSerialList(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance)
{
	m_serialList->AddTail(new CVehicle(id,name,maxFuelCapacity,fuelUsage,fuelRemaining,drivenDistance));
}

