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

void CVehicleCollection::DeleteVehicle(std::size_t elementAt)
{
	m_vehicles.erase(m_vehicles.begin() + elementAt);
}

CVehicle* CVehicleCollection::GetVehicle(size_t elementAt)
{
	auto x = m_vehicles.at(elementAt).get();
	return x;
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
