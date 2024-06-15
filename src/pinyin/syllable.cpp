#include "consonant.hpp"
#include "syllable.hpp"
#include <ostream>

std::ostream &operator<<(std::ostream &out, const Syllable &syl) {
	return out << CONSONANT_STR[syl.consonant].str << VOWEL_STR[syl.vowel].str
			   << syl.tone;
}

