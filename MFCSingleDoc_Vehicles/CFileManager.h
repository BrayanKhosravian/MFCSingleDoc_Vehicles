#pragma once
#include "CVehicle.h"
#include <string>

class CFileManager
{

public:
	CFileManager();
	~CFileManager();

	void WriteVehiclesToFile(CList<CVehicle*, CVehicle*>& vehicles, CString& fileName /*= L"Vehicles.veh"*/);
	CList<CVehicle*, CVehicle*> CreateVehiclesFromFile(const std::string& fileName = "Vehicles.veh");
};

