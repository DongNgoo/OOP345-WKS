
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
namespace seneca {

	struct  Settings {
		bool m_show_all;
		bool m_verbose;
		std::string m_time_units;
	};

	extern Settings g_settings;
}
#endif 