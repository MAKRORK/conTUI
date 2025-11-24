#include "TextTUI.h"

namespace ctui
{
	rawText *autoWrap(const std::string &input, int maxLength, bool withCols, ConColor col, ConColor backCol)
	{
		std::vector<std::string> lines;
		std::string cur = "";
		std::string affter_space = "";
		int after_space_len = 0;
		int cur_len = 0;
		int last_space = -1;
		bool ansi_started = false;

		attribute a = attribute(ConColor::getForeColor(col));
		a.addAttribute(ConColor::getBackColor(backCol));
		attribute c = attribute::clear;

		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == 0x1b)
			{
				ansi_started = true;
			}
			if (input[i] == '\n')
			{
				if (affter_space != "")
					lines.push_back(cur + " " + affter_space);
				else
					lines.push_back(cur);
				cur = "";
				affter_space = "";
				after_space_len = 0;
				last_space = -1;
				i++;
				if (input[i + 1] == ' ')
				{
					i++;
				}
				cur_len = 0;
				continue;
			}
			if (input[i] == ' ')
			{
				if (last_space != -1)
				{
					if (cur != "")
					{
						cur += ' ';
					}
					cur += affter_space;
					affter_space = "";
					cur_len += after_space_len;
					after_space_len = 0;
				}
				last_space = i;
				cur_len++;
				continue;
			}
			if ((cur_len + after_space_len) >= maxLength)
			{
				if (last_space > 0)
				{
					lines.push_back(cur);
					cur = affter_space;
					last_space = -1;
					cur_len = after_space_len;
					affter_space = "";
					after_space_len = 0;
				}
				else
				{
					lines.push_back(cur);
					cur = "";
					affter_space = "";
					last_space = -1;
					cur_len = 0;
					after_space_len = 0;
				}
			}
			if (last_space == -1)
			{
				cur += input[i];
				if (!ansi_started)
					cur_len++;
			}
			else
			{
				affter_space += input[i];
				if (!ansi_started)
					after_space_len++;
			}

			if (ansi_started && input[i] == 'm')
			{
				ansi_started = false;
				if (input[i - 1] == '0' && input[i - 2] == '[' && withCols)
				{
					if (last_space == -1)
					{
						cur += a.getAttributes();
					}
					else
					{
						affter_space += a.getAttributes();
					}
				}
			}
		}
		if (affter_space != "")
			lines.push_back(cur + " " + affter_space);
		else
			lines.push_back(cur);

		rawText *rt = new rawText(vec2(maxLength, (int)lines.size()));
		for (int i = 0; i < lines.size(); i++)
		{
			if (withCols)
				rt->txt[i] += a.getAttributes();
			rt->txt[i] += lines[i];
			if (withCols)
				rt->txt[i] += c.getAttributes();
		}
		return rt;
	}

	rawText *autoWrap(rawText *rt, int maxLength, bool withCols, ConColor col, ConColor backCol)
	{
		std::vector<rawText *> rts;
		int lines = 0;
		for (int i = 0; i < rt->size.y; i++)
		{
			rawText *rtt = autoWrap(rt->txt[i], maxLength, withCols, col, backCol);
			lines += rtt->size.y;
			rts.push_back(rtt);
		}
		rawText *r = new rawText(lines);
		for (int i = 0; i < rts.size(); i++)
		{
			for (int j = 0; j < rts[i]->size.y; j++)
			{
				r->txt[i] += rts[i]->txt[j];
			}
			delete rts[i];
		}
		return r;
	}
}