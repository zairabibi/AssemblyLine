#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds
{
	int Station::id_generator = 0;
	size_t Station::m_widthField = 0;

	Station::Station(const std::string& str)
	{
		Utilities util; //local Utilities object

		//local variables for extractToken function
		size_t pos = 0u;
		bool more = true;

		//temp string
		std::string temp;

		//storing id
		id_generator++;
		m_id = id_generator;

		//extracting name
		m_itemName = util.extractToken(str, pos, more);

		//extracting serial number
		temp = util.extractToken(str, pos, more);
		m_serialNumber = std::stoi(temp);

		//extracting quantity
		temp = util.extractToken(str, pos, more);
		m_quantity = std::stoi(temp);

		//setting field width to the maximum 
		if (m_widthField < util.getFieldWidth())
			m_widthField = util.getFieldWidth();

		//extracting description
		m_description = util.extractToken(str, pos, more);

	}

	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}

	size_t Station::getNextSerialNumber()
	{
		return (m_serialNumber++);
	}

	size_t Station::getQuantity() const
	{
		return m_quantity;
	}

	void Station::updateQuantity()
	{
		if (m_quantity > 0)
			m_quantity = m_quantity - 1;
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setw(3) << std::setfill('0') << std::right << m_id << " | ";
		os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << "  | ";
		os << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";


		if (full)
			os << std::setw(4) << std::setfill(' ') << std::right << m_quantity << " | " << m_description;
		

		os << std::endl;
	}
}