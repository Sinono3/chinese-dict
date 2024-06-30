#pragma once
#include "pinyin/word.hpp"
#include <span>

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

struct SearchResult {
	int entryIdx;
	float correlation;
};

std::vector<SearchResult> searchInEntries(std::span<const DictionaryEntry> entries,
								 std::string_view query);
