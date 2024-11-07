#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H
//searchWord function
#include <string>
#include <iostream>
#include "settings.h"
enum class PartOfSpeech
{
	Unknown,
	Noun,
	Pronoun,
	Adjective,
	Adverb,
	Verb,
	Preposition,
	Conjunction,
	Interjection,
};
struct Word
{
	std::string m_word{};
	std::string m_definition{};
	PartOfSpeech m_pos = PartOfSpeech::Unknown;
};
class Dictionary {
private:
	Word* m_words;
	size_t m_size; //number of word in array

	//Helper function parse part of speech from string
	PartOfSpeech parsePos(const std::string& pos);
public:

	//Default Constructor
	Dictionary();
	//Constructor  to load word from file
	Dictionary(const char* filename);
	//Destructor
	~Dictionary();
	//Disable copy operation
	Dictionary(const Dictionary&) = delete;
	Dictionary& operator=(const Dictionary&) = delete;

	//Enable move operations
	Dictionary(Dictionary&&) noexcept;
	Dictionary& operator=(Dictionary&&) noexcept;

	//search for a word in the dictionary
	void searchWord(const char* word) const;

};
#endif SENECA_DICTIONARY_H

