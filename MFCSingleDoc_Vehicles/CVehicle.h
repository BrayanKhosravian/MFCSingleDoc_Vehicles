#pragma once
class CVehicle : public CObject
{
public:
	DECLARE_SERIAL(CVehicle)
	CVehicle();
	CVehicle(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, 
						  CString fuelRemaining, CString drivenDistance);
	virtual ~CVehicle();

	virtual void Serialize(CArchive& archive);

protected:

private:
	CString m_id, m_name, m_maxFuelCapacity, m_fuelUsage, m_fuelRemaining, m_drivenDistance;
};

