#include "DictionaryEntry.hpp"
#include <span>
std::vector<DictionaryEntry> loadFromCsv(const char *path);
void saveToCsv(const char *path, std::span<DictionaryEntry> entries);
