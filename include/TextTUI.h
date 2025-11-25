#pragma once
#include <vector>
#include <string>
#include "Base.h"
#include "ConColor.h"

namespace ctui
{
	rawText *autoWrap(const std::string &input, int maxLength, vec2 offset = 0, vec2 maxSize = -1, bool withCols = true, ConColor col = ConColor::white, ConColor backCol = ConColor::black);
	rawText *autoWrap(rawText *rt, int maxLength, vec2 offset = 0, vec2 maxSize = -1, bool withCols = true, ConColor col = ConColor::white, ConColor backCol = ConColor::black);
}
