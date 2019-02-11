#include "stdafx.h"
#include "CFileManager.h"
#include <fstream>

using namespace std;

CFileManager::CFileManager()
{
}


CFileManager::~CFileManager()
{
}

void CFileManager::WriteVehiclesToFile(CList<CVehicle*, CVehicle*>& vehicles, CString& fileName)
{
	fileName += L".veh";

	std::fstream stream;
	stream.open(fileName, std::fstream::in | std::fstream::out | std::fstream::trunc);

	stream << "Count of registered vehicles: " << vehicles.GetSize() << "\n" << endl;

	for (size_t i = 0; i < vehicles.GetSize(); i++)
	{
		CVehicle* vehicle = vehicles.GetAt(vehicles.FindIndex(i));

		stream.precision(2);
		stream << "Vehicle ID: " << vehicle->getId() << endl;
		stream << "Vehicle Name: " << (CT2CA)vehicle->getName() << endl;
		stream << std::fixed << "Vehicle max fuel capacity in Liter: " << vehicle->getMaxFuelCapacity() << endl;
		stream << std::fixed << "Vehicle fuel usage in Liter: " << vehicle->getFuelUsage() << endl;
		stream << std::fixed << "Vehicle fuel remaining: " << vehicle->getFuelRemaining() << endl;
		stream << std::fixed << "Vehicle driven distance: " << vehicle->getDrivenDistance() << std::endl;
		stream << endl;
	}
	stream.close();
}
