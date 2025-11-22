#pragma once

namespace ctui
{
	class Err
	{
	private:
		int id = 0;
		const char *errMessage;

	public:
		Err(int _id, const char *_errMessage) : id(_id), errMessage(_errMessage) {}
		const char *getMessage();
		const static Err Ok;
		const static Err CanvasPanelCantBeChildError;
		const static Err CursorOutOfRenge;
		const static Err ConvertCharToUtf8Error;
		const static Err drawNoDrawableError;
		const static Err cantLoadImage;

		bool operator==(const Err &other) const
		{
			return id == other.id;
		}

		bool operator!=(const Err &other) const
		{
			return !(*this == other);
		}
	};
}