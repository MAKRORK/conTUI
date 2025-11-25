#include "panels/RectPanel.h"
#include "ConsoleBase.h"

namespace ctui
{
	ctText RectPanel::getText()
	{
		attribute a = attribute(ConColor::getForeColor(color));
		a.addAttribute(ConColor::getForeColor(backColor));
		ctText ct = ctText(getAbsoluteSize(), symbol(fillChar, a));
		vec2 s = getAbsoluteSize();
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
		if (this->r)
			delete r;
		r = Rect::getRawText(offset, maxSize, getAbsoluteSize());
		return r;
	}
}
