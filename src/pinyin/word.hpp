#pragma once
#include "syllable.hpp"
#include <vector>
#include <string_view>

typedef std::vector<Syllable> PinyinWord;
std::ostream &operator<<(std::ostream &out, const PinyinWord &word);

PinyinWord parseWord(std::string_view text);

