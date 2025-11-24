#pragma once
#include "TextPanel.h"

namespace ctui
{
	class MarkdownTextPanel : public TextPanel
	{
	private:
	public:
		MarkdownTextPanel(vec2 _pos, vec2 _size) : TextPanel(_pos, _size) {}
	};
}