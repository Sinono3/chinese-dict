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

	/// The higher the correlation, the closer the syllables are
	int getCorrelation (const Syllable &other) const {
		int consonantCorr = !(consonant == other.consonant);
		int vowelCorr = !(vowel == other.vowel);
		int toneCorr = !(tone == other.tone);
		// Neutral correlates with any tone
		if (tone == Tone::Neutral || other.tone == Tone::Neutral)
			toneCorr = 1;
		return consonantCorr + vowelCorr + toneCorr;
	}
};

std::ostream &operator<<(std::ostream &out, const Syllable &syl);
