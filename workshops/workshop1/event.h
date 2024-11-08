#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <iostream>
#include <chrono>
#include <string>
#include "settings.h"

namespace seneca {

	class Event {
	private:
		std::string m_name;
		std::chrono::nanoseconds m_duration;
	public:
		Event() : m_name(""), m_duration(0) {}
		Event(const char* name, const std::chrono::nanoseconds& duration)
			: m_name(name), m_duration(duration) {}

		friend std::ostream& operator<<(std::ostream& os, const Event& event);
	};

} // namespace seneca

#endif // SENECA_EVENT_H
