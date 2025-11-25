#pragma once
#include "Panel.h"
#include "ConColor.h"
#include "Rect.h"

namespace ctui
{
	class RectPanel : public Panel, public Rect
	{
	private:
	public:
		RectPanel(vec2 _pos = vec2(0), vec2 _size = vec2(0), char32_t _fillChar = U' ', ConColor _color = ConColor::grey, ConColor _backColor = ConColor::grey)
			: Panel(_pos, _size)
		{
			fillChar = _fillChar;
			color = _color;
			backColor = _backColor;
			debug_sym = U'R';
			corners[0] = topBorderChar;
			corners[1] = topBorderChar;
			corners[2] = bottomBorderChar;
			corners[3] = bottomBorderChar;
		}

		ctText getText() override;
		rawText *getRawText(vec2 offset, vec2 maxSize) override;
	};
}