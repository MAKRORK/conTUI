#pragma once
#include <vector>
#include <string>
#include "Base.h"
#include "ConColor.h"

namespace ctui
{
	rawText *autoWrap(const std::string &input, int maxLength, bool withCols = true, ConColor col = ConColor::white, ConColor backCol = ConColor::black);
	rawText *autoWrap(rawText *rt, int maxLength, bool withCols = true, ConColor col = ConColor::white, ConColor backCol = ConColor::black);
}
