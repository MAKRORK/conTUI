#include "panels/TextPanel.h"
#include "TextTUI.h"
#include "Log.h"

namespace ctui
{
	void TextPanel::setText(std::string _txt)
	{
		txt = _txt;
	}
	rawText *TextPanel::getRawText(vec2 offset, vec2 maxSize)
	{
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
		for (int i = 0; i < rt->size.y; i++)
		{
			std::string st = "";
			if (textAlignHorizontal == AlignHorizontal::CENTER)
			{
				r->offsets[i + o] = (s.x - realLens[i]) / 2;
			}
			if (textAlignHorizontal == AlignHorizontal::RIGHT)
			{
				r->offsets[i + o] = (s.x - realLens[i]);
			}
			r->txt[i + o] += st + rt->txt[i];
		}
		return r;
	}

}