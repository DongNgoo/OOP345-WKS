#include "logger.h"
#include <iostream>
#include <algorithm> // for std:: move

//Default constructor
Logger::Logger() : m_events(nullptr), m_size(0), m_capacity(0) {}

//Destrustor

Logger::~Logger() {
	delete[] m_events;
}

//Move construstor

Logger::Logger(Logger&& other) noexcept
	:m_events(other.m_events), m_size(other.m_size), m_capacity(other.m_capacity) {
	other.m_events = nullptr;
	other.m_size = 0;
	other.m_capacity = 0;
}

//Move assigment constructor 
Logger& Logger::operator=(Logger&& other) noexcept {
	if (this != &other) {
		delete[] m_events;

		m_events = other.m_events;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		other.m_events = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}
	return *this;
}
void Logger::resize(int newCapacity) {
	Event* newEvents = new Event[newCapacity];
	for (int i = 0; i < m_size; ++i) {
		newEvents[i] = std::move(m_events[i]);

	}
	delete[] m_events;
	m_events = newEvents;
	m_capacity = newCapacity;

}

void Logger::addEvent(const Event& event) {
	if (m_size == m_capacity) {
		int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
		resize(newCapacity);
	}
	m_events[m_size++] = event;
}
//friend helper
std::ostream& operator<<(std::ostream& os, const Logger& logger) {
	for (int i = 0; i < logger.m_size; ++i) {
		os << logger.m_events[i] << std::endl;
	}
	return os;
}
