#pragma once
#include "ConColor.h"
#include "Base.h"

namespace ctui
{
	class Rect : public Base
	{
	protected:
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
		rawText *getRawText(vec2 offset, vec2 maxSize, vec2 size) override;
	};

}