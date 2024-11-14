#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include "mediaItem.h"
#include <iostream>
#include <iomanip>
#include "settings.h"
namespace seneca 
{

	class Book : public MediaItem {
	private:
		std::string m_author;
		std::string m_country;
		double m_price;
		// Private constructor (only accessible within the class)
		Book(const std::string& author, const std::string& title, const std::string& country,
			double price, unsigned short year, const std::string& summary)
			: MediaItem(title, summary, year),
			m_author(author), m_country(country), m_price(price) { }

		/*	Book(const std::string& author, const std::string& title, const std::string& country,
			double price, int year, const std::string& summary)
			: MediaItem(title, year, summary), 
			m_author(author), m_country(country), m_price(price) {}*/
	public:
		void display(std::ostream& out) const override;
		static Book* createItem(const std::string& strBook);
	};


}
#endif