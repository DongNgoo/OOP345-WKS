#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include "mediaItem.h"
namespace seneca {
	class Book :: public MediaItem {
		std::string m_author{ };
		std::sting m_country{};
	};

public:
	Book* createItem(const std::string& strBook);
}
#endif