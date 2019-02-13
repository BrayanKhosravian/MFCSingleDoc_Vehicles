#include "stdafx.h"
#include "CVehicle.h"
#include <string>

// IMPLEMENT_SERIAL(CVehicle, CObject, 1)

using namespace std;

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
	m_id = this->idCounter();
	m_name = name;
	m_maxFuelCapacity = maxFuelCapacity;
	m_fuelUsage = fuelUsage;
	m_fuelRemaining = fuelRemaining;
	m_drivenDistance = drivenDistance;
}

CVehicle::CVehicle(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining,
	CString drivenDistance)
{
	m_id = this->idCounter();
	m_name = name;
	m_maxFuelCapacity = _wtoi(maxFuelCapacity);
	m_fuelUsage = _wtof(fuelUsage);
	m_fuelRemaining = _wtof(fuelRemaining);
	m_drivenDistance = _wtof(drivenDistance);
}

CVehicle::CVehicle(CString name, int maxFuelCapacity, float fuelUsage, float fuelRemaining, float drivenDistance,
	int power, int serviceInterval)
{
	m_id = this->idCounter();
	m_name = name;
	m_maxFuelCapacity = maxFuelCapacity;
	m_fuelUsage = fuelUsage;
	m_fuelRemaining = fuelRemaining;
	m_drivenDistance = drivenDistance;
	m_power = power;
	m_serviceInterval = serviceInterval;
}

CVehicle::CVehicle(CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining,
	CString drivenDistance, CString power, CString serviceInterval)
{
	m_id = this->idCounter();
	m_name = name;
	m_maxFuelCapacity = _wtoi(maxFuelCapacity);
	m_fuelUsage = _wtof(fuelUsage);
	m_fuelRemaining = _wtof(fuelRemaining);
	m_drivenDistance = _wtof(drivenDistance);
	m_power = _wtoi(power);
	m_serviceInterval = _wtoi(serviceInterval);
}


CVehicle::~CVehicle()
{
}

void CVehicle::doReFuel(float fuel)
{
	m_fuelRemaining += fuel;
	if (m_fuelRemaining > m_maxFuelCapacity) m_fuelRemaining = m_maxFuelCapacity;
}

void CVehicle::doDrive(float km)
{
	float maxDriveableDistance, fuelUsed;
	CString message;

	if (m_serviceInterval >= m_tempServiceDistance) message += L"You need to make a service for yor vehicle \n";

	if(m_fuelRemaining <= 0)
	{
		m_isFuelRemaining = false;
		m_fuelRemaining = 0;
		message += ("No fuel remaining. Refuel your vehicle");
	}
	else
	{
		maxDriveableDistance = m_fuelUsage / m_fuelRemaining * 100;
		fuelUsed = m_fuelUsage * 100 * km;

		if(km >= maxDriveableDistance)
		{
			m_isFuelRemaining = false;
			m_drivenDistance += maxDriveableDistance;
			m_tempServiceDistance += maxDriveableDistance;
			m_fuelRemaining = 0;
			CString test = convertToCString(maxDriveableDistance);
			message += L"No fuel remaining. Refuel your vehicle. You only drove: " + convertToCString(maxDriveableDistance) + L"km";
		}
		else
		{
			m_isFuelRemaining = true;
			m_drivenDistance += km;
			m_tempServiceDistance += km;
			m_fuelRemaining -= fuelUsed;
		}
	}

	AfxMessageBox(message);
}

void CVehicle::doService()
{
	m_isServiceNeeded = false;
	m_tempServiceDistance = 0;
}

void CVehicle::setAllMembers(CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining,
	CString drivenDistance, CString power, CString serviceInterval)
{
	m_name = name;
	m_maxFuelCapacity = _wtoi(maxFuelCapacity);
	m_fuelUsage = _wtof(fuelUsage);
	m_fuelRemaining = _wtof(fuelRemaining);
	m_drivenDistance = _wtof(drivenDistance);
	m_power = _wtoi(power);
	m_serviceInterval = _wtoi(serviceInterval);
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
