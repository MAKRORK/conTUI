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
		HANDLE hIn;
		static ConsoleBase *console;
		INPUT_RECORD irInBuf[128];
		DWORD events;

	public:
		static ConsoleBase *getConsoleBase();
		vec2 getConsoleSize();
		static int utf8Encode(char32_t c, unsigned char out[5]);
		static Err outChar(const symbol &sym, int x, int y);
		static Err outRawText(rawText *rt, int x, int y);
		static Err setCursorToPoint(vec2 point);
		static Err addCharToString(std::string &s, char32_t &c, int count = 1);
		static void consoleClear();
		static void init();

		std::string getEnterText();
		void consoleEventsBufferClear();

		static bool isKeyPressed(int key);
		static bool isKeyJustPressed(int key);

		bool isConsoleFocused();
	};
}