#pragma once
#include "Input.h"
#include "ConColor.h"
#include "Rect.h"

namespace ctui
{
	class RectButton : public Input
	{
	private:
		Rect normalStyle = Rect();
		Rect hoverStyle = Rect();

	public:
		RectButton(vec2 _idGridInput, vec2 _pos = vec2(0), vec2 _size = vec2(0)) : Input(_idGridInput, _pos, _size) {}

		Rect *getNormalStyleRect() { return &normalStyle; }
		Rect *getHoverStyleRect() { return &hoverStyle; }

		rawText *getRawText(vec2 offset, vec2 maxSize);
	};

}