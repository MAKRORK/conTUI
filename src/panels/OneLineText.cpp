#include "panels/OneLineText.h"

namespace ctui
{
	rawText *OneLineText::getRawText(vec2 offset, vec2 maxSize)
	{
		if (r)
			delete r;
		r = oneLine.getRawText(offset, maxSize, getAbsoluteSize());
		return r;
	}
	void OneLineText::setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV)
	{
		if (_alignV == AlignVertical::FULL)
		{
			_alignV = AlignVertical::CENTER;
		}
		Panel::setStyle(_posType, _alignH, _alignV);
	}
}