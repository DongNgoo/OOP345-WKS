#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <string>
#include <cstddef> // for size_t
namespace seneca{
	class Utilities {
		size_t m_widthField = 1;
		//share among all Utilities object
		static char m_delimiter; 
	public:
		//sets the field width of the current object to the value of parameter newWidth
		void setFieldWidth(size_t newWidth);

		//return field width of the current object
		size_t getFieldWidth() const;

		// extracts a token from string str referred to by the first parameter
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		//sets the delimeter for this class to the char received 
		static void setDelimiter(char newDelimiter);

		//returns the delimeter for this class
		static char getDelimiter();


		static void trim(std::string& str);
	};
}
#endif