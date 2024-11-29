#include "CustomerOrder.h"
#include <iomanip>
#include <algorithm>
#include <vector>
namespace seneca{
	
	size_t CustomerOrder::m_widthField = 0;
	
	//Default construsterS
	CustomerOrder::CustomerOrder() {}

	//Customer constructor
	CustomerOrder::CustomerOrder(const std::string& record) {
		Utilities util;
		size_t next_pos = 0;
		bool more = true;

		//Extract Customer name

		m_name = util.extractToken(record, next_pos, more);
		//Product name
		m_product = util.extractToken(record, next_pos, more);

		//Extract item names and populate the array
		std::vector<std::string> items;
		while (more) {
			items.push_back(util.extractToken(record, next_pos, more));
		}

		m_cntItem = items.size();
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(items[i]);
		}

		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}
	}
		//Move constructor
		CustomerOrder::CustomerOrder(CustomerOrder && other) noexcept {
			*this = std::move(other);
		}

		//Move assignment operator
		CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
			if (this != &other) {
				if (m_lstItem) {

					for (size_t i = 0; i < m_cntItem; ++i) {
						delete m_lstItem[i];
					}
					delete[] m_lstItem;
				}

				m_name = std::move(other.m_name);
				m_product = std::move(other.m_product);
				m_cntItem = other.m_cntItem;
				m_lstItem = other.m_lstItem;

				other.m_lstItem = nullptr;
				other.m_cntItem = 0;

			}

			return *this;
		}

		//Destructor

		CustomerOrder::~CustomerOrder() {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
		}

		//Check if order is filled
		bool CustomerOrder::isOrderFilled() const {
			for (size_t i = 0; i < m_cntItem; ++i) {
				if (!m_lstItem[i]->m_isFilled) return false;
			}

			return true;
		}

		//Check if a specific item is filled

		bool CustomerOrder::isItemFilled(const std::string& itemName) const {
			for (size_t i = 0; i < m_cntItem; ++i) {
				if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
					return false;
				}
			}
			return true;
		}

		//Fill an item in the order
		void CustomerOrder::fillItem(Station& station, std::ostream& os) {

			for (size_t i = 0; i < m_cntItem; ++i) {
				if (m_lstItem[i]->m_itemName == station.getItemName()) {

					if (station.getQuantity() > 0) {
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();

						m_lstItem[i]->m_isFilled = true;
						station.updateQuantity();
						os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
					}
					else {
						os << "Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
					}
					
				}
			}
		}
	
		//Display the order
	   void CustomerOrder::display(std::ostream& os) const {
		  os << m_name << " - " << m_product << '\n';
		 for (size_t i = 0; i < m_cntItem; ++i) {
	  		os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
					<< std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - "
					<< (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << '\n';
			}
		}


}