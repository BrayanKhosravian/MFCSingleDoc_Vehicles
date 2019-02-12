#pragma once
#include "CVehicleCollection.h"
#include "CVehicle.h"
#include <memory>
#include <vector>


class CVehicleCollection
{
public:
	CVehicleCollection();
	CVehicleCollection(CVehicleCollection &&move) noexcept : m_vehicles(std::move(move.m_vehicles)) {}
	~CVehicleCollection();

	void AddVehicle(CVehicle&& vehicle);
	void DeleteVehicleWithIndex(std::size_t elementAt);
	void DeleteVehicleWithId(long id);
	void EditVehicleWithId(long id);

	// Getters
	CVehicle* GetVehicle(size_t elementAt);
	size_t GetSize();

	// operators
	//CVehicleCollection& operator=(const CVehicleCollection &other);
	CVehicleCollection& operator=(CVehicleCollection &&other);


private:
	std::vector<std::unique_ptr<CVehicle>> m_vehicles;
};

