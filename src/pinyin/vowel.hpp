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

// WARNING! This must have the same order as the enum
const VowelStr VOWEL_STR[] = {
	{A, "a"},		{E, "e"},	  {I, "i"},		{O, "o"},		{U, "u"},
	{Er, "er"},		{Ai, "ai"},	  {Ei, "ei"},	{Ao, "ao"},		{Ou, "ou"},
	{An, "an"},		{En, "en"},	  {Ia, "ia"},	{Ie, "ie"},		{Iu, "iu"},
	{In, "in"},		{Ua, "ua"},	  {Uo, "uo"},	{Ui, "ui"},		{Un, "un"},
	{Ue, "ue"},		{Iao, "iao"}, {Ian, "ian"}, {Ing, "ing"},	{Uai, "uai"},
	{Ang, "ang"},	{Eng, "eng"}, {Ong, "ong"}, {Iang, "iang"}, {Iong, "iong"},
	{Uang, "uang"},
};
const int VOWEL_COUNT = std::extent<decltype(VOWEL_STR)>::value;

