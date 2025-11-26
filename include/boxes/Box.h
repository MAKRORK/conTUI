#pragma once
#include "panels/Panel.h"
#include "Log.h"

namespace ctui
{
	class Box : public Panel
	{
	private:
		bool autoSize = false;

	public:
		Box(vec2 _pos = vec2(0), vec2 _size = vec2(0)) : Panel(_pos, _size)
		{
			setDrawable(false);
		}

		~Box() { Log::getLog()->logString("Box destructed"); }

		virtual vec2 getPanelLocalPos(Panel *p) { return this->getAbsolutePos(); }
		virtual vec2 getPanelLocalSize(Panel *p) { return this->getAbsoluteSize(); }

		void setAutoSize(bool _autoSize) { autoSize = _autoSize; }
		bool getAutoSize() { return autoSize; }
	};
}
