#include "panels/CanvasEventSystem.h"
#include "panels/CanvasPanel.h"
#include "ConsoleBase.h"

namespace ctui
{
	void CanvasEventSystem::initEventSystem()
	{
		prevSize = ConsoleBase::getConsoleBase()->getConsoleSize();
	}
	void CanvasEventSystem::update(bool all_keys)
	{
		vec2 size = ConsoleBase::getConsoleBase()->getConsoleSize();
		if (size.x != prevSize.x || size.y != prevSize.y)
		{
			events.push(new CanvasResizeEvent(size));
			for (int i = 0; i < connectedEvents.size(); i++)
			{
				if (connectedEvents[i].cType == CanvasEventType::ResizedEvent)
				{
					(connectedEvents[i].pan->*connectedEvents[i].func)();
				}
			}
			prevSize = size;
		}
		if (all_keys)
		{
			for (int key = 0; key < 256; ++key)
			{
				if (GetAsyncKeyState(key) & 0x1)
				{
					events.push(new CanvasKeyEvent(key));
				}
			}
		}
	}
	CanvasEvent *CanvasEventSystem::popEvent()
	{
		if (events.empty())
			return new CanvasEvent();
		return events.front();
	}
	bool CanvasEventSystem::isKeyPressed(int key)
	{
		return (GetAsyncKeyState(key) & 0x8000) && ConsoleBase::getConsoleBase()->isConsoleFocused();
	}
	bool CanvasEventSystem::isKeyJustPressed(int key)
	{
		return (GetAsyncKeyState(key) & 0x1) && ConsoleBase::getConsoleBase()->isConsoleFocused();
	}

	void CanvasEventSystem::connectEvent(void (Panel::*_func)(), CanvasEventType _ct, Panel *_pan)
	{
		connectedEvents.push_back(connectedEvent(_func, _ct, _pan));
	}
}
