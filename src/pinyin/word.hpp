#pragma once
#include "syllable.hpp"
#include <vector>
#include <string_view>

using PinyinWord = std::vector<Syllable>;
std::ostream &operator<<(std::ostream &out, const PinyinWord &word);

PinyinWord parseWord(std::string_view text);

