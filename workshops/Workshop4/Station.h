#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <string>
#include <iostream>
#include "Utilities.h"
namespace seneca {

	class Station {
		int m_id = 0;
		std::string m_itemName;
		std::string m_description;
		size_t m_serialNumber = 0;
		size_t m_quantity = 0;

		static size_t m_widthField;
		static int id_generator;

	public:
		//Customer 1-arguement construstor

		Station(const std::string& record);

		const std::string& getItemName() const;

		size_t getNextSerialNumber();

		size_t getQuantity() const;

		void updateQuantity();

		void display(std::ostream& os, bool full) const;
	};
}

#endif