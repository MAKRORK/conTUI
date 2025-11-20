#pragma once
#include "Panel.h"
#include "Base.h"
#include "panels/CanvasEventSystem.h"
#include "ConColor.h"

namespace ctui
{
	class CanvasPanel : public Panel
	{
	private:
		ctText *buffer = nullptr;
		void initBuffer();
		Panel ***maskBuffer = nullptr;
		CanvasEventSystem *eventSystem = nullptr;
		void build(Panel *pan);
		ConColor fillColor = ConColor::black;

	protected:
		void rebuild() override;
		void redraw(Panel *p) override;

	public:
		CanvasPanel() : Panel()
		{
			this->initBuffer();
			eventSystem = new CanvasEventSystem();
			eventSystem->connectEvent(&Panel::onResize, CanvasEventType::ResizedEvent, this);
			debug_sym = U'C';
		}
		~CanvasPanel();
		void debug_outMask();
		void drawAll(Panel *p = nullptr);
		void drawRaw(Panel *p);
		void setSize(vec2 _size) override;
		rawText *getRawText(vec2 offset, vec2 maxSize) override;
		CanvasEventSystem *getEventSystem() { return eventSystem; }
		void onResize() override;

		Err addChild(Panel *p) override;
	};
}