#include "book.h"
#include "mediaItem.h"
#include "settings.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
namespace seneca {
	//display function
    void Book::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }
    Book* Book::createItem(const std::string& strBook) {
		if (strBook.size() == 0 || strBook[0] == '#') {
			throw "Not a valid book.";
		}
		std::string author, title, country, summary;
		unsigned short year;
		double price;
		size_t pos = 0;
		size_t nextPos = 0;
		
		

        //author
		nextPos = strBook.find(",", pos);
		author = strBook.substr(pos, nextPos - pos);
		MediaItem::trim(author);
		pos = nextPos + 1;
        
        //tittle
        nextPos = strBook.find(",", pos);
        title = strBook.substr(pos, nextPos - pos);
        MediaItem::trim(title);
        pos = nextPos + 1;

        //country
		nextPos = strBook.find(",", pos);
		country = strBook.substr(pos, nextPos - pos);
		MediaItem::trim(country);
		pos = nextPos + 1;
        // Price
        nextPos = strBook.find(",", pos);
        std::string priceStr = strBook.substr(pos, nextPos - pos);
        MediaItem::trim(priceStr);
        price = std::stod(priceStr);
        pos = nextPos + 1;

        // Year
        nextPos = strBook.find(",", pos);
        std::string yearStr = strBook.substr(pos, nextPos - pos);
        MediaItem::trim(yearStr);
        year = static_cast<unsigned short>(std::stoi(yearStr));
        pos = nextPos + 1;

        summary = strBook.substr(pos);
        MediaItem::trim(summary);

		//return nullptr;
        return new Book(author, title, country, price, year, summary);
	}
}
