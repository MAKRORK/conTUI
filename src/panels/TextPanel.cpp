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
		r = autoWrap(txt, getAbsoluteSize().x, offset, maxSize, true, foreColor, backColor);
		return r;
	}

}