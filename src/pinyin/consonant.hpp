#pragma once
#include <string_view>

enum Consonant {
	NoConsonant,
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
	{NoConsonant, ""}, {B, "b"}, {P, "p"}, {M, "m"},   {F, "f"},   {D, "d"},
	{T, "t"},		   {N, "n"}, {L, "l"}, {G, "g"},   {K, "k"},   {H, "h"},
	{J, "j"},		   {Z, "z"}, {C, "c"}, {S, "s"},   {Y, "y"},   {W, "w"},
	{R, "r"},		   {Q, "q"}, {X, "x"}, {Zh, "zh"}, {Ch, "ch"}, {Sh, "sh"}};
const int CONSONANT_COUNT = std::extent<decltype(CONSONANT_STR)>::value;
