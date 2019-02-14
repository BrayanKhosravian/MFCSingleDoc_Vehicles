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
	if (m_fuelRemaining > m_maxFuelCapacity) m_fuelRemaining = m_maxFuelCapacity;
}

CVehicle::CVehicle(long id, CString name, int maxFuelCapacity, float fuelUsage, float fuelRemaining, float drivenDistance)
{
	m_id = this->idCounter();
	m_name = name;
	m_maxFuelCapacity = maxFuelCapacity;
	m_fuelUsage = fuelUsage;
	m_fuelRemaining = fuelRemaining;
	m_drivenDistance = drivenDistance;
	if (m_fuelRemaining > m_maxFuelCapacity) m_fuelRemaining = m_maxFuelCapacity;
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
	if (m_fuelRemaining > m_maxFuelCapacity) m_fuelRemaining = m_maxFuelCapacity;
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
	if (m_fuelRemaining > m_maxFuelCapacity) m_fuelRemaining = m_maxFuelCapacity;
}

CVehicle::CVehicle(CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining,
	CString drivenDistance, CString power, CString serviceInterval, CString isServiceNeeded, CString isFuelRemaining)
{
	m_id = this->idCounter();
	m_name = name;
	m_maxFuelCapacity = _wtoi(maxFuelCapacity);
	m_fuelUsage = _wtof(fuelUsage);
	m_fuelRemaining = _wtof(fuelRemaining);
	m_drivenDistance = _wtof(drivenDistance);
	m_power = _wtoi(power);
	m_serviceInterval = _wtoi(serviceInterval);

	if (isServiceNeeded.Find(L"TRUE") != -1) m_isServiceNeeded = true;
	else m_isServiceNeeded = false;
	if (isFuelRemaining.Find(L"TRUE") != -1) m_isFuelRemaining = true;
	else m_isFuelRemaining = false;

	if (m_fuelRemaining > m_maxFuelCapacity) m_fuelRemaining = m_maxFuelCapacity;
}


CVehicle::~CVehicle()
{

}

void CVehicle::doRefuel(float fuel)
{
	m_fuelRemaining += fuel;
	if (m_fuelRemaining > m_maxFuelCapacity)
	{
		m_fuelRemaining = m_maxFuelCapacity;
		AfxMessageBox(L"You refueled too much! the max fuel capacity is: " + convertToCString(m_maxFuelCapacity));
	}
}

void CVehicle::doDrive(float km)
{
	// verbrauch = [Liter / gefahrene km] * 100

	float maxDriveableDistance, fuelUsed;
	CString message;

	if(m_fuelRemaining <= 0)
	{
		m_isFuelRemaining = false;
		m_fuelRemaining = 0;
		message += L">> No fuel remaining. Refuel your vehicle \n";
	}
	else
	{
		maxDriveableDistance = (m_fuelRemaining / m_fuelUsage) * 100;
		fuelUsed = (m_fuelUsage / 100) * km;

		if(km >= maxDriveableDistance)
		{
			m_isFuelRemaining = false;
			m_drivenDistance += maxDriveableDistance;
			m_tempServiceDistance += maxDriveableDistance;
			m_fuelRemaining = 0;
			CString test = convertToCString(maxDriveableDistance);
			message += L">> No fuel remaining. Refuel your vehicle. You only drove: " + convertToCString(maxDriveableDistance) + L"km \n";
		}
		else
		{
			m_isFuelRemaining = true;
			m_drivenDistance += km;
			m_tempServiceDistance += km;
			m_fuelRemaining -= fuelUsed;
		}
	}

	if (m_tempServiceDistance >= m_serviceInterval && m_serviceInterval > 0)
	{
		message += L">> You need to make a service for yor vehicle \n";
		m_isServiceNeeded = true;
	}

	if(!message.IsEmpty()) AfxMessageBox(message);
}

void CVehicle::doService()
{
	m_isServiceNeeded = false;
	m_tempServiceDistance = 0;
}

void CVehicle::setAllMembers(CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining,
	CString drivenDistance, CString power, CString serviceInterval, CString isServiceNeeded, CString isFuelRemaining)
{
	m_name = name;
	m_maxFuelCapacity = _wtoi(maxFuelCapacity);
	m_fuelUsage = _wtof(fuelUsage);
	m_fuelRemaining = _wtof(fuelRemaining);
	m_drivenDistance = _wtof(drivenDistance);
	m_power = _wtoi(power);
	m_serviceInterval = _wtoi(serviceInterval);
	if (isServiceNeeded.Find(L"TRUE") != -1) m_isServiceNeeded = true;
	else m_isServiceNeeded = false;
	if (isFuelRemaining.Find(L"TRUE") != -1 && m_fuelRemaining >= 0) m_isFuelRemaining = true;
	else m_isFuelRemaining = false;
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
