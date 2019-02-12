#pragma once
#include "CVehicle.h"
#include <string>

class CVehicleCollection;

class CFileManager
{

public:
	CFileManager();
	~CFileManager();

	void WriteVehiclesToFile(CVehicleCollection& vehicles, CString& fileName /*= L"Vehicles.veh"*/);
	CVehicleCollection CreateVehiclesFromFile(CString& fileName /* = "Vehicles.veh")*/);

private:
	bool strEndsWith(CString& fileName, CString compareWith);

	
};

