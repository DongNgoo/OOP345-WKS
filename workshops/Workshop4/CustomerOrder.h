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
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{ 0 };
		Item** m_lstItem{ nullptr };
		static size_t m_widthField;

	public:
		//Default Constructor
		CustomerOrder();

		//Customer Constructor - 1 argument
		CustomerOrder(const std::string& record);

		//Destructor
	    ~CustomerOrder();

		/**********PROF****************/
		//copy constructor
		// CustomerOrder(const CustomerOrder&) = delete;
		// Should be....
		CustomerOrder(const CustomerOrder&);
		
		//Copy assignment constructor
		CustomerOrder& operator=(const CustomerOrder&) = delete;
	
		//Move construstor
		CustomerOrder(CustomerOrder&& other) noexcept;
		
		//Move Assignment Operator
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;

	


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
