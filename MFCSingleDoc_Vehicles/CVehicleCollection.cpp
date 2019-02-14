#include "stdafx.h"
#include "CVehicleCollection.h"
#include <memory>
#include <iostream>


CVehicleCollection::CVehicleCollection()
{
}


CVehicleCollection::~CVehicleCollection()
{
}

void CVehicleCollection::AddVehicle(CVehicle&& vehicle)
{
	m_vehicles.push_back(std::make_unique<CVehicle>(vehicle));
}

void CVehicleCollection::DeleteVehicleWithIndex(std::size_t elementAt)
{
	m_vehicles.erase(m_vehicles.begin() + elementAt);
}

void CVehicleCollection::DeleteVehicleWithId(long id)
{
	for (size_t i = 0; i < m_vehicles.size(); i++)
	{
		if (m_vehicles.at(i)->getId() == id)
		{
			this->DeleteVehicleWithIndex(i);
			return;
		}
	}
	assert(false);
}

void CVehicleCollection::EditVehicleWithId(long id, CString name, CString maxFuelCapacity, CString fuelUsage,
	CString fuelRemaining, CString drivenDistance, CString power, CString serviceInterval, CString isServiceNeeded, CString isFuelRemaining)
{
	auto vehicle = this->GetVehicleWithId(id);
	vehicle->setAllMembers(name, maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance, power, serviceInterval, isServiceNeeded, isFuelRemaining);
}

CVehicle* CVehicleCollection::GetVehicleWithIndex(size_t elementAt)
{
	auto x = m_vehicles.at(elementAt).get();
	return x;
}

CVehicle* CVehicleCollection::GetVehicleWithId(long id)
{
	for (size_t i = 0; i < m_vehicles.size(); i++)
	{
		if (m_vehicles.at(i)->getId() == id)
		{
			return m_vehicles.at(i).get();
		}
	}
	assert(false);
}

size_t CVehicleCollection::GetSize()
{
	return m_vehicles.size();
}

/*
CVehicleCollection& CVehicleCollection::operator=(const CVehicleCollection &other)
{
	std::swap(m_vehicles, other.m_vehicles);
	return *this;
}
*/
CVehicleCollection& CVehicleCollection::operator=(CVehicleCollection&& other)
{
	std::swap(m_vehicles, other.m_vehicles);
	return *this;
}
