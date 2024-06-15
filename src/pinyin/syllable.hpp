#pragma once
#include "consonant.hpp"
#include "vowel.hpp"
#include "tone.hpp"

#include <ostream>

struct Syllable {
	Consonant consonant;
	Vowel vowel;
	Tone tone;

	bool operator==(const Syllable &other) const {
		return consonant == other.consonant && vowel == other.vowel &&
			   tone == other.tone;
	}
};

std::ostream &operator<<(std::ostream &out, const Syllable &syl);
