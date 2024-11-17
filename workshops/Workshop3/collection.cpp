#include "collection.h"

namespace seneca {
	//Constructor
	Collection::Collection(const std::string& name) : m_name(name) {}

	//Destructor
	Collection::~Collection()
	{
		for (auto item : m_items)
			delete item;
	}

	//query
   const std::string& Collection::name() const {
		return m_name;
	}

   size_t Collection::size() const {
	   return m_items.size();
   }

   //set Observer
   void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
	   m_observer = observer;
   }

   //add item
   Collection& Collection::operator+=(MediaItem* item) {
	   auto it = std::find_if(m_items.begin(), m_items.end(),
		   [item](const MediaItem* existing) {
			   return existing->getTitle() == item->getTitle();
		   });
	   //item not found
	   if (it == m_items.end()) {
		   m_items.push_back(item);
		   if (m_observer)
			   m_observer(*this, *item);
	   }
	   else {
		   delete item;
	   }
	   return *this;

  }
   //access by index
   MediaItem* Collection::operator[](size_t idx) const 
   {
	   if (idx >= m_items.size()) 
	   {
		   throw std::out_of_range("Bad index [" + std::to_string(idx) +
			   "]. Collection has [" + std::to_string(m_items.size()) + "] items.");
	   }
	   return m_items[idx];
	   
   }

   //access by tittle
   MediaItem* Collection::operator[](const std::string& title) const {
	   auto it = std::find_if(m_items.begin(), m_items.end(),
		   [&title](const MediaItem* item) {
			   return item->getTitle() == title;
		   });
	   return it != m_items.end() ? *it : nullptr;
   }

   //remove quote

   void Collection::removeQuotes() {
	   std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item) {
		   std::string title = item->getTitle();
		   std::string summary = item->getSummary();

		   if (!title.empty() && title.front() == '"' && title.back() == '"')
			   item->setTitle(title.substr(1, title.size() - 2));


		   if (!summary.empty() && summary.front() == '"' && summary.back() == '"')
			   item->setSummary(summary.substr(1, summary.size() - 2));
		   });
   }

   void Collection::sort(const std::string& field) {
	   std::sort(m_items.begin(), m_items.end(), [&field](MediaItem* a, MediaItem* b) {
		   if (field == "title")
			   return a->getTitle() < b->getTitle();

		   if (field == "year")
			   return a->getYear() < b->getYear();

		   return false;
		   });
   }
   std::ostream& operator<<(std::ostream& out, const Collection& collection)
   {
	   for (const auto item : collection.m_items)
		   out << *item;
	   return out;
   }

}