#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include "mediaItem.h"
#include <string>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>
namespace seneca {
	class Collection {
	private:
		std::string m_name;
		std::vector<MediaItem*> m_items;
		void (*m_observer)(const Collection&, const MediaItem&) = nullptr;
	public:
		//constructor
		explicit Collection(const std::string& name);

		// Rule of Five - Delete all copy/move operations
		Collection(const Collection&) = delete;
		Collection(Collection&&) = delete;
		Collection& operator=(const Collection&) = delete;
		Collection& operator=(Collection&&) = delete;

		//Destructor
		~Collection();
		
		//query
		const std::string& name() const;
		size_t size() const;

		//setObserver
		void setObserver(void (*observer)(const Collection&, const MediaItem&));
		
		//add item
		Collection& operator+=(MediaItem* item);

		//retuns the item at index
		MediaItem* operator[](size_t idx) const;

		//return address of the item with tittle
		MediaItem* operator[](const std::string& title) const;

		//remove quotes
		void removeQuotes();

		//sort quotes
		void sort(const std::string& field);
		
		//Helpers
		friend std::ostream& operator<<(std::ostream& out, const Collection& collection);

	};
}
#endif