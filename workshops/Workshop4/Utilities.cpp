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
            throw "   ERROR: No token.";
        }

        size_t end_pos = str.find(m_delimiter, next_pos);
        std::string token;

        if (end_pos == std::string::npos) {
            token = str.substr(next_pos);
            next_pos = str.length();
        }
        else {
            token = str.substr(next_pos, end_pos - next_pos);
            next_pos = end_pos + 1;
        }

        if (token.empty()) {
            more = false;
            throw "   ERROR: No token.";
        }

        more = (next_pos < str.length());

        if (token.length() > m_widthField) {
            m_widthField = token.length();
        }
		Utilities::trim(token);
        return token;
    
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}


	void Utilities::trim(std::string& str)
	{
		size_t i = 0u;
		for (i = 0u; i < str.length() && str[i] == ' '; ++i);
		str = str.substr(i);

		for (i = str.length(); i > 0 && str[i - 1] == ' '; --i);
		str = str.substr(0, i);


	}

}