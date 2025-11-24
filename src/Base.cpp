#include "Base.h"

namespace ctui
{
	attribute attribute::clear = attribute(0);
	ctText::ctText(vec2 _size, symbol fillChar)
	{
		size = _size;
		if (size.x != 0 && size.y != 0)
		{
			txt = new symbol *[size.y];
			for (int i = 0; i < size.y; i++)
			{
				txt[i] = new symbol[size.x];
				for (int j = 0; j < size.x; j++)
				{
					txt[i][j] = symbol(fillChar);
				}
			}
		}
	}
	ctText::~ctText()
	{
		if (txt)
		{
			for (int i = 0; i < size.y; i++)
			{
				delete[] txt[i];
			}
			delete[] txt;
		}
	}
	void ctText::setChr(int x, int y)
	{
	}
	symbol *ctText::getSym(int x, int y)
	{
		return &txt[y][x];
	}
	bool ctText::empty()
	{
		return size.x == 0 || size.y == 0;
	}
	symbol::symbol(const symbol &sym)
	{
		chr = sym.chr;
		attr = attribute(sym.attr);
	}
	attribute::attribute(const attribute &attr)
	{
		atts = attr.atts;
	}
}