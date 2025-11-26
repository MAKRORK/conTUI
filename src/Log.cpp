#include "Log.h"

namespace ctui
{
	Log *Log::log = nullptr;
	void Log::logString(std::string str)
	{
		file.open(logFile, std::ios_base::app);
		file << str << '\n';
		file.close();
	}
	Log *Log::getLog()
	{
		if (!log)
		{
			log = new Log();
		}
		return log;
	}
	void Log::init()
	{
		log = new Log();
		log->file.open(log->logFile, std::ios_base::out);

		log->file.close();
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