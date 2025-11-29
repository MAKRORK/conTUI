#include "TextTUI.h"
#include "Log.h"

namespace ctui
{

	std::string getLineWithOffset(std::string input, int offset, int maxSize)
	{
		bool ansi_started = false;
		bool unicode_started = false;
		std::string ansi = "";
		std::string output = "";
		int real_len = 0;
		for (int i = 0; i < input.size(); i++)
		{
			if (maxSize != -1 && real_len - offset >= maxSize)
			{
				return output;
			}
			if (input[i] == 0x1b)
			{
				ansi_started = true;
			}
			if (real_len < offset)
			{
				if (ansi_started)
				{
					ansi += input[i];
				}
			}
			else
			{
				output += input[i];
			}
			if (!ansi_started)
			{
				if (unicode_started && !isUnicodeCont(input[i + 1]))
				{
					unicode_started = false;
					real_len++;
				}
				else if (isUnicodeStart(input[i]) && isUnicodeCont(input[i + 1]))
				{
					unicode_started = true;
				}
				else if (!unicode_started)
				{
					real_len++;
				}
			}

			if (ansi_started && input[i] == 'm')
			{
				ansi_started = false;
				if (input[i - 1] == '0' && input[i - 2] == '[')
				{
					ansi = "";
				}
			}
		}
		return output;
	}
	std::string getLine(int n, char c)
	{
		std::string s = "";
		for (int i = 0; i < n; i++)
			s += c;
		return s;
	}
	bool isUnicodeCont(unsigned char c)
	{
		c = c >> 6;
		if (c == 0b10)
			return true;
		return false;
	}
	bool isUnicodeStart(unsigned char c)
	{
		c = c >> 3;
		if (c == 0b11110)
			return true;
		c = c >> 1;
		if (c == 0b1110)
			return true;
		c = c >> 1;
		if (c == 0b110)
			return true;
		return false;
	}

	int getRealLength(std::string &str)
	{
		int l = 0;
		bool ansi_started = false;
		bool unicode_started = false;
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == 0x1b)
			{
				ansi_started = true;
			}
			if (!ansi_started)
			{
				if (unicode_started && !isUnicodeCont(str[i]))
				{
					unicode_started = false;
				}
				if (isUnicodeStart(str[i]) && isUnicodeCont(str[i + 1]))
				{
					unicode_started = true;
					l++;
				}
				if (!unicode_started)
				{
					l++;
				}
			}
			if (ansi_started && str[i] == 'm')
			{
				ansi_started = false;
			}
		}
		return l;
	}

	std::vector<char32_t> stringToChars(std::string &str)
	{
		std::vector<char32_t> chrs;
		for (int i = 0; i < str.size(); i++)
		{
			unsigned char c = str[i];
			char32_t ch = 0x0;
			c = c >> 3;
			if (c == 0b11110)
			{
				ch += (unsigned char)str[i];
				ch = ch << 24;
				ch += (unsigned char)str[i + 1];
				ch = ch << 16;
				ch += (unsigned char)str[i + 2];
				ch = ch << 8;
				ch += (unsigned char)str[i + 3];
				chrs.push_back(ch);
				i += 3;
				continue;
			}
			c = c >> 1;
			if (c == 0b1110)
			{
				ch += (unsigned char)str[i];
				ch = ch << 16;
				ch += (unsigned char)str[i + 1];
				ch = ch << 8;
				ch += (unsigned char)str[i + 2];
				chrs.push_back(ch);
				i += 2;
				continue;
			}
			c = c >> 1;
			if (c == 0b110)
			{
				ch += (unsigned char)str[i];
				ch = ch << 8;
				ch += (unsigned char)str[i + 1];
				chrs.push_back(ch);
				i += 1;
				continue;
			}
			ch += (unsigned char)str[i];
			chrs.push_back(ch);
		}
		return chrs;
	}
	std::string chrsToString(std::vector<char32_t> &chrs)
	{
		std::string s = "";
		for (int i = 0; i < chrs.size(); i++)
		{
			char32_t c = chrs[i];
			unsigned char ch[4];
			ch[3] = (unsigned char)c;
			ch[2] = (unsigned char)(c >> 8);
			ch[1] = (unsigned char)(c >> 16);
			ch[0] = (unsigned char)(c >> 24);
			for (int j = 0; j < 4; j++)
			{
				if (ch[j] != 0)
				{
					s += ch[j];
				}
			}
		}
		return s;
	}

	rawText *autoWrap(const std::string &input, int maxLength, vec2 offset, vec2 maxSize, std::vector<int> &realLens, bool withCols, ConColor col, ConColor backCol)
	{
		std::vector<std::string> lines;
		std::string cur = "";
		std::string affter_space = "";
		int after_space_len = 0;
		int cur_len = 0;
		int last_space = -1;
		bool ansi_started = false;
		bool unicode_started = false;
		bool was_space = false;
		// std::vector<int> realLens;
		attribute a = attribute(ConColor::getForeColor(col));
		a.addAttribute(ConColor::getBackColor(backCol));
		attribute c = attribute::clear;

		for (int i = 0; i < input.size(); i++)
		{
			was_space = false;
			// Log::getLog()->logString(std::to_string((int)input[i]));
			if (input[i] == 0x1b)
			{
				ansi_started = true;
			}
			if (input[i] == '\n')
			{
				if (affter_space != "")
				{

					lines.push_back(getLineWithOffset(cur + affter_space, offset.x, maxSize.x));
					realLens.push_back(ctmin(cur_len + 1 + after_space_len, maxSize.x - offset.x));
				}
				else
				{
					lines.push_back(getLineWithOffset(cur, offset.x, maxSize.x));
					realLens.push_back(ctmin(cur_len + 1, maxSize.x - offset.x));
				}
				cur = "";
				affter_space = "";
				after_space_len = 0;
				last_space = -1;
				// i++;
				// if (input[i + 1] == ' ')
				//{
				//	i++;
				//}
				cur_len = 0;
				continue;
			}
			if (input[i] == ' ')
			{

				if (last_space != -1)
				{

					cur += affter_space;
					affter_space = "";
					cur_len += after_space_len;
					after_space_len = 0;
					was_space = true;
				}
				cur += ' ';
				last_space = i;
				cur_len++;
				if (cur_len > maxLength)
				{
					// cur += ' ';
					lines.push_back(getLineWithOffset(cur, offset.x, maxSize.x));
					realLens.push_back(ctmin(cur_len, maxSize.x - offset.x));
					cur = "";
					cur_len = 0;
					// last_space = -1;
				}
				continue;
			}
			if ((cur_len + after_space_len) >= maxLength)
			{
				if (last_space > 0)
				{
					lines.push_back(getLineWithOffset(cur, offset.x, maxSize.x));
					realLens.push_back(ctmin(cur_len, maxSize.x - offset.x));
					cur = affter_space;
					last_space = -1;
					cur_len = after_space_len;
					affter_space = "";
					after_space_len = 0;
				}
				else
				{
					lines.push_back(getLineWithOffset(cur, offset.x, maxSize.x));
					realLens.push_back(ctmin(cur_len, maxSize.x - offset.x));
					cur = "";
					affter_space = "";
					last_space = -1;
					cur_len = 0;
					after_space_len = 0;
				}
			}
			if (isUnicodeStart(input[i]) && isUnicodeCont(input[i + 1]))
			{
				unicode_started = true;
				if (last_space == -1)
				{
					cur += input[i];
					// if (!ansi_started)
					//	cur_len++;
				}
				else
				{
					affter_space += input[i];
					// if (!ansi_started)
					//	after_space_len++;
				}
			}
			else if (unicode_started)
			{
				if (last_space == -1)
				{
					cur += input[i];
				}
				else
				{
					affter_space += input[i];
				}
				if (!isUnicodeCont(input[i + 1]))
				{
					unicode_started = false;
					if (last_space == -1)
					{
						if (!ansi_started)
							cur_len++;
					}
					else
					{
						if (!ansi_started)
							after_space_len++;
					}
				}
			}
			else
			{
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
		bool t = false;
		if (input.size() != 0)
		{
			if (input[input.size() - 1] == ' ')
				t = true;
		}
		if (affter_space != "" || t)
		{
			lines.push_back(getLineWithOffset(cur + affter_space, offset.x, maxSize.x));

			realLens.push_back(ctmin(cur_len + after_space_len, maxSize.x - offset.x));
		}
		else
		{

			lines.push_back(getLineWithOffset(cur, offset.x, maxSize.x));

			realLens.push_back(ctmin(cur_len, maxSize.x - offset.x));
		}

		rawText *rt = new rawText(vec2(maxLength, (int)lines.size()));
		for (int i = 0; i < ctmin(maxSize.y, (int)lines.size()); i++)
		{
			if (withCols)
				rt->txt[i] += a.getAttributes();
			rt->txt[i] += lines[i + offset.y];
			if (withCols)
				rt->txt[i] += c.getAttributes();
		}
		return rt;
	}

	rawText *autoWrap(rawText *rt, int maxLength, vec2 offset, vec2 maxSize, bool withCols, ConColor col, ConColor backCol)
	{
		std::vector<rawText *> rts;
		int lines = 0;
		std::vector<int> realLens;
		for (int i = 0; i < rt->size.y; i++)
		{
			rawText *rtt = autoWrap(rt->txt[i], maxLength, offset, maxSize, realLens, withCols, col, backCol);
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