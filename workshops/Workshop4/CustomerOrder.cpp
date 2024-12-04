#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
namespace seneca {

	size_t CustomerOrder::m_widthField = 0;

	//Default construsterS
	CustomerOrder::CustomerOrder() {}

	//Customer constructor
	CustomerOrder::CustomerOrder(const std::string& record) {
		Utilities ut;
		size_t next_pos = 0;
		bool more = false;
		m_name = ut.extractToken(record, next_pos, more);
		if (more) {
			m_product = ut.extractToken(record, next_pos, more);
		}
		if (more) {
			m_cntItem = std::count(record.begin(), record.end(), ut.getDelimiter()) - 1;
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; ++i) {
				m_lstItem[i] = new Item(ut.extractToken(record, next_pos, more));
			}
		}
		if (m_widthField < ut.getFieldWidth()) {
			m_widthField = ut.getFieldWidth();
		}
	}


	//Destructor
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	CustomerOrder::CustomerOrder(const CustomerOrder&)
	{
		throw std::string("ERROR: Cannot make copies.");
	}

	//Move constructor
	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
		*this = std::move(other);
	}

	//Move assignment operator
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
		if (this != &other) {


			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;


			m_name = other.m_name;
			m_product = other.m_product;
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;

			other.m_lstItem = nullptr;
			other.m_cntItem = 0;

		}

		return *this;
	}



	//Check if order is filled
	bool CustomerOrder::isOrderFilled() const {
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;
			}
		}

		return true;
	}

	//Check if a specific item is filled

	/*bool CustomerOrder::isItemFilled(const std::string& itemName) const {

		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}*/

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {

		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	//Fill an item in the order
	/*void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "Filled " << m_name << ", " << m_product << " ["
						<< m_lstItem[i]->m_itemName << "]\n";
				}
				else {
					os << "Unable to fill " << m_name << ", " << m_product << " ["
						<< m_lstItem[i]->m_itemName << "]\n";
				}
				return;
			}
		}
	}*/


	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; ++i) {

			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {

				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					os << "    Filled " << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				return;  // Stop processing after handling one item
			}
		}
	}





	//Display the order
	void CustomerOrder::display(std::ostream& os) const {


		os << m_name << " - " << m_product << '\n';
		for (size_t i = 0; i < m_cntItem; ++i) {
			Utilities::trim(m_lstItem[i]->m_itemName);

		}

		for (size_t i = 0; i < m_cntItem; ++i) {

			// Format the output as per the required specifications
			Utilities::trim(m_lstItem[i]->m_itemName);


			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< std::left << std::setw(m_widthField - 1) << std::setfill(' ')
				<< m_lstItem[i]->m_itemName
				<< "- " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << "\n";



		}
	}

}