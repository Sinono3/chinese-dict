#pragma once
#include "syllable.hpp"
#include "word.hpp"

struct PrettySyllable {
 const Syllable& syl;
};

std::ostream &operator<<(std::ostream &out, const PrettySyllable &syl);

struct PrettyPinyinWord {
 const PinyinWord& word;
};

std::ostream &operator<<(std::ostream &out, const PrettyPinyinWord &word);
