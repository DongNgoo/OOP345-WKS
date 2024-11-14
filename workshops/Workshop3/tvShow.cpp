#include "tvShow.h"
#include "mediaItem.h"
#include "settings.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
// for long episode 
//use STL to find episodes that are longer than 60 mins
// and add them to the list, with using for loop anywhere in the code 

//for each function is also STL algorithm,no using  manual loop
//check transform, copy_if,accumualte

namespace seneca {
	// Private constructor
	 // Private constructor
	TvShow::TvShow(const std::string& id, const std::string& title, int year, const std::string& summary)
		: MediaItem(title, summary, year), m_id(id) {}
    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }
    TvShow* TvShow::createItem(const std::string& strShow) {
        if (strShow.empty() || strShow[0] == '#') {
            throw std::invalid_argument("Not a valid show");
        }
        std::istringstream stream(strShow);
        std::string id, title, yearStr, summary;
        std::getline(stream, id, ',');
        std::getline(stream, title, ',');
        std::getline(stream, yearStr, ',');
        std::getline(stream, summary, ',');

        auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(' '));
            str.erase(str.find_last_not_of(' ') + 1);
            };
        trim(id);
        trim(title);
        trim(yearStr);
        trim(summary);

        int year = std::stoi(yearStr);
        return new TvShow(id, title, year, summary);
    }
    template<typename Collection_t>
    void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode) {
        if (strEpisode.empty() || strEpisode[0] == '#') {
            throw std::invalid_argument("Not a valid episode");
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
        std::getline(stream, summary, ',');

        auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(' '));
            str.erase(str.find_last_not_of(' ') + 1);
            };
        trim(id);
        trim(numberOverallStr);
        trim(seasonStr);
        trim(numberInSeasonStr);
        trim(airDate);
        trim(lengthStr);
        trim(title);
        trim(summary);

        unsigned short numberOverall = static_cast<unsigned short>(std::stoi(numberOverallStr));
        unsigned short season = seasonStr.empty() ? 1 : static_cast<unsigned short>(std::stoi(seasonStr));
        unsigned short numberInSeason = static_cast<unsigned short>(std::stoi(numberInSeasonStr));
        unsigned int length = static_cast<unsigned int>(std::stoi(lengthStr));
        auto it = std::find_if(col.begin(), col.end(), [&id](const std::unique_ptr<MediaItem>& item) {
            return item->getId() == id;
            });

        if (it != col.end()) {
            TvEpisode episode{ dynamic_cast<TvShow*>(it->get()), numberOverall, season, numberInSeason, airDate, length, title, summary };
            dynamic_cast<TvShow*>(it->get())->m_episodes.push_back(episode);
        }
    }

    // Calculate the average length of episodes
    double TvShow::getEpisodeAverageLength() const {
        if (m_episodes.empty()) return 0.0;
        return std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0,
            [](double sum, const TvEpisode& episode) { return sum + episode.m_length; }) / m_episodes.size();
    }

    // Get a list of long episode names (at least 1 hour)
    std::list<std::string> TvShow::getLongEpisodes() const {
        std::list<std::string> longEpisodes;
        std::copy_if(m_episodes.begin(), m_episodes.end(), std::back_inserter(longEpisodes),
            [](const TvEpisode& episode) { return episode.m_length >= 3600; });
        return longEpisodes;
    }
    
}