#include "MathTUI.h"

bool ctui::vec2::inRect(vec2 _p, vec2 _s)
{
	if (x >= _p.x && x <= _p.x + _s.x)
	{
		if (y >= _p.y && y <= _p.y + _s.y)
		{
			return true;
		}
	}
	return false;
}
int ctui::ctmin(int a, int b)
{
	if (a < b)
		return a;
	return b;
}
int ctui::ctmax(int a, int b)
{
	if (a < b)
		return b;
	return a;
}