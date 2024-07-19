#include "word.hpp"
#include <algorithm>
#include <cmath>
#include <ostream>
#include <optional>
#include <vector>
#include <iostream>

std::ostream &operator<<(std::ostream &out, const PinyinWord &word) {
	for (auto syl : word)
		out << syl;
	return out;
}

PinyinWord parseWord(std::string_view text) {
	std::vector<Syllable> vec;
	int index = 0;

	while (index < text.size()) {
		std::optional<Consonant> cons;
		std::optional<Vowel> vowel;
		std::optional<Tone> tone;

		// Search in order of longest to shortest match
		for (int j = 0; j < CONSONANT_COUNT; j++) {
			auto i = (CONSONANT_COUNT - 1) - j;
			auto entry = CONSONANT_STR[i];
			auto sub = text.substr(index, entry.str.size());

			// std::cout << sub << " == " << entry.str << std::endl;
			if (sub == entry.str) {
				index += entry.str.size();
				cons = entry.cons;
				break;
			}
		}

		for (int j = 0; j < VOWEL_COUNT; j++) {
			auto i = (VOWEL_COUNT - 1) - j;
			auto entry = VOWEL_STR[i];
			auto sub = text.substr(index, entry.str.size());

			// std::cout << sub << " == " << entry.str << std::endl;
			if (sub == entry.str) {
				index += entry.str.size();
				vowel = entry.vowel;
				break;
			}
		}

		switch (text[index]) {
		case '0':
			tone = Tone::Neutral;
			index += 1;
			break;
		case '1':
			tone = Tone::First;
			index += 1;
			break;
		case '2':
			tone = Tone::Second;
			index += 1;
			break;
		case '3':
			tone = Tone::Third;
			index += 1;
			break;
		case '4':
			tone = Tone::Fourth;
			index += 1;
			break;
		default:
			tone = Tone::Neutral;
			break;
		}

		// std::cout 
		// 	<< "Cons: " << (cons.has_value() ? cons.value(): ) << " " 
		// 	<< "Vowel: " << (vowel.has_value() ? vowel.value(): 0) << " " 
		// 	<< "Tone: " << (tone.has_value() ? (int)tone.value(): 0) << std::endl;

		if (cons.has_value() && vowel.has_value() && tone.has_value()) {
			// Syllable syl = {cons.has_value() ? cons.value() : NoConsonant, vowel.value(), tone.value()};
			Syllable syl = {cons.value(), vowel.value(), tone.value()};
			vec.push_back(syl);
		} else {
			break;
		}
	}

	return vec;
}

