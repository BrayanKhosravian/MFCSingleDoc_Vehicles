#include "stdafx.h"
#include "CVehicleSerialization.h"

IMPLEMENT_SERIAL(CVehicleSerialization, CObject, 1)

CVehicleSerialization::CVehicleSerialization()
{
}


CVehicleSerialization::~CVehicleSerialization()
{
}

void CVehicleSerialization::Serialize(CArchive& archive)
{
	CObject::Serialize(archive);

	// now do the stuff for our specific class
	if (archive.IsStoring())
		archive << m_id << m_name << m_maxFuelCapacity << m_fuelUsage << m_fuelRemaining << m_drivenDistance;
	else
		archive >> m_id >> m_name >> m_maxFuelCapacity >> m_fuelUsage >> m_fuelRemaining >> m_drivenDistance;
}
