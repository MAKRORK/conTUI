#pragma once
#include "Box.h"

namespace ctui
{
	class HorizontalBox : public Box
	{
	public:
		HorizontalBox(vec2 _pos = vec2(0), vec2 _size = vec2(0)) : Box(_pos, _size)
		{
			debug_sym = 'H';
		}
		vec2 getPanelLocalPos(Panel *p) override;
		vec2 getPanelLocalSize(Panel *p) override;
	};
}