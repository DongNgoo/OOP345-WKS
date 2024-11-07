#include "event.h"
#include <iomanip>
#include <iostream>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const Event& event) {
	static int counter = 0; //local static variable to count calls
	counter++;
	
	int durationWidth;
	std::string timeUnits = g_settings.m_time_units;

	if (timeUnits == "seconds") 
	{
		durationWidth = 2;
	}
	else if (timeUnits == "miliseconds") 
	{
		durationWidth = 5;
	}
	else if (timeUnits == "microseconds")
	{
		durationWidth = 8;
	}
	else if (timeUnits == "nanoseconds")
	{
		durationWidth = 11;
	}
	//set width
	os << std::setw(2) << counter << ": "
		<< std::setw(40) << event.m_name << " ->"
		<< std::setw(durationWidth) << event.m_duration.count() << " "
		<< timeUnits;
	return os;

}