#pragma once
#include "pinyin/word.hpp"

struct DictionaryEntry {
	PinyinWord pinyin;
	std::string characters;
	std::string definition;
	// std::vector<std::string> examples;

	DictionaryEntry(
        std::string pinyin,
		std::string characters,
		std::string definition
		// std::vector<std::string> examples
    ) : pinyin(parseWord(pinyin)), characters(characters), definition(definition) {}
};

