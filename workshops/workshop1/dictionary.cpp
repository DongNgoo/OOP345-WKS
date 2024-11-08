#include "dictionary.h"
#include "dictionary.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
//default constructor
namespace seneca {
	// Helper function to trim whitespace from both ends of a string
		std::string trim(const std::string & str) {
		auto start = str.begin();
		while (start != str.end() && std::isspace(*start)) {
			start++;
		}

		auto end = str.end();
		do {
			end--;
		} while (std::distance(start, end) > 0 && std::isspace(*end));

		return std::string(start, end + 1);
	}
		// Convert PartOfSpeech to string
		std::string posToString(PartOfSpeech pos) {
			switch (pos) {
			case PartOfSpeech::Noun: return "noun";
			case PartOfSpeech::Adverb: return "adverb";
			case PartOfSpeech::Adjective: return "adjective";
			case PartOfSpeech::Verb: return "verb";
			case PartOfSpeech::Preposition: return "preposition";
			case PartOfSpeech::Pronoun: return "pronoun";
			case PartOfSpeech::Conjunction: return "conjunction";
			case PartOfSpeech::Interjection: return "interjection";
			default: return "unknown";
			}
		}
	Dictionary::Dictionary() : m_words(nullptr), m_size(0) {}

	//Helper function to parse part of speech
	PartOfSpeech Dictionary::parsePos(const std::string& pos) {
		if (pos == "n." || pos == "n. pl.") return PartOfSpeech::Noun;
		if (pos == "adv.") return PartOfSpeech::Adverb;
		if (pos == "a.") return PartOfSpeech::Adjective;
		if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.") return PartOfSpeech::Verb;
		if (pos == "prep.") return PartOfSpeech::Preposition;
		if (pos == "pron.") return PartOfSpeech::Pronoun;
		if (pos == "conj.") return PartOfSpeech::Conjunction;
		if (pos == "interj.") return PartOfSpeech::Interjection;
		return PartOfSpeech::Unknown;
	}

	//Construstor that loads words from a file

	Dictionary::Dictionary(const char* filename) : m_words(nullptr), m_size(0) {
		std::ifstream file(filename);
		if (!file) {
			std::cerr << "Failed to open file" << filename << std::endl;
			return;
		}
		// First pass: count lines to determine the number of words
		std::string line;
		size_t wordCount = 0;
		while (getline(file, line)) {
			if (!line.empty()) {
				++wordCount;
			}
		}

		

		//Allocate exact memery for words
		m_size = wordCount;
		m_words = new Word[m_size];

		//Second pass: load words
		file.clear();
		file.seekg(0); //rewind to begin

		size_t index = 0;
		while (getline(file, line) && index < m_size) {
			std::istringstream iss(line);
			std::string word, pos, definition;

			// Parse line assuming "word, part_of_speech, definition" format
			if (!getline(iss, word, ',')) continue;        // Read word
			if (!getline(iss, pos, ',')) continue;         // Read part of speech
			if (!getline(iss, definition)) continue;       // Read definition (remaining part)

			// Trim any whitespace around parsed parts if necessary
			word = trim(word);
			pos = trim(pos);
			definition = trim(definition);

			// Populate the word structure
			m_words[index].m_word = word;
			m_words[index].m_pos = parsePos(pos);
			m_words[index].m_definition = definition;
			++index;
			
		}
		
	}
	

	//destructor
	Dictionary::~Dictionary() {
		delete[] m_words;
	}
	// Copy constructor
	Dictionary::Dictionary(const Dictionary& other) : m_size(other.m_size) {
		m_words = new Word[m_size];
		for (size_t i = 0; i < m_size; ++i) {
			m_words[i] = other.m_words[i];
		}
	}

	// Copy assignment operator
	Dictionary& Dictionary::operator=(const Dictionary& other) {
		if (this != &other) {
			delete[] m_words;

			m_size = other.m_size;
			m_words = new Word[m_size];
			for (size_t i = 0; i < m_size; ++i) {
				m_words[i] = other.m_words[i];
			}
		}
		return *this;
	}
	//Move contrustor
	Dictionary::Dictionary(Dictionary&& other) noexcept : m_words(other.m_words), m_size(other.m_size) {
		other.m_words = nullptr;
		other.m_size = 0;
	}

	//Move assignment operator
	Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
		if (this != &other) {
			delete[] m_words;
			m_words = other.m_words;
			m_size = other.m_size;
			other.m_words = nullptr;
			other.m_size = 0;

		}
		return *this;
	}
	void Dictionary::searchWord(const char* word) const {
		std::string target(word);
		bool found = false;
		for (size_t i = 0; i < m_size; ++i) {
			//std::cout << static_cast<int>(m_words[i].m_pos) << std::endl;
			if (m_words[i].m_word == target) {
				if (!found) {
					std::cout << m_words[i].m_word;
					found = true;
				}
				else {
					std::cout << std::setw(target.size()) << ' ';

				}
				if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
					std::cout << " - (" << posToString(m_words[i].m_pos) << ") ";
				}
				else {
					std::cout << " - ";
				}
				std::cout << m_words[i].m_definition << std::endl;
				if (!g_settings.m_show_all) break;
			}
		}
		if (!found) {
			std::cout << "Word ' " << word << "' was not found in the dictionary " << std::endl;
		}
	}
}