#pragma once
#include "pinyin/word.hpp"
#include <span>

struct DictionaryEntry {
	PinyinWord pinyin;
	std::string string;
};

struct SearchResult {
	int entryIdx, correlation;
};

std::vector<SearchResult> searchInEntries(std::span<const DictionaryEntry> entries,
								 std::string_view query);
