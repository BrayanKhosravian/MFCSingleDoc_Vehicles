#pragma once
class CVehicleSerialization : public CObject
{
public:
	DECLARE_SERIAL(CVehicleSerialization)
	CVehicleSerialization();
	virtual ~CVehicleSerialization();

	virtual void Serialize(CArchive& archive);

	CString m_id, m_name, m_maxFuelCapacity, m_fuelUsage, m_fuelRemaining, m_drivenDistance;
protected:

private:
};

