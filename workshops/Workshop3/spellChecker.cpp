#include "spellChecker.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
namespace seneca {

	SpellChecker::SpellChecker(const char* filename) {
		std::ifstream file(filename);
		if (!file) {
			throw "Bad file name";
		}
		std::string line;
		size_t index = 0;

		while (std::getline(file, line) && index < ARRAY_SIZE) {
			std::istringstream stream(line);
			std::string badWord, goodWord;
			stream >> badWord >> goodWord;
			if (!badWord.empty() && !goodWord.empty()) {
				m_badWords[index] = badWord;
				m_goodWords[index] = goodWord;
				m_replacementCounts[index] = 0;
				++index;
			}
		}
		file.close();
	}
	void SpellChecker :: operator()(std::string& text) {
		for (size_t i = 0; i < ARRAY_SIZE; ++i) {
			size_t pos = 0;
			while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
				text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
				++m_replacementCounts[i];
				pos += m_goodWords[i].length();
			}
		}
	}
	void SpellChecker::showStatistics(std::ostream& out) const {
		for (size_t i = 0; i < ARRAY_SIZE; ++i) {
			out << std::setw(15) << std::right << m_badWords[i] << ": "
				<< m_replacementCounts[i] << " replacements" << std::endl;
		}
	}

};

