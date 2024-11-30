#include "Workstation.h"

namespace seneca {

    // Global queues
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    // Custom constructor
    Workstation::Workstation(const std::string& name) : Station(name), m_pNextStation(nullptr) {}


    //Fill the order at the front of the queue
    void Workstation::fill(std::ostream& os) {
       /* if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }*/
        if (!m_orders.empty()) {
            // Try to fill the item for the order at the front
            auto& order = m_orders.front();
            
                order.fillItem(*this, os);
            
        
        }
        
    }
    //Attempt to move the order at the front of the queue to the next station
    bool Workstation::attemptToMoveOrder() {
        //if (!m_orders.empty()) {
        //    // If the order at the front is either filled or cannot be filled at this station
        //    if (m_orders.front().isOrderFilled() || !m_orders.front().isItemFilled(getItemName())) {
        //        if (m_pNextStation) {
        //            // Pass to the next station
        //            *m_pNextStation += std::move(m_orders.front());
        //        }
        //        else {
        //            // No next station, move to completed or incomplete queue
        //             if (m_orders.front().isOrderFilled()) {
        //                g_completed.push_back(std::move(m_orders.front()));
        //            }
        //            else {
        //                g_incomplete.push_back(std::move(m_orders.front()));
        //            }
        //        }
        //        m_orders.pop_front(); // Remove the order from this station's queue
        //        return true;
        //    }
        //}
        //return false;
        if (!m_orders.empty()) {
            auto& currentOrder = m_orders.front();

            // Check if the current station's item is filled or if the item cannot be filled
            if (currentOrder.isItemFilled(getItemName()) || getQuantity() == 0) {
                if (m_pNextStation) {
                    // Move to the next station
                    *m_pNextStation += std::move(currentOrder);
                }
                else {
                    // No next station, move to the appropriate global queue
                    if (currentOrder.isOrderFilled()) {
                        g_completed.push_back(std::move(currentOrder));
                    }
                    else {
                        g_incomplete.push_back(std::move(currentOrder));
                    }
                }
                // Remove from the current station's queue
                m_orders.pop_front();
                return true;
            }
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