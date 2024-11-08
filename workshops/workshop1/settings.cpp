#include "settings.h"
namespace seneca {
	Settings g_settings = {
		false, //set default for m_show_all
		false, //set default for m_verbose
		"nanoseconds" //set default for m_time_unit
	};
}