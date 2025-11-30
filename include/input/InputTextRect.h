#pragma once
#include "Input.h"
#include "Rect.h"
#include "panels/TextPanel.h"

namespace ctui
{
	class InputTextRect : public Input
	{
	private:
		Rect normalRect = Rect();
		Rect hoverRect = Rect();
		int txtCursorPos = 0;
		vec2 realCursorPos = vec2(0);
		std::vector<int> realLens;

		int getTextCursorPos(vec2 realPos, vec2 cps, std::vector<int> &lens, vec2 size);
		vec2 getRealCursorPos(int txtPos, std::vector<int> &lens);

		vec2 selected = vec2(0, 0);
		attribute selectedTextStyle = attribute();
		ConColor textColor = ConColor::white;

		bool selectStarted = false;
		int selectStartPoint = -1;

		TextPanel *tp = nullptr;
		std::string txt = "";
		std::vector<char32_t> txtt;
		int textVerticalOffset = 0;

	public:
		InputTextRect(vec2 _idGridInput, vec2 _pos = vec2(0), vec2 _size = vec2(0)) : Input(_idGridInput, _pos, _size)
		{
			tp = new TextPanel(vec2(0), vec2(1));
			tp->setStyle(PositionType::Relative, AlignHorizontal::FULL, AlignVertical::FULL);
			tp->setFillStrings(true, false);
			tp->setRawTextOut(true);
			setTextColor(textColor);
			selectedTextStyle.addAttribute(ConColor::getForeColor(ConColor::white));
			selectedTextStyle.addAttribute(ConColor::getBackColor(ConColor::grey));
			this->addChild(tp);
		}

		void accept() override;
		void updateInput() override;

		rawText *getRawText(vec2 offset, vec2 maxSize);

		void setTextColor(ConColor col);
		void setSelectedTextAttribute(attribute attr) { selectedTextStyle = attr; }

		void setTextPadding(int p);
		void setTextPadding(int l, int t, int r, int b);
		Rect *getNormalStyleRect() { return &normalRect; }
		Rect *getHoverStyleRect() { return &hoverRect; }
	};
}