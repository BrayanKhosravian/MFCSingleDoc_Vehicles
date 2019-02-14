#pragma once
class CVehicle
{
public:
	// DECLARE_SERIAL(CVehicle)
	CVehicle();
	CVehicle(CString name, int maxFuelCapacity, float fuelUsage, float fuelRemaining, float drivenDistance);
	CVehicle(CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance);
	CVehicle(long id, CString name, int maxFuelCapacity, float fuelUsage, float fuelRemaining, float drivenDistance);
	CVehicle(CString id, CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance);
	CVehicle(CString name, int maxFuelCapacity, float fuelUsage, float fuelRemaining, float drivenDistance, int power, int serviceInterval);
	CVehicle(CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance, CString power, CString serviceInterval, CString isServiceNeeded, CString isFuelRemaining);
	~CVehicle();

	// virtual void Serialize(CArchive& archive);

	// methods
	void doRefuel(float fuel);
	void doDrive(float km);
	void doService();

	// setters
	void setID(long id);
	void setName(const CString& name);
	void setMaxFuelCapacity(int maxFuelCapacity);
	void setFuelUsage(float fuelUsage);
	void setAllMembers(CString name, CString maxFuelCapacity, CString fuelUsage, CString fuelRemaining, CString drivenDistance, CString power, CString serviceInterval, CString isServiceNeeded, CString isFuelRemaining);
	void setIsFuelRemaining(const bool isFuelRemaining) { m_isFuelRemaining = isFuelRemaining; }
	void setIsServiceNeeded(const bool isServiceNeeded) { m_isServiceNeeded = isServiceNeeded; }

	// getters
	long getId() const { return m_id; }
	CString& getName() { return m_name; }
	int getMaxFuelCapacity() const { return m_maxFuelCapacity; }
	int getPower() const { return m_power; }
	int getServiceInterval() const { return m_serviceInterval; }
	float getFuelUsage() const { return m_fuelUsage; }
	float getFuelRemaining() const { return m_fuelRemaining; }
	float getDrivenDistance() const { return m_drivenDistance; }
	bool getIsFuelRemaining() const { return m_isFuelRemaining; }
	bool getIsServiceNeeded() const { return m_isServiceNeeded; }

protected:

private:
	// fields
	long m_id = 0;
	CString m_name = L"";
	int m_maxFuelCapacity, m_power, m_serviceInterval = 0;
	float m_fuelUsage, m_fuelRemaining, m_drivenDistance , m_tempServiceDistance = 0.00f;
	bool m_isFuelRemaining, m_isServiceNeeded = false;

	// methods
	long idCounter()
	{
		static std::size_t n = 0;
		return  n++;
	}

	template<typename T>
	inline CString convertToCString(T toConvert)
	{
		static_assert(std::is_arithmetic_v<T>, "Method CVehicle::convertToCString only uses arithmetic types as parameter");
		
		CString output;
		if(std::is_floating_point_v<T>) output.Format(_T("%f"), toConvert);
		else if(std::is_integral_v<T>) output.Format(_T("%d"), toConvert);

		return output;
	}
};

