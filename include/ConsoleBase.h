#pragma once
#include "MathTUI.h"
#include "windows.h"
#include "Base.h"
#include "Error.h"

namespace ctui
{
	class ConsoleBase
	{
	private:
		ConsoleBase();
		HANDLE hConsole;
		static ConsoleBase *console;

	public:
		static ConsoleBase *getConsoleBase();
		vec2 getConsoleSize();
		static int utf8Encode(char32_t c, unsigned char out[5]);
		static Err outChar(const symbol &sym, int x, int y);
		static Err outRawText(rawText *rt, int x, int y);
		static Err addCharToString(std::string &s, char32_t &c, int count = 1);
		static void consoleClear();
		bool isConsoleFocused();
	};
}