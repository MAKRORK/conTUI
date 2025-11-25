#pragma once
#include "CanvasEvent.h"
#include <iostream>
#include <queue>
#include "KeyTUI.h"
#include "panels/Panel.h"

namespace ctui
{

	struct connectedEvent
	{
		void (Panel::*func)();
		CanvasEventType cType;
		Panel *pan;
		connectedEvent(void (Panel::*_func)(), CanvasEventType _cType, Panel *_pan) : func(_func), cType(_cType), pan(_pan) {}
	};
	class CanvasEventSystem
	{
	private:
		std::queue<CanvasEvent *> events;
		vec2 prevSize;
		void initEventSystem();
		std::vector<connectedEvent> connectedEvents;
		static CanvasEventSystem *eventSystem;
		CanvasEventSystem()
		{
			initEventSystem();
		}

	public:
		void update(bool all_keys = false);
		CanvasEvent *popEvent();
		static CanvasEventSystem *getEventSystem();
		void connectEvent(void (Panel::*_func)(), CanvasEventType _ct, Panel *_pan);
	};
}