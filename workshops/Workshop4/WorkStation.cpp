#include "Workstation.h"

namespace seneca {

    // Global queues
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    // Custom constructor
    Workstation::Workstation(const std::string& name) : Station(name) {}

    //Fill the order at the front of the queue
    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }
    //Attempt to move the order at the front of the queue to the next station
    bool Workstation::attemptToMoveOrder() {

        if (m_orders.empty()) return false;

        if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
            if (m_pNextStation) {
                //Move to the next station 
                *m_pNextStation += std::move(m_orders.front());

            }
            else {
                //Determine if order is complete
                if (m_orders.front().isOrderFilled()) {
                    g_completed.push_back(std::move(m_orders.front()));
                }
                else {
                    g_incomplete.push_back(std::move(m_orders.front()));
                }
            }
            m_orders.pop_front();
            return true;

        }
        return false;

    }

    //Set next station
    void Workstation::setNextStation(Workstation* station) {

        m_pNextStation = station;
    }

   //Get the station
    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    //display
    void Workstation::display(std::ostream& os) const {

        os << getItemName() << " --> ";
        if (m_pNextStation) {
            os << m_pNextStation->getItemName();
        }
        else {
            os << "End of Line";
        }
        os << '\n';
    }

    //Add a new order to the back of the queue
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }


}