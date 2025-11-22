#pragma once
#include <string>
#include <fstream>

namespace ctui
{
	class Log
	{
	private:
		std::string logFile = "ctui_log.log";
		static Log *log;
		std::ofstream file;
		Log() {}

	public:
		void logString(std::string str);
		static Log *getLog();
		static void init();
		static void deinit();
	};
}