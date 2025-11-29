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
		bool fillStrings = false;
		bool fillLast = true;
		bool rawTextOut = false;

	public:
		TextPanel(vec2 _pos, vec2 _size) : Panel(_pos, _size) {}
		void setText(std::string _txt);
		void addText(std::string _txt);
		void setRawText(rawText *rt);

		rawText *getRawText(vec2 offset, vec2 maxSize) override;
		void setForeColor(ConColor _foreColor) { foreColor = _foreColor; }
		void setBackColor(ConColor _backColor) { backColor = _backColor; }
		void setRawTextOut(bool _rawTextOut) { rawTextOut = _rawTextOut; }

		ConColor getForeColor() { return foreColor; }
		ConColor getBackColor() { return backColor; }

		void setTextAlignHorizontal(AlignHorizontal _textAlignHorizontal) { textAlignHorizontal = _textAlignHorizontal; }
		void setTextAlignVertical(AlignVertical _textAlignVertical) { textAlignVertical = _textAlignVertical; }

		void setFillStrings(bool _fillStrings, bool _fillLast = true)
		{
			fillStrings = _fillStrings;
			fillLast = _fillLast;
		}

		AlignHorizontal getTextAlignHorizontal() { return textAlignHorizontal; }
		AlignVertical getTextAlignVertical() { return textAlignVertical; }
	};
}