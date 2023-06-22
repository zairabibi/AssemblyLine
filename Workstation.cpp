#include "Workstation.h"

namespace sdds
{

	Workstation::Workstation(const std::string &str) :Station(str) {}

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			CustomerOrder &o = m_orders.front();
			o.fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool moved = false;

		if (!m_orders.empty())
		{
			CustomerOrder &o = m_orders.front();

			if (o.isItemFilled(this->getItemName()))
			{
				if (m_pNextStation)
					m_pNextStation->m_orders.push_back(std::move(o));
				else if (o.isOrderFilled())
					g_completed.push_back(std::move(o));
				else
					g_incomplete.push_back(std::move(o));

				moved = true;
				m_orders.pop_front();
			}
			else if (this->getQuantity() < 1)
			{
				if (m_pNextStation)
					m_pNextStation->m_orders.push_back(std::move(o));
				else
					g_incomplete.push_back(std::move(o));

				moved = true;
				m_orders.pop_front();
			}
		}

		return moved;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> ";
		if (!m_pNextStation)
			os << "End of Line";
		else
			os << getNextStation()->getItemName();
		os << std::endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}
