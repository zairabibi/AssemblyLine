#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <string>
#include "Station.h"

namespace sdds
{
	class CustomerOrder
	{
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

		//instance variables
		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item** m_lstItem;

		static size_t m_widthField;
		size_t countItems(std::string);

	public:
		CustomerOrder();
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder &c);
		CustomerOrder& operator= (const CustomerOrder &c) = delete;
		CustomerOrder(CustomerOrder&& c) noexcept;
		CustomerOrder& operator = (CustomerOrder &&c) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;


	};

}

#endif


