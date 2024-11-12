#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include "mediaItem.h"
namespace seneca {
	class Tvshow:: public MediaItem {
		//struct
		std::string m_id{};
		std::list<tvEpisode> m_episodes{};
	};
}
#endif