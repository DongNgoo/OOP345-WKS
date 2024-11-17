#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include "mediaItem.h"
#include <list>
#include <string>
#include <memory>
#include <ostream>
#include <stdexcept>
namespace seneca {
	class TvShow;
	struct TvEpisode
	{
		const TvShow* m_show{};
		unsigned short m_numberOverall{};
		unsigned short m_season{};
		unsigned short m_numberInSeason{};
		std::string m_airDate{};
		unsigned int m_length{};
		std::string m_title{};
		std::string m_summary{};
	};
	class TvShow : public MediaItem {
	private:
		std::string m_id{};
		std::list<TvEpisode> m_episodes{};

		//Private constructor
	   TvShow(const std::string& title, const std::string& summary, unsigned short year, const std::string& id)
			: MediaItem(title, summary, year), m_id{ id } {}
	public:
		void display(std::ostream& out) const override;
		static TvShow* createItem(const std::string& strShow);

		template<typename Collection_t>
		static void addEpisode(Collection_t& col, const std::string& strEpisode);

		double getEpisodeAverageLength() const;

		std::list<std::string> getLongEpisodes() const;

		const std::string& getId() const { return m_id; }

	};
}
#endif