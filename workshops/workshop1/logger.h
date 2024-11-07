#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
class Logger {
private:
	Event* m_events;
	int m_size;
	int m_capacity;

	void resize(int newCapacity);
public:
	//Default contrustor
	Logger();

	//Destructor
	~Logger();

	//disable copy operations
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	//Move contrustor
	Logger(Logger&& other) noexcept;

	//Move assignment constructor
	Logger& operator=(Logger&& other) noexcept;

	//addNewEventFunction
	void addEvent(const Event& event);
	
	//friend helper
	friend std::ostream& operator<<(std::ostream& os, const Logger& logger);
};
#endif SENECA_LOGGER_H

