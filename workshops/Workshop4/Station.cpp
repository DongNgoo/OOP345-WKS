#include "Station.h"
#include <iomanip>
#include <stdexcept>

namespace seneca{
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	//Customer constructor
	Station::Station(const std::string& record) : m_id(++id_generator), m_serialNumber(0), m_quantity(0) {
		seneca::Utilities util;
		size_t next_pos = 0;
		bool more = true;
		try 
		{
			//Extract name of the item
			m_itemName = util.extractToken(record, next_pos, more);

			//Extract the starting serial number
			std::string serial = util.extractToken(record, next_pos, more);
			m_serialNumber = std::stoul(serial);

			//Extract the quanity in stock
			std::string quantity = util.extractToken(record, next_pos, more);
			m_quantity = std::stoul(quantity);
			
			//Extract description
			m_description = util.extractToken(record, next_pos, more);

			//update m_widthField
			if (util.getFieldWidth() > m_widthField) {
				m_widthField = util.getFieldWidth();
			}


		}
		catch (const std::exception& e) {
			throw std::runtime_error("Error parsing station record: " + std::string(e.what()));
		}

	}

	//Return the item name 
	const std::string& Station::getItemName() const {
		return m_itemName;
	}

	//return the next serial number to be used on the assembly line and increments 
	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}

	//return the remaining quantity of items in the Station object
	size_t Station::getQuantity() const {

		return m_quantity;
	}

	//substract 1 from available quantity of items in the Station object;
	void Station::updateQuantity() {
		if (m_quantity > 0) {
			m_quantity--;
		}
	}

	//insert info about the current object into stream os
	void Station::display(std::ostream& os, bool full) const {

		os << std::setw(3) << std::setfill('0') << m_id << "|";
		os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << "|";
		os << std::setw(6) << std::setfill('0') << m_quantity << "|";

		if (full) {
			os << std::setw(4) << std::setfill(' ') << m_quantity << "|";
			os << m_description;
		}

		os << std::endl;

	}



}