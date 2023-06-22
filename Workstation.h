#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <iostream>
#include <string>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds
{
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation{ nullptr };

	public:

		Workstation(const std::string &str);

		//deleted copy and move operations
		Workstation(const Workstation &c) = delete;
		Workstation& operator= (const Workstation &c) = delete;
		Workstation(Workstation&& c) = delete;
		Workstation& operator = (Workstation &&c) = delete;

		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};
}

#endif


