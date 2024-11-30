#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Station.h"
#include "Utilities.h"

namespace seneca {
	
	class CustomerOrder {

		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};
		std::string m_name;
		std::string m_product;
		size_t m_cntItem{ 0 };
		Item** m_lstItem{ nullptr };
		static size_t m_widthField;

	public:
		//Default Customer
		CustomerOrder();

		//Customer coddnstructor
		CustomerOrder(const std::string& record);


		//No copy constructor
		CustomerOrder(const CustomerOrder&) {
			throw std::runtime_error("Copy constructor is not allowed.");
		}
		//Move construstor
		CustomerOrder(CustomerOrder&& other) noexcept;
		
		//Move Assignment Operator
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;

		//Destructor
		~CustomerOrder();


		/*CustomerOrder(const CustomerOrder& other) = delete;
		CustomerOrder& operator=(const CustomerOrder& other) = delete; */
		 
		
		
		//copy constructor
		/*CustomerOrder(const CustomerOrder& other);*/
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};

}

#endif
