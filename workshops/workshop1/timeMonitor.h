#include <iostream>
#include <chrono>
#include "event.h"

#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
namespace seneca {
	class TimeMonitor {
	private:
		std::string m_eventName;//name current event
		std::chrono::steady_clock::time_point m_startTime; // start time of the event
		bool m_eventInProgress; //tracks if an event is currently in progress
	public:
		//default construct
		TimeMonitor() : m_eventInProgress(false) {}

		void startEvent(const char* name);

		Event stopEvent();
	};
}
#endif 
