#pragma once
class CVehicle : public CObject
{
public:
	DECLARE_SERIAL(CVehicle)
	CVehicle();
	CVehicle(CString name, int maxFuelCapacity, float fuelUsage, float fuelRemaining, float drivenDistance);
	CVehicle(CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance);
	CVehicle(long id, CString name, int maxFuelCapacity, float fuelUsage, float fuelRemaining, float drivenDistance);
	CVehicle(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance);
	virtual ~CVehicle();

	virtual void Serialize(CArchive& archive);

	// methods
	void reFuel(float fuel);
	void drive(float km);

	// setters
	void setID(long id);
	void setName(const CString& name);
	void setMaxFuelCapacity(int maxFuelCapacity);
	void setFuelUsage(float fuelUsage);

	// getters
	long getId() const { return m_id; }
	CString& getName() { return m_name; }
	int getMaxFuelCapacity() const { return m_maxFuelCapacity; }
	float getFuelUsage() const { return m_fuelUsage; }
	float getFuelRemaining() const { return m_fuelRemaining; }
	float getDrivenDistance() const { return m_drivenDistance; }

protected:

private:
	// fields
	long m_id;
	CString m_name;
	int m_maxFuelCapacity;
	float m_fuelUsage, m_fuelRemaining, m_drivenDistance;

	// methods
	long idCounter()
	{
		static std::size_t n = 0;
		return  n++;
	}
};

