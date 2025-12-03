#pragma once
#include "Input.h"
#include "ConColor.h"
#include "OneLine.h"

namespace ctui
{
	class InputTextLine : public Input
	{
	private:
		OneLine oneLine = OneLine();
		ConColor foreColor = ConColor::white;
		ConColor backColor = ConColor::black;
		ConColor hoverForeColor = ConColor::black;
		ConColor hoverBackColor = ConColor::white;

		int txtCursorPos = 0;

		vec2 selected = vec2(0, 0);
		attribute selectedTextStyle = attribute();
		ConColor textColor = ConColor::white;

		bool selectStarted = false;
		int selectStartPoint = -1;

		std::string txt = "";
		std::vector<char32_t> txtt;
		int textHorizontalOffset = 0;

		std::vector<char32_t> getTextWithOffset(std::vector<char32_t> &txtv, int offset, int maxLength);

		void updateNormalState();
		void updateHoverState();

	public:
		InputTextLine(vec2 _idGridInput, vec2 _pos = vec2(0), vec2 _size = vec2(0)) : Input(_idGridInput, _pos, _size)
		{
			selectedTextStyle.addAttribute(ConColor::getForeColor(ConColor::white));
			selectedTextStyle.addAttribute(ConColor::getBackColor(ConColor::grey));
			oneLine.setForeColor(foreColor);
			oneLine.setBackColor(backColor);
		}

		void accept() override;
		void updateInput() override;
		rawText *getRawText(vec2 offset, vec2 maxSize);

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

		void setSelectedTextAttribute(attribute attr) { selectedTextStyle = attr; }
		void setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV) override;

		void startActive() override;
		void startDisActive() override;
	};
}