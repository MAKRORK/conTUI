#pragma once
#include "MathTUI.h"

namespace ctui
{
	enum class CanvasEventType
	{
		EmptyEvent,
		KeyEvent,
		ResizedEvent
	};

	class CanvasEvent
	{
	private:
		CanvasEventType type;

	public:
		CanvasEventType getType() { return type; }
		CanvasEvent(CanvasEventType _type = CanvasEventType::EmptyEvent) : type(_type) {}
	};
	class CanvasKeyEvent : public CanvasEvent
	{
	private:
		int key;

	public:
		CanvasKeyEvent(int _key) : CanvasEvent(CanvasEventType::KeyEvent) { key = _key; }
		char getKey() { return key; }
	};
	class CanvasResizeEvent : public CanvasEvent
	{
	private:
		vec2 newSize;

	public:
		CanvasResizeEvent(vec2 _newSize) : CanvasEvent(CanvasEventType::ResizedEvent) { newSize = _newSize; }
		vec2 getKey() { return newSize; }
	};

}