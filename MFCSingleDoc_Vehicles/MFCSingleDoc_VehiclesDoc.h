
// MFCSingleDoc_VehiclesDoc.h : interface of the CMFCSingleDocVehiclesDoc class
//


#pragma once
#include "CVehicle.h"
#include "CVehicleCollection.h"


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
	// methods
	void AddVehicleToSerialList(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance);
	void DeleteVehicleWithId(long id);
	void EditVehicleWithId(long id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance, CString power, CString serviceInterval, CString isServiceNeeded, CString isFuelRemaining);

	// getters
	CVehicleCollection GetVehicleColltection() { return std::move(m_serialCollection); }

	// setters
	void SetVehicleCollection(CVehicleCollection vehicles) { m_serialCollection = std::move(vehicles); }

	//CList<CVehicle*, CVehicle*>* getSerialList() const { return m_serialCollection; }

private:
	// CList<CVehicle*, CVehicle*>* m_serialCollection = new CList<CVehicle*, CVehicle*>;
	CVehicleCollection m_serialCollection;
	size_t m_objectCount = 0;
public:
	afx_msg void OnToolsAddvehicle();

};
