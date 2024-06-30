#pragma once
#include "DictionaryEntry.hpp"
#include "pinyin/word.hpp"
#include <span>

struct SearchResult {
	int entryIdx;
	float correlation;
};

std::vector<SearchResult> searchInEntries(std::span<const DictionaryEntry> entries,
								 std::string_view query);
