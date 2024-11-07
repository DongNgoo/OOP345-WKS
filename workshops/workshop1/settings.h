
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

struct  Settings {
	bool m_show_all;
	bool m_verbose;
	std::string m_time_units;
};

extern Settings g_settings;
#endif SENECA_SETTINGS_H