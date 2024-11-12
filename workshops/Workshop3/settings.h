#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
namespace seneca {
	struct Settings{
		bool m_tableView = false;
		unsigned short m_maxSummaryWidth = 80;
		//bool m
		//short m
	};
	extern Settings g_settings;
}

#endif 