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
double ctui::pov(double a, int p)
{
	for (int i = 1; i < p; i++)
	{
		a *= a;
	}
	return a;
}
int ctui::clamp(int a, int mn, int mx)
{
	if (a < mn)
		return mn;
	if (a > mx)
	{
		return mx;
	}
	return a;
}
int ctui::snake(int a, int mx)
{
	if (a < 0)
		return mx + a;
	if (a >= mx)
		return a - mx;
	return a;
}