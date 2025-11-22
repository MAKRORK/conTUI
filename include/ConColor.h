#pragma once
#include <windows.h>

namespace ctui
{
	class ConColor
	{
	private:
		int col;

	public:
		ConColor();
		ConColor(int c);

		static ConColor mix(const ConColor &c1, const ConColor &c2);

		static int getForeColor(const ConColor &col);
		static int getBackColor(const ConColor &col);

		static ConColor getColorFromRGB(int r, int g, int b, float gamma = 2.2f);

		static ConColor toBright(const ConColor &col);

		bool operator==(const ConColor &other) const
		{
			return col == other.col;
		}

		bool operator!=(const ConColor &other) const
		{
			return !(*this == other);
		}

		static const ConColor none;

		static const ConColor white;
		static const ConColor grey;
		static const ConColor black;

		static const ConColor red;
		static const ConColor green;
		static const ConColor blue;
		static const ConColor yellow;
		static const ConColor purple;
		static const ConColor moonstone;

		static const ConColor ligth_red;
		static const ConColor ligth_green;
		static const ConColor ligth_blue;
		static const ConColor ligth_yellow;
		static const ConColor magenta;
		static const ConColor cyan;
	};
}