#include "ConColor.h"
#include "MathTUI.h"
#include <cmath>
#include "Log.h"

namespace ctui
{
	const ConColor ConColor::none = ConColor(-1);
	const ConColor ConColor::white = ConColor(0x7);
	const ConColor ConColor::grey = ConColor(0x7);
	const ConColor ConColor::black = ConColor();

	const ConColor ConColor::red = ConColor(0x1);
	const ConColor ConColor::green = ConColor(0x2);
	const ConColor ConColor::blue = ConColor(0x4);
	const ConColor ConColor::yellow = ConColor(0x3);
	const ConColor ConColor::purple = ConColor(0x5);
	const ConColor ConColor::moonstone = ConColor(0x6);

	const ConColor ConColor::ligth_red = ConColor::toBright(ConColor::red);
	const ConColor ConColor::ligth_green = ConColor::toBright(ConColor::green);
	const ConColor ConColor::ligth_blue = ConColor::toBright(ConColor::blue);
	const ConColor ConColor::ligth_yellow = ConColor::toBright(ConColor::yellow);
	const ConColor ConColor::magenta = ConColor::toBright(ConColor::purple);
	const ConColor ConColor::cyan = ConColor::toBright(ConColor::moonstone);

	ConColor::ConColor()
	{
		col = 0;
	}

	ConColor::ConColor(int c)
	{
		col = c;
	}

	ConColor ConColor::mix(const ConColor &c1, const ConColor &c2)
	{
		return ConColor(c1.col | c2.col);
	}

	int ConColor::getForeColor(const ConColor &col)
	{
		return col.col + 30;
	}

	int ConColor::getBackColor(const ConColor &col)
	{
		return col.col + 40;
	}

	ConColor ConColor::getColorFromRGB(int r, int g, int b, float gamma)
	{
		int c = 0;
		r = (int)round(powf((float)r / 255.f, gamma) * 2.f);
		g = (int)round(powf((float)g / 255.f, gamma) * 2.f);
		b = (int)round(powf((float)b / 255.f, gamma) * 2.f);

		if (r)
		{
			c |= 0b001;
		}
		if (g)
		{
			c |= 0b010;
		}
		if (b)
		{
			c |= 0b100;
		}
		if (r > 1 || g > 1 || b > 1)
			c += 60;
		return ConColor(c);
	}

	ConColor ConColor::toBright(const ConColor &col)
	{
		return col.col + 60;
	}
}