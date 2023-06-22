#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
#include <string>
#include <cstddef>

namespace sdds
{
	class Station
	{
		int m_id;
		std::string m_itemName;
		std::string m_description;
		unsigned m_serialNumber;
		unsigned m_quantity;

		static size_t m_widthField;
		static int id_generator;

	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

}

#endif


