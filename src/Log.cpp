#include "Log.h"

namespace ctui
{
	Log *Log::log = nullptr;
	void Log::logString(std::string str)
	{
		file << str << '\n';
	}
	Log *Log::getLog()
	{
		if (!log)
		{
			init();
		}
		return log;
	}
	void Log::init()
	{
		log = new Log();
		log->file.open(log->logFile, std::ios_base::out);
		log->file.write("", 0);
		log->file.close();
		log->file.open(log->logFile, std::ios_base::app);
	}
	void Log::deinit()
	{
		if (log)
		{
			log->file.close();
			delete log;
			log = nullptr;
		}
	}
}