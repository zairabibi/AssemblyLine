#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"


namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder()
	{
		m_cntItem = 0;
		m_name = "";
		m_product = "";
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities util;

		size_t pos = 0u;
		bool more = true;

		m_name = util.extractToken(str, pos, more);
		m_product = util.extractToken(str, pos, more);

		m_cntItem = countItems(str);
		m_lstItem = new Item*[m_cntItem];
		size_t items = 0;

		while (more)
		{
			m_lstItem[items] = new Item(util.extractToken(str, pos, more));
			items++;
		}


		if (m_widthField < util.getFieldWidth())
			CustomerOrder::m_widthField = util.getFieldWidth();

	}

	size_t CustomerOrder::countItems(std::string str)
	{
		size_t count = 0;

		Utilities util;
		bool more = true;
		size_t pos = 0u;
		while (more)
		{
			util.extractToken(str, pos, more);
			count++;
		}
		return (count - 2);
	}

	CustomerOrder::CustomerOrder(const CustomerOrder &c)
	{
		throw std::string("Exception from Copy Constructor\n");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& c) noexcept
	{
		//assigning c to current object
		this->m_name = c.m_name;
		this->m_product = c.m_product;

		this->m_cntItem = c.m_cntItem;
		this->m_lstItem = c.m_lstItem;

		c.m_name = "";
		c.m_product = "";
		c.m_lstItem = nullptr;
		c.m_cntItem = 0;
	}

	CustomerOrder& CustomerOrder::operator = (CustomerOrder &&c) noexcept
	{

		//assigning c to current object
		this->m_name = c.m_name;
		this->m_product = c.m_product;

		//deleting previous memory
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItem[i];

		delete[] m_lstItem;

		this->m_cntItem = c.m_cntItem;
		this->m_lstItem = c.m_lstItem;

		c.m_name = "";
		c.m_product = "";
		c.m_lstItem = nullptr;
		c.m_cntItem = 0;
		

		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}

		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool filled = false;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_isFilled)
				filled = true;
			else
			{
				filled = false;
				break;
			}
		}
		return filled;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool filled = false, found = false;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
				found = true;
		}

		if (!found)
			filled = true;
		else
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				if (m_lstItem[i]->m_itemName == itemName)
				{
					filled = m_lstItem[i]->m_isFilled;
				}
			}
		}

		return filled;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!(m_lstItem[i]->m_isFilled))
			{
				if (station.getItemName() == m_lstItem[i]->m_itemName)
				{
					if (station.getQuantity() > 0)
					{
						station.updateQuantity();
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						m_lstItem[i]->m_isFilled = true;

						os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					}
					else
						os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;

					if (m_lstItem[i]->m_isFilled)
						break;
				}

			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << "   - ";
			if (m_lstItem[i]->m_isFilled)
				os << "FILLED";
			else
				os << "TO BE FILLED";
			os << std::endl;
		}
	}


}
