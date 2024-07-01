#include "pretty.hpp"
#include "consonant.hpp"
#include "vowel.hpp"
#include <map>

const std::map<char, std::array<std::string_view, 5>> VOWEL_CHARS {
	{'a', {"a","ā","á","ǎ","à"}},
	{'e', {"e","ē","é","ě","è"}},
	{'i', {"i","ī","í","ǐ","ì"}},
	{'o', {"o","ō","ó","ǒ","ò"}},
	{'u', {"u","ū","ú","ǔ","ù"}},
	// Unused for now
	// {"ü", {"ü","ǖ","ǘ","ǚ","ǜ"}},
};

std::ostream &operator<<(std::ostream &out, const PrettySyllable &syl) {
	auto vowelStr = VOWEL_STR[syl.syl.vowel];
	// The vowel that we should replace
	char toneVowel = vowelStr.str[vowelStr.toneCharIndex];
	auto tonedVowel = VOWEL_CHARS.at(toneVowel).at((int)syl.syl.tone);

	return out << CONSONANT_STR[syl.syl.consonant].str
		       << vowelStr.str.substr(0, vowelStr.toneCharIndex) 
  	           << tonedVowel
			   << vowelStr.str.substr(vowelStr.toneCharIndex + 1);
}

std::ostream &operator<<(std::ostream &out, const PrettyPinyinWord &word) {
 	for (auto syl : word.word)
		out << PrettySyllable { syl };
	return out;
}
