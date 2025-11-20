#pragma once
#include "Panel.h"
#include "ConColor.h"

namespace ctui
{
	class RectPanel : public Panel
	{
	private:
		char32_t leftBorderChar = U'|';
		char32_t rigthBorderChar = U'|';
		char32_t topBorderChar = U'=';
		char32_t bottomBorderChar = U'|';
		char32_t fillChar;
		char32_t corners[4];
		bool border = false;
		bool uniqCorner = false;
		ConColor color;
		ConColor borderColor;
		ConColor backColor;
		ConColor backBorderColor;

	public:
		RectPanel(vec2 _pos = vec2(0), vec2 _size = vec2(0), char32_t _fillChar = U' ', ConColor _color = ConColor::grey, ConColor _backColor = ConColor::grey)
			: Panel(_pos, _size), fillChar(_fillChar), color(_color), backColor(_backColor)
		{
			debug_sym = U'R';
			corners[0] = topBorderChar;
			corners[1] = topBorderChar;
			corners[2] = bottomBorderChar;
			corners[3] = bottomBorderChar;
		}
		void setBorder(bool _border, ConColor _borderColor,
					   ConColor _backBorderColor, char32_t _leftBorderChar, char32_t _rigthBorderChar, char32_t _topBorderChar, char32_t _bottomBorderChar);
		void setBorder(bool _border);
		void setBorder(bool _border, ConColor _borderColor,
					   ConColor _backBorderColor, char32_t hborderChar, char32_t vborderChar);
		void setUniqueCorners(bool _uniqCorner, char32_t ltc, char32_t rtc, char32_t lbc, char32_t rbc);
		void setUniqueCorners(bool _uniqCorner, char32_t corner);
		void setUniqueCorners(bool _uniqCorner);

		void setFillStyle(char32_t _fillChar, ConColor _color, ConColor _backColor);
		void setFillStyle(ConColor fillColor);

		ctText getText() override;
		rawText *getRawText(vec2 offset, vec2 maxSize) override;
	};
}