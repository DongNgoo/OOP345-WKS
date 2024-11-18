#include "tvShow.h"
#include "mediaItem.h"
#include "settings.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <iterator>
// for long episode 
 
//use STL to find episodes that are longer than 60 mins
// and add them to the list, with using for loop anywhere in the code 

//for each function is also STL algorithm,no using  manual loop
//check transform, copy_if,accumualte

namespace seneca {
	// Private constructor
	 // Private constructor
    /*TvShow::TvShow(const std::string& title, const std::string& summary, unsigned short year, const std::string& id)
        : MediaItem(title, summary, year), m_id{ id } {}*/
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
   
   

    // Calculate the average length of episodes
    double TvShow::getEpisodeAverageLength() const {
        if (m_episodes.empty()) return 0.0;
        return std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0,
            [](double total, const TvEpisode& ep) { return total + ep.m_length; }) / m_episodes.size();
    }
   
    std::list<std::string> TvShow::getLongEpisodes() const {
        std::list<TvEpisode> episodeNames;
       
        std::copy_if(m_episodes.begin(), m_episodes.end(), std::back_inserter(episodeNames),
            [](const TvEpisode& episode) { return episode.m_length >= 3600; });
        
        std::list<std::string> names(episodeNames.size());

        std::transform(episodeNames.begin(), episodeNames.end(), names.begin(), [](const TvEpisode& n)
            {
                return n.m_title;
            });

        return names;
       
    }
}