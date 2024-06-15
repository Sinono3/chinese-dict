#include "search.hpp"
#include <iterator>
#include <map>
#include <span>
#include <vector>

std::vector<SearchResult> searchInEntries(std::span<const DictionaryEntry> entries,
								 std::string_view query) {
	std::vector<SearchResult> results;

	if (query.length() > 0) {
		auto searchPinyin = parseWord(query);

		for (int entryIdx = 0; entryIdx < entries.size(); entryIdx++) {
			const DictionaryEntry &entry = entries[entryIdx];
			int correlation = 0;

			for (int i = 0; i < entry.pinyin.size(); i++) {
				for (int j = 0; j < searchPinyin.size(); j++) {
					if (entry.pinyin[i] == searchPinyin[j]) {
						correlation++;
					}
				}
			}

			if (correlation > 0) {
				results.push_back({entryIdx, correlation});
			}
		}

		std::stable_sort(results.begin(), results.end(),
						 [](SearchResult a, SearchResult b) {
							 return a.correlation > b.correlation;
						 });

	} else {
		// If query is null, add all entries
		for (int i = 0; i < entries.size(); i++) {
			results.push_back(SearchResult{i, 0});
		}
	}

	return results;
}
