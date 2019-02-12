#include "stdafx.h"
#include "CFileManager.h"
#include "CVehicleCollection.h"
#include <fstream>

using namespace std;

CFileManager::CFileManager()
{
}


CFileManager::~CFileManager()
{
}

void CFileManager::WriteVehiclesToFile(CVehicleCollection& vehicles, CString& fileName)
{
	if(!this->strEndsWith(fileName, L".veh")) fileName += L".veh";
	
	std::fstream stream;
	stream.open(fileName, std::fstream::in | std::fstream::out | std::fstream::trunc);

	stream << "Count of registered vehicles: " << vehicles.GetSize() << "\n" << endl;

	for (size_t i = 0; i < vehicles.GetSize(); i++)
	{
		CVehicle* vehicle = vehicles.GetVehicleWithIndex(i);

		stream.precision(2);
		stream << "Vehicle ID: " << vehicle->getId() << endl;
		stream << "Vehicle Name: " << (CT2CA)vehicle->getName() << endl;
		stream << std::fixed << "Vehicle max fuel capacity in Liter: " << vehicle->getMaxFuelCapacity() << endl;
		stream << std::fixed << "Vehicle fuel usage in Liter: " << vehicle->getFuelUsage() << endl;
		stream << std::fixed << "Vehicle fuel remaining: " << vehicle->getFuelRemaining() << endl;
		stream << std::fixed << "Vehicle driven distance: " << vehicle->getDrivenDistance() << std::endl;
		stream << std::fixed << "Vehicle power: " << vehicle->getPower() << std::endl;
		stream << std::fixed << "Vehicle service interval: " << vehicle->getServiceInterval() << std::endl;
		stream << endl;
	}
	stream.close();
}

CVehicleCollection CFileManager::CreateVehiclesFromFile(CString& fileName)
{
	CVehicleCollection vehicleVector;

	long ID = 0;
	string name;
	int maxFuelCapacity = 0;
	float fuelUsage = 0;
	float fuelRemaining = 0;
	float drivenDistance = 0;
	int power = 0;
	int serviceInterval = 0;

	int i = 0;
	int dataLine = 0;

	std::ifstream inFile(fileName);
	for (std::string line; getline(inFile, line); )
	{
		if (i == 0) { i++; continue; }// skip first line
		if (i == 1) { i++; continue; }// skip second line
		if (line.empty()) { continue; }
		else
		{
			if (dataLine == 0) // get vehicle ID
			{
				string content = line.substr(12, string::npos);
				ID = stol(content);
				dataLine++;
				continue;
			}
			else if (dataLine == 1)	// get vehicle name
			{
				string content = line.substr(14, string::npos);
				name = content;
				dataLine++;
				continue;
			}
			else if (dataLine == 2) // get vehicle max fuel capacity
			{
				string content = line.substr(36, string::npos);
				maxFuelCapacity = stoi(content);
				dataLine++;
				continue;
			}
			else if (dataLine == 3)	// get vehicle fuel usage
			{
				string content = line.substr(29, string::npos);
				fuelUsage = stof(content);
				dataLine++;
				continue;
			}
			else if (dataLine == 4)	// get vehicle fuel remaining
			{
				string content = line.substr(24, string::npos);
				fuelRemaining = stof(content);
				dataLine++;
				continue;
			}
			else if (dataLine == 5)	// get vehicle driven distance
			{
				string content = line.substr(25, string::npos);
				drivenDistance = stof(content);
				dataLine++;
				continue;
			}
			else if (dataLine == 6)	// get vehicle power
			{
				string content = line.substr(15, string::npos);
				power = stoi(content);
				dataLine ++;
				continue;
			}
			else if (dataLine == 7)	// get vehicle power
			{
				string content = line.substr(26, string::npos);
				serviceInterval = stoi(content);
				vehicleVector.AddVehicle(CVehicle((CString)name.c_str(), maxFuelCapacity, fuelUsage, fuelRemaining, drivenDistance, power, serviceInterval));
				dataLine = 0;
				continue;
			}
		}
	}
	inFile.close();
	return vehicleVector;

}

bool CFileManager::strEndsWith(CString& fileName, CString compareWith)
{
	CString temp = fileName.Right(4);
	temp.MakeLower();

	if (temp == compareWith) return true;
	else return false;
}
