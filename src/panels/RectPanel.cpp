#include "panels/RectPanel.h"
#include "ConsoleBase.h"

namespace ctui
{
	ctText RectPanel::getText()
	{
		attribute a = attribute(ConColor::getForeColor(color));
		a.addAttribute(ConColor::getForeColor(backColor));
		ctText ct = ctText(getSize(), symbol(fillChar, a));
		vec2 s = getSize();
		if (border)
		{
			int st = 0, fn = s.x;
			int fny = s.y;
			if (uniqCorner)
			{
				ct.getSym(0, 0)->chr = corners[0];
				ct.getSym(0, 0)->attr.addAttribute(ConColor::getForeColor(borderColor));
				ct.getSym(0, 0)->attr.addAttribute(ConColor::getBackColor(backBorderColor));
				ct.getSym(s.x - 1, 0)->chr = corners[1];
				ct.getSym(s.x - 1, 0)->attr.addAttribute(ConColor::getForeColor(borderColor));
				ct.getSym(s.x - 1, 0)->attr.addAttribute(ConColor::getBackColor(backBorderColor));

				ct.getSym(0, s.y - 1)->chr = corners[2];
				ct.getSym(0, s.y - 1)->attr.addAttribute(ConColor::getForeColor(borderColor));
				ct.getSym(0, s.y - 1)->attr.addAttribute(ConColor::getBackColor(backBorderColor));
				ct.getSym(s.x - 1, s.y - 1)->chr = corners[3];
				ct.getSym(s.x - 1, s.y - 1)->attr.addAttribute(ConColor::getForeColor(borderColor));
				ct.getSym(s.x - 1, s.y - 1)->attr.addAttribute(ConColor::getBackColor(backBorderColor));
				st += 1;
				fn -= 1;
				fny -= 1;
			}

			for (int i = st; i < fn; i++)
			{
				ct.getSym(i, 0)->chr = topBorderChar;
				ct.getSym(i, 0)->attr.addAttribute(ConColor::getForeColor(borderColor));
				ct.getSym(i, 0)->attr.addAttribute(ConColor::getBackColor(backBorderColor));
			}
			for (int i = st; i < fn; i++)
			{
				ct.getSym(i, s.y - 1)->chr = topBorderChar;
				ct.getSym(i, s.y - 1)->attr.addAttribute(ConColor::getForeColor(borderColor));
				ct.getSym(i, s.y - 1)->attr.addAttribute(ConColor::getBackColor(backBorderColor));
			}

			for (int i = 1; i < fny; i++)
			{
				ct.getSym(0, i)->chr = leftBorderChar;
				ct.getSym(0, i)->attr.addAttribute(ConColor::getForeColor(borderColor));
				ct.getSym(0, i)->attr.addAttribute(ConColor::getBackColor(backBorderColor));
				for (int j = st; j < fn; i++)
				{
					ct.getSym(j, i)->chr = fillChar;
					ct.getSym(j, i)->attr.addAttribute(ConColor::getForeColor(borderColor));
					ct.getSym(j, i)->attr.addAttribute(ConColor::getBackColor(backBorderColor));
				}
				ct.getSym(s.x - 1, i)->chr = topBorderChar;
				ct.getSym(s.x - 1, i)->attr.addAttribute(ConColor::getForeColor(borderColor));
				ct.getSym(s.x - 1, i)->attr.addAttribute(ConColor::getBackColor(backBorderColor));
			}
		}
		else
		{
			for (int i = 0; i < s.y; i++)
			{
				for (int j = 0; j < s.x; i++)
				{
					ct.getSym(j, i)->chr = fillChar;
					ct.getSym(j, i)->attr.addAttribute(ConColor::getForeColor(borderColor));
					ct.getSym(j, i)->attr.addAttribute(ConColor::getBackColor(backBorderColor));
				}
			}
		}

		return ct;
	}
	rawText *RectPanel::getRawText(vec2 offset, vec2 maxSize)
	{
		vec2 s = getSize();
		if (this->r)
			delete r;
		r = new rawText(maxSize - offset);
		attribute b = attribute(ConColor::getForeColor(borderColor));
		b.addAttribute(ConColor::getBackColor(backBorderColor));
		attribute a = attribute(ConColor::getForeColor(color));
		a.addAttribute(ConColor::getBackColor(backColor));
		attribute c = attribute(0);
		int stx = offset.x;
		int sty = offset.y;
		int fn = maxSize.x;
		int fny = maxSize.y;
		if (border && offset.y == 0)
		{

			int l = maxSize.x - offset.x;
			r->txt[0] += b.getAttributes();
			if (uniqCorner && (offset.x == 0))
			{
				ConsoleBase::addCharToString(r->txt[0], corners[0]);
				l--;
			}
			if (uniqCorner && maxSize.x == s.x)
				l--;
			ConsoleBase::addCharToString(r->txt[0], topBorderChar, l);
			if (uniqCorner && (maxSize.x == s.x))
			{
				ConsoleBase::addCharToString(r->txt[0], corners[1]);
			}
			r->txt[0] += c.getAttributes();
			sty += 1;
		}
		if (border && (maxSize.y == s.y))
			fny -= 1;
		if (border && offset.x == 0)
			stx += 1;
		if (border && (maxSize.x == s.x))
			fn -= 1;
		for (int i = sty; i < fny; i++)
		{
			if (border && offset.x == 0)
			{
				r->txt[i - offset.y] += b.getAttributes();
				ConsoleBase::addCharToString(r->txt[i - offset.y], leftBorderChar);
				r->txt[i - offset.y] += c.getAttributes();
			}
			r->txt[i - offset.y] += a.getAttributes();

			ConsoleBase::addCharToString(r->txt[i - offset.y], fillChar, fn - stx);
			r->txt[i - offset.y] += c.getAttributes();

			if (border && (maxSize.x == s.x))
			{
				r->txt[i - offset.y] += b.getAttributes();
				ConsoleBase::addCharToString(r->txt[i - offset.y], rigthBorderChar);
				r->txt[i - offset.y] += c.getAttributes();
			}
		}
		if (border && (maxSize.y == s.y))
		{
			int l = maxSize.x - offset.x;
			r->txt[s.y - offset.y - 1] += b.getAttributes();
			if (uniqCorner && (offset.x == 0))
			{
				ConsoleBase::addCharToString(r->txt[s.y - offset.y - 1], corners[2]);
				l--;
			}
			if (uniqCorner && maxSize.x == s.x)
				l--;
			ConsoleBase::addCharToString(r->txt[s.y - offset.y - 1], bottomBorderChar, l);
			if (uniqCorner && (maxSize.x == s.x))
			{
				ConsoleBase::addCharToString(r->txt[s.y - offset.y - 1], corners[3]);
			}
			r->txt[s.y - offset.y - 1] += c.getAttributes();
		}
		return r;
	}

	void RectPanel::setBorder(bool _border, ConColor _borderColor, ConColor _backBorderColor, char32_t hborderChar, char32_t vborderChar)
	{
		setBorder(_border, _borderColor, _backBorderColor, hborderChar, hborderChar, vborderChar, vborderChar);
	}

	void RectPanel::setBorder(bool _border, ConColor _borderColor, ConColor _backBorderColor, char32_t _leftBorderChar, char32_t _rigthBorderChar, char32_t _topBorderChar, char32_t _bottomBorderChar)
	{
		setBorder(_border);
		topBorderChar = _topBorderChar;
		bottomBorderChar = _bottomBorderChar;
		leftBorderChar = _leftBorderChar;
		rigthBorderChar = _rigthBorderChar;
		borderColor = _borderColor;
		backBorderColor = _backBorderColor;
	}
	void RectPanel::setBorder(bool _border)
	{
		border = _border;
	}

	void RectPanel::setUniqueCorners(bool _uniqCorner, char32_t ltc, char32_t rtc, char32_t lbc, char32_t rbc)
	{
		setUniqueCorners(_uniqCorner);
		corners[0] = ltc;
		corners[1] = rtc;
		corners[2] = lbc;
		corners[3] = rbc;
	}
	void RectPanel::setUniqueCorners(bool _uniqCorner, char32_t corner)
	{
		setUniqueCorners(_uniqCorner, corner, corner, corner, corner);
	}
	void RectPanel::setUniqueCorners(bool _uniqCorner)
	{
		uniqCorner = _uniqCorner;
	}

	void RectPanel::setFillStyle(char32_t _fillChar, ConColor _color, ConColor _backColor)
	{
		fillChar = _fillChar;
		color = _color;
		backColor = _backColor;
	}
	void RectPanel::setFillStyle(ConColor fillColor)
	{
		setFillStyle(U' ', fillColor, fillColor);
	}
}
