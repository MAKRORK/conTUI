#include "OneLine.h"
#include "TextTUI.h"

#include <vector>

namespace ctui
{
	rawText *OneLine::getRawText(vec2 offset, vec2 maxSize, vec2 size)
	{
		std::vector<int> rl;
		rawText *rt = autoWrap(line, (int)line.size() + 1, offset, maxSize, rl, true, foreColor, backColor);
		rawText *rrr = new rawText(vec2(size.x, 1));
		attribute a = attribute(ConColor::getForeColor(foreColor));
		a.addAttribute(ConColor::getBackColor(backColor));
		int l = getRealLength(line);
		if (textAlign == AlignHorizontal::CENTER)
		{
			rrr->txt[0] += a.getAttributes();
			rrr->txt[0] += getLine((size.x - l) / 2);
			rrr->txt[0] += rt->txt[0];
			rrr->txt[0] += a.getAttributes();
			rrr->txt[0] += getLine((size.x - l) / 2);
			rrr->txt[0] += attribute::clear.getAttributes();
		}
		else if (textAlign == AlignHorizontal::RIGHT)
		{
			rrr->txt[0] += a.getAttributes();
			rrr->txt[0] += getLine((size.x - l));
			rrr->txt[0] += rt->txt[0];
			rrr->txt[0] += attribute::clear.getAttributes();
		}
		else
		{
			rrr->txt[0] += a.getAttributes();
			rrr->txt[0] += rt->txt[0];
			rrr->txt[0] += a.getAttributes();
			rrr->txt[0] += getLine((size.x - l));
			rrr->txt[0] += attribute::clear.getAttributes();
		}
		delete rt;
		return rrr;
	}
}