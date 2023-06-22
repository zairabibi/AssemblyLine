#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "LineManager.h"

namespace sdds
{
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::ifstream f(file);

		try
		{
			while (f.good())
			{
				std::string line, s, ns;

				std::getline(f, line);
				std::stringstream separator(line);
				std::getline(separator, s, '|');
				std::getline(separator, ns, '\n');

				if (!ns.empty())
				{
					//using STL algorithm to set next station;
					std::for_each(stations.begin(), stations.end(), [=](Workstation* x)
					{
						if (x->getItemName() == s)
						{
							std::for_each(stations.begin(), stations.end(), [=, &x](Workstation* y)
							{
								if (y->getItemName() == ns)
									x->setNextStation(y);
							});
						}

					});
				}


				//using STL algorithm to push work stations into activeLine
				std::for_each(stations.begin(), stations.end(), [=](Workstation* x)
				{
					if (x->getItemName() == s)
					{
						m_activeLine.push_back(x);
						
					}
				});

			}

			m_firstStation = m_activeLine[4];
			m_cntCustomerOrder = g_pending.size();
		}

		catch (...)
		{
			std::cout << "ERROR" << std::endl;
		}
	}

	void LineManager::reorderStations()
	{
		m_activeLine.insert(m_activeLine.begin(), m_activeLine[4]);
		m_activeLine.erase(m_activeLine.begin() + 5);

		for (size_t x = 0; x < m_activeLine.size(); x++)
		{
			for (size_t y = 1; y < m_activeLine.size(); y++)
			{

				if (m_activeLine[x]->getNextStation())
				{
					if (m_activeLine[x]->getNextStation()->getItemName() == m_activeLine[y]->getItemName())
					{
						auto it = m_activeLine.begin() + (x + 1);
						size_t pos = y;
						m_activeLine.insert(it, m_activeLine[y]);
						m_activeLine.erase(m_activeLine.begin() + pos + 1);
						break;
					}
				}
			}
		}
	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t iteration = 0;

		os << "Line Manager Iteration: " << iteration + 1 << std::endl;
		if (!g_pending.empty())
		{
			(*m_firstStation).operator+=(std::move(g_pending.front()));
			g_pending.pop_front();
		}

		for (auto i = m_activeLine.begin(); i != m_activeLine.end(); i++)
		{
			(*i)->fill(os);
		}

		for (auto i = m_activeLine.begin(); i != m_activeLine.end(); i++)
		{
			(*i)->attemptToMoveOrder();
		}

		iteration++;

		//check if all orders have been processed
		if (g_pending.empty() && g_completed.size() + g_incomplete.size() == m_cntCustomerOrder)
			return true;

		return false;
	}

	void LineManager::display(std::ostream& os) const
	{
		std::vector<Workstation*>::const_iterator i;
		for (i = m_activeLine.begin(); i != m_activeLine.end(); i++)
		{
			(*i)->display(os);
		}
	}
}
