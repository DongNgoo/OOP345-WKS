#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include "mediaItem.h"
namespace seneca {
	class Movie : public MediaItem {
	private:
		Movie(const std::string& title, unsigned short year, const std::string& summary)
			:MediaItem(title, summary, year) {}

	public:
		//void display func in desc
		void display(std::ostream& out) const override;
		//createItem header static function
		static Movie* createItem(const std::string& strMovie);
	};

	//tokenize the string and create a new movie object
	

}
#endif