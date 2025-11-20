#include "Error.h"

namespace ctui
{
	const Err Err::Ok = Err(0, "Ok");
	const Err Err::CanvasPanelCantBeChildError = Err(1, "Canvas penel must be root panel");
	const Err Err::CursorOutOfRenge = Err(2, "Cannot set cursor ou of console range");
	const Err Err::ConvertCharToUtf8Error = Err(3, "Cannot convert char to utf8 format");
	const char *Err::getMessage()
	{
		return errMessage;
	}
}
