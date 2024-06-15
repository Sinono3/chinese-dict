#ifndef _PINYIN_CPP
#define _PINYIN_CPP

#include "FL/Fl.H"
#include "FL/Fl_Input.H"
#include "FL/Fl_Window.H"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>
#include <vector>

namespace pinyin {
enum Consonant {
	B,
	P,
	M,
	F,
	D,
	T,
	N,
	L,
	G,
	K,
	H,
	J,
	Z,
	C,
	S,
	Y,
	W,
	R,
	Q,
	X,
	Zh,
	Ch,
	Sh
};

struct ConsonantStr {
	Consonant cons;
	std::string_view str;
};

// WARNING! This must have the same order as the enum
const ConsonantStr CONSONANT_STR[] = {
	{B, "b"}, {P, "p"}, {M, "m"},	{F, "f"},	{D, "d"},  {T, "t"},
	{N, "n"}, {L, "l"}, {G, "g"},	{K, "k"},	{H, "h"},  {J, "j"},
	{Z, "z"}, {C, "c"}, {S, "s"},	{Y, "y"},	{W, "w"},  {R, "r"},
	{Q, "q"}, {X, "x"}, {Zh, "zh"}, {Ch, "ch"}, {Sh, "sh"}};
const int CONSONANT_COUNT = std::extent<decltype(CONSONANT_STR)>::value;

// Can be one or two vowel combinations
// WARNING! This must have the same order as the enum
enum Vowel {
	A,
	E,
	I,
	O,
	U,
	Er,
	Ai,
	Ei,
	Ao,
	Ou,
	An,
	En,
	La,
	Ie,
	Iu,
	In,
	Ua,
	Uo,
	Ui,
	Un,
	Ue,
	Iao,
	Ian,
	Ing,
	Uai,
	Ang,
	Eng,
	Ong,
	Iang,
	Iong,
	Uang,
};

struct VowelStr {
	Vowel vowel;
	std::string_view str;
};

const VowelStr VOWEL_STR[] = {
	{A, "a"},		{E, "e"},	  {I, "i"},		{O, "o"},		{U, "u"},
	{Er, "er"},		{Ai, "ai"},	  {Ei, "ei"},	{Ao, "ao"},		{Ou, "ou"},
	{An, "an"},		{En, "en"},	  {La, "la"},	{Ie, "ie"},		{Iu, "iu"},
	{In, "in"},		{Ua, "ua"},	  {Uo, "uo"},	{Ui, "ui"},		{Un, "un"},
	{Ue, "ue"},		{Iao, "iao"}, {Ian, "ian"}, {Ing, "ing"},	{Uai, "uai"},
	{Ang, "ang"},	{Eng, "eng"}, {Ong, "ong"}, {Iang, "iang"}, {Iong, "iong"},
	{Uang, "uang"},
};
const int VOWEL_COUNT = std::extent<decltype(VOWEL_STR)>::value;

enum Tone { Neutral = 0, First = 1, Second = 2, Third = 3, Fourth = 4 };

struct Syllable {
	Consonant consonant;
	Vowel vowel;
	Tone tone;

	bool operator==(const Syllable &other) const {
		return consonant == other.consonant && vowel == other.vowel &&
			   tone == other.tone;
	}
};

std::ostream &operator<<(std::ostream &out, const Syllable &syl) {
	return out << CONSONANT_STR[syl.consonant].str << VOWEL_STR[syl.vowel].str
			   << syl.tone;
}

typedef std::vector<Syllable> Word;

std::ostream &operator<<(std::ostream &out, const Word &word) {
	for (auto syl : word) {
		out << syl;
	}
	return out;
}

struct InvalidPinyinException {};

Word parse(std::string_view text) {
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
			tone = Neutral;
			index += 1;
			break;
		case '1':
			tone = First;
			index += 1;
			break;
		case '2':
			tone = Second;
			index += 1;
			break;
		case '3':
			tone = Third;
			index += 1;
			break;
		case '4':
			tone = Fourth;
			index += 1;
			break;
		}

		if (cons.has_value() && vowel.has_value() && tone.has_value()) {
			Syllable syl = {cons.value(), vowel.value(), tone.value()};
			vec.push_back(syl);
		} else {
			break;
		}
	}

	return vec;
}

} // namespace pinyin

struct DictionaryEntry {
	pinyin::Word pinyin;
	std::string string;
};

DictionaryEntry ENTRIES[] = {
	{pinyin::parse("pin1yin1"), "拼音"},
	{pinyin::parse("yin1yue4"), "音樂"},
};

int main() {

	// auto tests = {
	// 	"pin1yin1", "shui2", "xi3huan1", "shou3ji1", "wo3men0",
	// };

	// for (auto test : tests) {
	// 	auto word = pinyin::parse(test);

	// 	for (auto syl : word) {
	// 		std::cout << syl;
	// 	}
	// 	std::cout << std::endl;
	// }

	Fl_Window *window = new Fl_Window(300, 300, "Chinese Dictionary!");
	window->begin();

	Fl_Input *input = new Fl_Input(0, 0, 300, 80);
	input->when(FL_WHEN_CHANGED);
	input->callback([](Fl_Widget *widget, void *b) {
		Fl_Input *input = (Fl_Input *)(widget);
		auto search = input->value();
		auto searchPinyin = pinyin::parse(search);

		struct SearchResult {
			int entryIdx, correlation;
		};

		std::vector<SearchResult> results;

		for (int entryIdx = 0;
			 entryIdx < (sizeof(ENTRIES) / sizeof(ENTRIES[0])); entryIdx++) {
			const DictionaryEntry &entry = ENTRIES[entryIdx];
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

		system("clear");

		for (auto result : results) {
			const DictionaryEntry &entry = ENTRIES[result.entryIdx];
			std::cout << "- " << entry.string << ": " << entry.pinyin
					  << std::endl;
		}
	});

	window->end();
	window->show();

	return Fl::run();
}

#endif
