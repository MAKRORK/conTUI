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
		Log::getLog()->logString("x = " + std::to_string(getAbsoluteSize().x));
		r = autoWrap(txt, getAbsoluteSize().x, true, foreColor, backColor);
		return r;
	}
}