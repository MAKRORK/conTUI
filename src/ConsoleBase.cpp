#include "ConsoleBase.h"
#include <iostream>
#include <string>

namespace ctui
{
	ConsoleBase *ConsoleBase::console = nullptr;
	ConsoleBase::ConsoleBase()
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	ConsoleBase *ConsoleBase::getConsoleBase()
	{
		if (!console)
		{
			console = new ConsoleBase();
		}
		return console;
	}

	void ConsoleBase::init()
	{
		console = new ConsoleBase();
		console->hIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(console->hIn, &mode);
		mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
		SetConsoleMode(console->hIn, mode);
	}
	vec2 ConsoleBase::getConsoleSize()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(hConsole, &info);
		int w = info.srWindow.Right - info.srWindow.Left + 1;
		int h = info.srWindow.Bottom - info.srWindow.Top + 1;
		return vec2(w, h);
	}

	int ConsoleBase::utf8Encode(char32_t c, unsigned char out[5])
	{
		if (c <= 0x7F)
		{
			out[0] = (unsigned char)c;
			out[1] = 0;
			return 1;
		}
		else if (c <= 0x7FF)
		{
			out[0] = 0xC0 | (c >> 6);
			out[1] = 0x80 | (c & 0x3F);
			out[2] = 0;
			return 2;
		}
		else if (c <= 0xFFFF)
		{
			out[0] = 0xE0 | (c >> 12);
			out[1] = 0x80 | ((c >> 6) & 0x3F);
			out[2] = 0x80 | (c & 0x3F);
			out[3] = 0;
			return 3;
		}
		else if (c <= 0x10FFFF)
		{
			out[0] = 0xF0 | (c >> 18);
			out[1] = 0x80 | ((c >> 12) & 0x3F);
			out[2] = 0x80 | ((c >> 6) & 0x3F);
			out[3] = 0x80 | (c & 0x3F);
			out[4] = 0;
			return 4;
		}
		return -1;
	}

	void ConsoleBase::consoleEventsBufferClear()
	{
		GetNumberOfConsoleInputEvents(hIn, &events);
		// std::string s = "";
		if (events > 0)
		{
			ReadConsoleInput(hIn, irInBuf, 128, &events);
		}
	}

	std::string ConsoleBase::getEnterText()
	{
		GetNumberOfConsoleInputEvents(hIn, &events);
		std::string s = "";
		if (events > 0)
		{
			ReadConsoleInput(hIn, irInBuf, 128, &events);

			for (DWORD i = 0; i < events; i++)
			{
				if (irInBuf[i].EventType == KEY_EVENT)
				{
					KEY_EVENT_RECORD &kev = irInBuf[i].Event.KeyEvent;

					if (kev.bKeyDown)
					{
						wchar_t ch = kev.uChar.UnicodeChar;
						if (ch != 0)
						{
							s += (char)ch;
												}
					}
				}
			}
		}
		return s;
	}

	Err ConsoleBase::setCursorToPoint(vec2 point)
	{
		if (!point.inRect(vec2(0), getConsoleBase()->getConsoleSize()))
			return Err::CursorOutOfRenge;
		printf("\033[%u;%uH", point.y + 1, point.x + 1);
		return Err::Ok;
	}

	Err ConsoleBase::outChar(const symbol &sym, int x, int y)
	{
		unsigned char utf8[5];
		int n = utf8Encode(sym.chr, utf8);
		if (n < 1)
		{
			return Err::ConvertCharToUtf8Error;
		}

		for (int i = 0; i < n; i++)
		{

			if (utf8[i] == 0)
				break;
		}
		Err res = setCursorToPoint(vec2(x, y));
		if (res != Err::Ok)
			return res;
		attribute a = sym.attr;

		printf("%s", a.getAttributes().c_str());
		printf("%s\033[0m", (char *)utf8);
		return Err::Ok;
	}
	Err ConsoleBase::outRawText(rawText *rt, int x, int y)
	{
		for (int i = 0; i < rt->size.y; i++)
		{
			Err res = setCursorToPoint(vec2(x + rt->offsets[i], y + i));
			if (res != Err::Ok)
				return res;
			// printf("\033[%u;%uH", y + i + 1, x + 1 + rt->offsets[i]);
			printf("%s\033[0m", rt->txt[i].c_str());
		}
		return Err::Ok;
	}
	Err ConsoleBase::addCharToString(std::string &s, char32_t &c, int count)
	{
		unsigned char utf8[5];
		int it = utf8Encode(c, utf8);
		if (it < 1)
		{
			return Err::ConvertCharToUtf8Error;
		}
		for (int j = 0; j < count; j++)
		{
			for (int i = 0; i < it; i++)
			{
				s += utf8[i];
			}
		}
		return Err::Ok;
	}

	bool ConsoleBase::isKeyPressed(int key)
	{
		return (GetAsyncKeyState(key) & 0x8000);
	}
	bool ConsoleBase::isKeyJustPressed(int key)
	{
		return (GetAsyncKeyState(key) & 0x1);
	}

	bool ConsoleBase::isConsoleFocused()
	{
		HWND console = GetConsoleWindow();
		HWND foreground = GetForegroundWindow(); // TO DO
		return true;
	}
	void ConsoleBase::consoleClear()
	{
		system("cls");
	}
}
