#pragma once

#include "Panel.h"
#include "ConColor.h"

namespace ctui
{
	class TextPanel : public Panel
	{
	private:
		ConColor foreColor = ConColor::white;
		ConColor backColor = ConColor::black;
		std::string txt = "";
		AlignHorizontal textAlignHorizontal = AlignHorizontal::LEFT;
		AlignVertical textAlignVertical = AlignVertical::TOP;

	public:
		TextPanel(vec2 _pos, vec2 _size) : Panel(_pos, _size) {}
		void setText(std::string _txt);

		rawText *getRawText(vec2 offset, vec2 maxSize) override;
		void setForeColor(ConColor _foreColor) { foreColor = _foreColor; }
		void setBackColor(ConColor _backColor) { backColor = _backColor; }

		void setTextAlignHorizontal(AlignHorizontal _textAlignHorizontal) { textAlignHorizontal = _textAlignHorizontal; }
		void setTextAlignVertical(AlignVertical _textAlignVertical) { textAlignVertical = _textAlignVertical; }

		AlignHorizontal getTextAlignHorizontal() { return textAlignHorizontal; }
		AlignVertical getTextAlignVertical() { return textAlignVertical; }
	};
}