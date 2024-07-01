#include "csv.hpp"
#include <fstream>
#include <iostream>
#include <span>

constexpr char SEPARATOR = '\t';

std::vector<DictionaryEntry> loadFromCsv(const char *path) {
	std::vector<DictionaryEntry> entries;
	std::ifstream file(path);

	std::string line;
	std::string fields[3];

	while (std::getline(file, line)) {
		int curField = 0;

		for (int i = 0; i < line.size(); i++) {
			if (line[i] == SEPARATOR) {
				curField++;
			} else {
				fields[curField].push_back(line[i]);
			}
		}

		// If the fields were filled, then add them to the dictionary
		if (curField == 2) {
			entries.push_back(DictionaryEntry(fields[0], fields[1], fields[2]));
		}

		// Clear fields before going to the next line
		for (int i = 0; i < 3; i++) {
			fields[i].clear();
		}
	}

	return entries;
}

void saveToCsv(const char *path, std::span<DictionaryEntry> entries) {
	std::ofstream file(path);

	for (int i = 0; i < entries.size(); i++) {
		file << entries[i].pinyin << SEPARATOR << entries[i].characters
			 << SEPARATOR << entries[i].definition << std::endl;
	}
}
