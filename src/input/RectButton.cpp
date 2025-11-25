#include "input/RectButton.h"
#include "ConsoleBase.h"

namespace ctui
{
	rawText *RectButton::getRawText(vec2 offset, vec2 maxSize)
	{
		if (r)
			delete r;
		if (getIsActive())
		{
			r = hoverStyle.getRawText(offset, maxSize, getAbsoluteSize());
		}
		else
			r = normalStyle.getRawText(offset, maxSize, getAbsoluteSize());
		return r;
	}
}