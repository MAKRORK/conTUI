#pragma once
#include <vector>
#include <string>
#include "Base.h"
#include "ConColor.h"

namespace ctui
{
	std::string getLineWithOffset(std::string input, int offset, int maxSize = -1);
	bool isUnicodeCont(unsigned char c);
	bool isUnicodeStart(unsigned char c);
	std::string getLine(int n, char c = ' ');
	int getRealLength(std::string &str);
	std::vector<char32_t> stringToChars(std::string &str);
	std::string chrsToString(std::vector<char32_t> &chrs);
	rawText *autoWrap(const std::string &input, int maxLength, vec2 offset = 0, vec2 maxSize = -1, std::vector<int> &realLens = std::vector<int>(), bool withCols = true, ConColor col = ConColor::white, ConColor backCol = ConColor::black);
	rawText *autoWrap(rawText *rt, int maxLength, vec2 offset = 0, vec2 maxSize = -1, bool withCols = true, ConColor col = ConColor::white, ConColor backCol = ConColor::black);
}
