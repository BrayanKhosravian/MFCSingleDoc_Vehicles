#include "stdafx.h"
#include "CVehicle.h"

// IMPLEMENT_SERIAL(CVehicle, CObject, 1)

CVehicle::CVehicle()
{
	m_id = this->idCounter();
}

CVehicle::CVehicle(CString name, int maxFuelCapacity, float fuelUsage, float fuelRemaining, float drivenDistance)
{
	m_id = this->idCounter();
	m_name = name;
	m_maxFuelCapacity = maxFuelCapacity;
	m_fuelUsage = fuelUsage;
	m_fuelRemaining = fuelRemaining;
	m_drivenDistance = drivenDistance;
}

CVehicle::CVehicle(long id, CString name, int maxFuelCapacity, float fuelUsage, float fuelRemaining, float drivenDistance)
{
	m_id = id;
	m_name = name;
	m_maxFuelCapacity = maxFuelCapacity;
	m_fuelUsage = fuelUsage;
	m_fuelRemaining = fuelRemaining;
	m_drivenDistance = drivenDistance;
}

CVehicle::CVehicle(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining,
	CString drivenDistance)
{
	m_id = _wtol(id);
	m_name = name;
	m_maxFuelCapacity = _wtoi(maxFuelCapacity);
	m_fuelUsage = _wtof(fuelUsage);
	m_fuelRemaining = _wtof(fuelRemaining);
	m_drivenDistance = _wtof(drivenDistance);
}


CVehicle::~CVehicle()
{
}
//
//void CVehicle::Serialize(CArchive& archive)
//{
//	// CObject::Serialize(archive);
//
//	if (archive.IsStoring())
//		archive << m_id << m_name << m_maxFuelCapacity << m_fuelUsage << m_fuelRemaining << m_drivenDistance;
//	else
//		archive >> m_id >> m_name >> m_maxFuelCapacity >> m_fuelUsage >> m_fuelRemaining >> m_drivenDistance;
//}
