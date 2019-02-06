
// MFCSingleDoc_VehiclesDoc.h : interface of the CMFCSingleDocVehiclesDoc class
//


#pragma once
#include "CVehicleSerialization.h"


class CMFCSingleDocVehiclesDoc : public CDocument
{
protected: // create from serialization only
	CMFCSingleDocVehiclesDoc() noexcept;
	DECLARE_DYNCREATE(CMFCSingleDocVehiclesDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCSingleDocVehiclesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

// custom implementations	
public:
	void AddVehicleToSerialList(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance);
private:
	CList<CVehicleSerialization*, CVehicleSerialization*> m_serialList;
};
