#include "input/OneLineButton.h"

namespace ctui
{
	rawText *OneLineButton::getRawText(vec2 offset, vec2 maxSize)
	{
		if (r)
			delete r;
		r = oneLine.getRawText(offset, maxSize, getAbsoluteSize());
		return r;
	}
	void OneLineButton::setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV)
	{
		if (_alignV == AlignVertical::FULL)
		{
			_alignV = AlignVertical::CENTER;
		}
		Panel::setStyle(_posType, _alignH, _alignV);
	}

	void OneLineButton::updateNormalState()
	{
		if (!getIsActive())
		{
			oneLine.setForeColor(foreColor);
			oneLine.setBackColor(backColor);
		}
	}

	void OneLineButton::updateHoverState()
	{
		if (getIsActive())
		{
			oneLine.setForeColor(hoverForeColor);
			oneLine.setBackColor(hoverBackColor);
		}
	}

	void OneLineButton::startActive()
	{
		oneLine.setForeColor(hoverForeColor);
		oneLine.setBackColor(hoverBackColor);
	}

	void OneLineButton::startDisActive()
	{
		oneLine.setForeColor(foreColor);
		oneLine.setBackColor(backColor);
	}
}