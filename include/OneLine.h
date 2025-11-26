#pragma once
#include <string>
#include "Base.h"
#include "ConColor.h"

namespace ctui
{
	class OneLine : public Base
	{
	private:
		std::string line = "";
		ConColor foreColor = ConColor::black;
		ConColor backColor = ConColor::white;
		AlignHorizontal textAlign = AlignHorizontal::LEFT;

	public:
		rawText *getRawText(vec2 offset, vec2 maxSize, vec2 size) override;
		void setForeColor(ConColor _foreColor) { foreColor = _foreColor; }
		void setBackColor(ConColor _backColor) { backColor = _backColor; }
		void setTextAlign(AlignHorizontal _textAlign) { textAlign = _textAlign; }
		void setLineText(std::string str) { line = str; }
	};
}