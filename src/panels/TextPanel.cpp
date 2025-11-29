#include "panels/TextPanel.h"
#include "TextTUI.h"
#include "Log.h"

namespace ctui
{
	void TextPanel::setText(std::string _txt)
	{
		txt = _txt;
	}
	void TextPanel::addText(std::string _txt)
	{
		txt += _txt;
	}

	void TextPanel::setRawText(rawText *rt)
	{
		r = rt;
	}
	rawText *TextPanel::getRawText(vec2 offset, vec2 maxSize)
	{
		if (rawTextOut)
		{
			return r;
		}
		if (r)
		{
			delete r;
		}
		std::vector<int> realLens;
		rawText *rt = autoWrap(txt, getAbsoluteSize().x, offset, maxSize, realLens, true, foreColor, backColor);
		vec2 s = getAbsoluteSize();
		int l = rt->size.y;
		if (rt->size.y < s.y)
		{
			if (textAlignVertical == AlignVertical::CENTER)
				l += (s.y - rt->size.y) / 2;
			else if (textAlignVertical == AlignVertical::BOTTOM)
				l += (s.y - rt->size.y);
		}
		int o = l - rt->size.y;
		r = new rawText(vec2(s.x, l));
		attribute a = attribute(ConColor::getForeColor(foreColor));
		a.addAttribute(ConColor::getBackColor(backColor));
		if (fillStrings)
		{
			for (int i = 0; i < rt->size.y; i++)
			{
				std::string st = a.getAttributes();
				std::string fn = a.getAttributes();
				int l = (s.x - realLens[i]);
				if (textAlignHorizontal == AlignHorizontal::CENTER)
				{
					int d = l / 2;
					st += getLine(d);
					fn += getLine(l - d);
				}
				else if (textAlignHorizontal == AlignHorizontal::RIGHT)
				{
					st += getLine(l);
				}
				else if (textAlignHorizontal == AlignHorizontal::LEFT)
				{
					fn += getLine(l);
				}
				st += attribute::clear.getAttributes();
				fn += attribute::clear.getAttributes();
				if (fillLast || i < rt->size.y - 1)
					r->txt[i + o] += st + rt->txt[i] + fn;
				else
				{
					r->txt[i + o] += st + rt->txt[i];
				}
			}
		}
		else
		{
			for (int i = 0; i < rt->size.y; i++)
			{
				std::string st = "";
				if (textAlignHorizontal == AlignHorizontal::CENTER)
				{
					r->offsets[i + o] = (s.x - realLens[i]) / 2;
				}
				else if (textAlignHorizontal == AlignHorizontal::RIGHT)
				{
					r->offsets[i + o] = (s.x - realLens[i]);
				}
				r->txt[i + o] += st + rt->txt[i];
			}
		}
		return r;
	}

}