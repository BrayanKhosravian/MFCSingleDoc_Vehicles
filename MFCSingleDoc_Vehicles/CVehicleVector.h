#pragma once
#include "CVehicle.h"
#include <vector>
#include <memory>


class CVehicleVector
{
	CVehicleVector();
	CVehicleVector(CVehicleVector &&move) noexcept : m_vehicles(std::move(move.m_vehicles)) {}
	~CVehicleVector();

	void AddVehicle(CVehicle&& vehicle);
	void DeleteVehicle(std::size_t elementAt);
	void ListVehicle(std::size_t elementAt);

	// Getters
	CVehicle* GetVehicle(size_t elementAt);
	size_t GetSize();

	// print for debug
	void PrintVectorSize();
	void PrintVehicleNames();
	void PrintVehicleIDs();

	// test
	void CVehicleVector2Test();

private:
	std::vector<std::unique_ptr<CVehicle>> m_vehicles;


};

