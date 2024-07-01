#pragma once
#include <string_view>

// Can be one or two vowel combinations
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
	Ia,
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
	Uan,
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
	// The index of character where we place the tone marker
	int toneCharIndex;
};

// WARNING! This must have the same order as the enum
const VowelStr VOWEL_STR[] = {
	{A, "a", 0},		{E, "e", 0},		{I, "i", 0},	  {O, "o", 0},		{U, "u", 0},
	{Er, "er", 0},		{Ai, "ai", 0},		{Ei, "ei", 0},	  {Ao, "ao", 0},	{Ou, "ou", 0},
	{An, "an", 0},		{En, "en", 0},		{Ia, "ia", 1},	  {Ie, "ie", 1},	{Iu, "iu", 1},
	{In, "in", 0},		{Ua, "ua", 1},		{Uo, "uo", 1},	  {Ui, "ui", 1},	{Un, "un", 0},
	{Ue, "ue", 1},		{Iao, "iao", 1},	{Ian, "ian", 1}, {Ing, "ing", 0}, {Uai, "uai", 1},
	{Uan, "uan", 1},	{Ang, "ang", 0},	{Eng, "eng", 0}, {Ong, "ong", 0}, {Iang, "iang", 1},
	{Iong, "iong", 1}, {Uang, "uang", 2},
};
const int VOWEL_COUNT = std::extent<decltype(VOWEL_STR)>::value;
