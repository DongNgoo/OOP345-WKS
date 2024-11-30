#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation = nullptr;

	public:

		//Customer construsctor

		Workstation(const std::string& name);

		// Deleted copy and move operations
		Workstation(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		//Member function
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;

		//Overload operator
		Workstation& operator+=(CustomerOrder&& newOrder);
	};

}
#endif