#pragma once
#include "MathTUI.h"
#include <iostream>
#include <vector>
#include "Base.h"
#include "Error.h"

namespace ctui
{
	class Panel
	{
	private:
		vec2 pos;
		vec2 size;
		std::vector<Panel *> childs;
		Panel *parent = nullptr;
		style stl = style();
		bool covered = false;

		int padding[4] = {0, 0, 0, 0};
		bool drawable = true;

	protected:
		virtual void rebuild();
		virtual void setParent(Panel *p);
		rawText *r = nullptr;
		virtual void redraw(Panel *p = nullptr);
		void setSizeWithoutRebild(vec2 _size)
		{
			size = _size;
		}
		void setDrawable(bool _d) { drawable = _d; }

	public:
		Panel(vec2 _pos = vec2(0), vec2 _size = vec2(0)) : pos(_pos), size(_size) {}
		virtual ~Panel();
		vec2 getPos() { return pos; }
		virtual vec2 getSize() { return size; }
		vec2 getAbsolutePos();
		virtual vec2 getAbsoluteSize();
		style getStyle() { return stl; }
		void setCovered(bool _c) { covered = _c; }
		bool getCovered() { return covered; }
		bool getDrawable() { return drawable; }
		void setPos(vec2 _pos)
		{
			pos = _pos;
			rebuild();
		}
		virtual void setSize(vec2 _size)
		{
			size = _size;
			rebuild();
		}
		virtual void setStyle(PositionType _posType);
		virtual void setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV);
		virtual void setPadding(int l, int t, int r, int b);
		virtual void setPadding(int p);

		char debug_sym = ' ';

		virtual Err addChild(Panel *p);
		virtual void removeChild(Panel *p);
		Panel *getParent() { return parent; }
		std::vector<Panel *> *getChilds() { return &childs; }
		virtual ctText getText() { return ctText(); }
		virtual rawText *getRawText(vec2 offset, vec2 maxSize) { return r; }
		virtual void onResize() {}
	};
};