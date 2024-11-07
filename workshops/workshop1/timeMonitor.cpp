#include "timeMonitor.h"
#include <stdexcept>

void TimeMonitor::startEvent(const char* name) {
	m_eventName = name;
	m_startTime = std::chrono::steady_clock::now();
	m_eventInProgress = true; // mark event has started
}

Event TimeMonitor::stopEvent() {
	if (!m_eventInProgress) {
		throw std::runtime_error("No event in progress to stop.");
	}

	auto endTime = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast < std::chrono::nanoseconds > (endTime - m_startTime);
	
	m_eventInProgress = false;

	return Event(m_eventName.c_str(), duration);
}