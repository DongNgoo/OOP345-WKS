#include "book.h"
namespace seneca {
	//display function
	Book::Book* createItem(const std::string& strBook) {
		if (strBook.size() == 0 || strBook[0] == '#') {
			throw "Not a valid book";
		}
		std::string tittle, author, country, summary;
		usigned short year;
		double price;
		size_t pos;
		size_t nextPos = 0;
		//tittle
		nextPos = strBook.find(",", pos);
		tittle = strBook.substr(pos, nextPos - pos);
		MediaItem::trim(tittle);
		pos = nextPos + 1;

		nextPos = strBook.find(",", pos);
		author = strBook.substr(pos, nextPos - pos);
		MediaItem::trim(author);
		pos = nextPos + 1;

		nextPos = strBook.find(",", pos);
		country = strBook.substr(pos, nextPos - pos);
		MediaItem::trim(country);
		pos = nextPos + 1;

		summary = strBook.substr(pos, nextPos = pos)

		return nullptr;
	}
}
