#include "Utilities.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
namespace seneca {

	//initialize static member
	char Utilities::m_delimiter = ',';

	//set the current object = newWidth
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	//returnt the field width
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {

		if (next_pos >= str.length()) {
			more = false;
			return {};
		}

		size_t delimter_pos = str.find(m_delimiter, next_pos);

		//throw exception
		if (delimter_pos == next_pos) {
			throw std::runtime_error("Delimiter found at the starting position.");
		}

		//extract token
		std::string token = (delimter_pos == std::string::npos) 
			? str.substr(next_pos) 
			: str.substr(next_pos, delimter_pos - next_pos);

		//trim 
		token.erase(0, token.find_first_not_of(' '));
		token.erase(token.find_last_not_of(' ') + 1);
		
		//update field width
		if (token.length() > m_widthField) {
			m_widthField = token.length();
		}
		return token;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}


}