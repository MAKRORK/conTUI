#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "MathTUI.h"

namespace ctui
{

	struct attribute
	{
		std::vector<int> atts;
		attribute() {}
		attribute(int _a)
		{
			atts.push_back(_a);
		}
		void addAttribute(int _a)
		{
			atts.push_back(_a);
		}
		std::string getAttributes()
		{
			if (atts.empty())
			{
				return "";
			}
			std::string s = "\x1b[";
			for (int i = 0; i < atts.size(); i++)
			{
				s += std::to_string(atts[i]);
				if (i != atts.size() - 1)
				{
					s += ";";
				}
			}
			return s + "m";
		}
		attribute(const attribute &attr);
	};
	struct rawText
	{
		std::string *txt = nullptr;
		vec2 size;
		rawText(vec2 _size = vec2(0)) : size(_size)
		{
			txt = new std::string[size.y];
			for (int i = 0; i < size.y; i++)
			{
				txt[i] = "";
			}
		}
		~rawText()
		{
			// std::cout << "raw deleted\n";
			delete[] txt;
		}
	};

	struct symbol
	{
		char32_t chr;
		attribute attr;
		symbol(char32_t _chr = ' ', attribute _attr = attribute()) : chr(_chr), attr(_attr) {}
		symbol(const symbol &sym);
	};
	struct ctText
	{
		symbol **txt = nullptr;
		vec2 size;
		ctText(vec2 _size = vec2(0), symbol fillChar = symbol());
		~ctText();
		void setChr(int x, int y);
		symbol *getSym(int x, int y);
		bool empty();
	};

	enum class AlignHorizontal
	{
		LEFT,
		CENTER,
		RIGHT,
		FULL
	};
	enum class AlignVertical
	{
		TOP,
		CENTER,
		BOTTOM,
		FULL
	};
	enum class PositionType
	{
		Relative,
		Absolute
	};

	struct style
	{
		PositionType posType;
		AlignHorizontal alignH;
		AlignVertical alignV;
		style(PositionType _posType = PositionType::Absolute, AlignHorizontal _alignH = AlignHorizontal::LEFT, AlignVertical _alignV = AlignVertical::TOP)
			: posType(_posType), alignH(_alignH), alignV(_alignV) {}
	};

	class Attribute
	{
	public:
		const static int bold = 1;
		const static int dim = 2;
		const static int italic = 3;
		const static int underlined = 4;
		const static int slow_blink = 5;
		const static int fast_blink = 6;
		const static int inverted_colors = 7;
		const static int hide = 8;
		const static int crossed_out = 9;
	};
};
