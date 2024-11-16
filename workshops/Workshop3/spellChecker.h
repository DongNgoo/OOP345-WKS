#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <string>
#include <array>
#include <ostream>
namespace seneca {
	class SpellChecker {
		static constexpr size_t ARRAY_SIZE = 6;
		std::array <std::string, ARRAY_SIZE> m_badWords{};
		std::array <std::string, ARRAY_SIZE> m_goodWords{};
		std::array <size_t, ARRAY_SIZE> m_replacementCounts{};
	public:
		SpellChecker(const char* filename);
		void operator()(std::string& text);
		void showStatistics(std::ostream& out) const;

	};

}
#endif
