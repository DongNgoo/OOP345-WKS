#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include "mediaItem.h"
#include "settings.h"
#include <list>
#include <string>
#include <algorithm>
#include <memory>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
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
	  TvShow(const std::string& id, const std::string& title,
			const std::string& summary, unsigned short year)
			: MediaItem(title, summary, year), m_id{ id } {}
	public:
		void display(std::ostream& out) const override;

        static TvShow* createItem(const std::string& strShow);

        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode) {
            if (strEpisode.empty() || strEpisode[0] == '#') {
                throw "Not a valid episode.";
            }

            std::istringstream stream(strEpisode);
            std::string id, numberOverallStr, seasonStr, numberInSeasonStr, airDate, lengthStr, title, summary;

            std::getline(stream, id, ',');
            std::getline(stream, numberOverallStr, ',');
            std::getline(stream, seasonStr, ',');
            std::getline(stream, numberInSeasonStr, ',');
            std::getline(stream, airDate, ',');
            std::getline(stream, lengthStr, ',');
            std::getline(stream, title, ',');
            std::getline(stream, summary);

            trim(id);
            trim(numberOverallStr);
            trim(seasonStr);
            trim(numberInSeasonStr);
            trim(airDate);
            trim(lengthStr);
            trim(title);
            trim(summary);

            unsigned short numberOverall = std::stoi(numberOverallStr);
            unsigned short season = seasonStr.empty() ? 1 : std::stoi(seasonStr);
            unsigned short numberInSeason = std::stoi(numberInSeasonStr);
            unsigned int length = std::stoi(lengthStr);

            TvEpisode episode{ nullptr, numberOverall, season, numberInSeason, airDate, length, title, summary };

            bool found = false;
            for (size_t i = 0; i < col.size(); ++i) {
                TvShow* tvShow = dynamic_cast<TvShow*>(col[i]); // Ensure col[i] is of type TvShow
                if (tvShow && tvShow->m_id == id) {  // Direct access to m_id
                    tvShow->m_episodes.push_back(episode);  // Add episode
                    found = true;
                    break;
                }
            }

            if (!found) {
                throw "TV Show ID not found in the collection.";
            }
        }

		double getEpisodeAverageLength() const;

		std::list<std::string> getLongEpisodes() const;

        template<typename Collection_t>
        friend void addEpisode(Collection_t& col, const std::string& strEpisode);

	};
}
#endif