#pragma once
#include "Input.h"
#include "OneLine.h"

namespace ctui
{
	class OneLineButton : public Input
	{
	private:
		OneLine oneLine = OneLine();
		ConColor foreColor = ConColor::black;
		ConColor backColor = ConColor::white;
		ConColor hoverForeColor = ConColor::white;
		ConColor hoverBackColor = ConColor::black;
		void updateNormalState();
		void updateHoverState();

	public:
		OneLineButton(vec2 _idGridInput, vec2 _pos, int length) : Input(_idGridInput, _pos, vec2(length, 1))
		{
			oneLine.setForeColor(foreColor);
			oneLine.setBackColor(backColor);
		}
		rawText *getRawText(vec2 offset, vec2 maxSize) override;
		OneLine *getStyleLine() { return &oneLine; }
		void setLineText(std::string str) { oneLine.setLineText(str); }

		void setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV) override;

		void setForeColor(ConColor _foreColor)
		{
			foreColor = _foreColor;
			updateNormalState();
		}
		void setBackColor(ConColor _backColor)
		{
			backColor = _backColor;
			updateNormalState();
		}
		void setHoverForeColor(ConColor _hoverForeColor)
		{
			hoverForeColor = _hoverForeColor;
			updateHoverState();
		}
		void setHoverBackColor(ConColor _hoverBackColor)
		{
			hoverBackColor = _hoverBackColor;
			updateHoverState();
		}

		void startActive() override;
		void startDisActive() override;
	};
}