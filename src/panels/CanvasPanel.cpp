#include "panels/CanvasPanel.h"
#include "ConsoleBase.h"
#include <iostream>
#include <cmath>
#include <algorithm>

namespace ctui
{

	void CanvasPanel::initBuffer()
	{

		if (buffer && !buffer->empty())
		{

			delete buffer;
		}

		vec2 size = getAbsoluteSize();
		if (maskBuffer)
		{

			for (int i = 0; i < size.y; i++)
			{
				delete[] maskBuffer[i];
			}
			delete[] maskBuffer;
		}
		setSize(ConsoleBase::getConsoleBase()->getConsoleSize());
		size = getAbsoluteSize();
		maskBuffer = new Panel **[size.x];
		for (int i = 0; i < size.y; i++)
		{
			maskBuffer[i] = new Panel *[size.x];
			for (int j = 0; j < size.x; j++)
			{
				maskBuffer[i][j] = this;
			}
		}
		buffer = new ctText(size);
	}
	Err CanvasPanel::drawAll(Panel *p)
	{
		if (!p)
			p = this;
		if (p->getDrawable())
		{
			Err res = drawRaw(p);
			if (drawRaw(p) != Err::Ok)
			{
				return res;
			}
		}

		std::vector<Panel *> *ch = p->getChilds();
		for (int i = 0; i < ch->size(); i++)
		{
			drawAll((*ch)[i]);
		}
		return Err::Ok;
	}

	void CanvasPanel::setSize(vec2 _size)
	{
		setSizeWithoutRebild(_size);
	}

	Err CanvasPanel::drawRaw(Panel *p)
	{
		vec2 ps = p->getAbsolutePos();
		vec2 o = vec2(0);
		vec2 cs = ConsoleBase::getConsoleBase()->getConsoleSize();
		if (ps.x < 0)
		{
			o.x = -ps.x;
		}
		if (ps.y < 0)
		{
			o.y = -ps.y;
		}
		vec2 ms = p->getAbsoluteSize();
		if (ps.x + ms.x > cs.x)
		{
			ms.x -= (ps.x + ms.x - cs.x);
		}
		if (ps.y + ms.y > cs.y)
		{
			ms.y -= (ps.y + ms.y - cs.y);
		}
		rawText *rt = p->getRawText(o, ms);
		if (!rt)
			return Err::drawNoDrawableError;
		ConsoleBase::outRawText(rt, ps.x + o.x, ps.y + o.y);
		return Err::Ok;
	}
	rawText *CanvasPanel::getRawText(vec2 offset, vec2 maxSize)
	{
		vec2 s = getAbsoluteSize();
		if (r)
			delete r;
		r = new rawText(s);
		attribute a = attribute(ConColor::getBackColor(fillColor));
		a.addAttribute(ConColor::getForeColor(fillColor));
		attribute c = attribute(0);
		char32_t ch = U' ';
		for (int i = 0; i < s.y; i++)
		{
			r->txt[i] += a.getAttributes();
			ConsoleBase::addCharToString(r->txt[i], ch, s.x);
			r->txt[i] += c.getAttributes();
			// std::cout << rt->txt[i] << '\n';
		}
		return r;
	}
	void CanvasPanel::onResize()
	{
		initBuffer();
		build(this);
		ConsoleBase::consoleClear();
		drawAll();
	}

	Err CanvasPanel::addChild(Panel *p)
	{
		Err res = Panel::addChild(p);
		if (res != Err::Ok)
		{
			return res;
		}
		build(this);
		return Err::Ok;
	}
	CanvasPanel::~CanvasPanel()
	{
		vec2 size = ConsoleBase::getConsoleBase()->getConsoleSize();
		if (maskBuffer)
		{
			for (int i = 0; i < size.y; i++)
			{
				delete[] maskBuffer[i];
			}
			delete[] maskBuffer;
		}
		if (buffer)
		{
			delete buffer;
		}
	}
	void CanvasPanel::debug_outMask()
	{
		vec2 size = getAbsoluteSize();

		std::cout << size.x << " " << size.y << "\n";
		for (int i = 0; i < size.y; i++)
		{
			for (int j = 0; j < size.x; j++)
			{
				std::cout << static_cast<char>(maskBuffer[i][j]->debug_sym);
			}
			std::cout << '\n';
		}
	}
	void CanvasPanel::rebuild()
	{
		build(this);
	}
	void CanvasPanel::build(Panel *pan)
	{
		std::vector<Panel *> *ch = pan->getChilds();
		vec2 ptmp = pan->getAbsolutePos();
		vec2 stmp = pan->getAbsoluteSize();
		vec2 cs = getAbsoluteSize();
		pan->setCovered(false);

		// std::cout << "      " << ptmp.x << ", " << ptmp.y << '\n';
		// std::cout << "      " << stmp.x << ", " << stmp.y << '\n';
		vec2 fn = vec2(ctmin(cs.x, (stmp.x + ptmp.x)), ctmin(cs.y, stmp.y + ptmp.y));
		for (int i = ctmax(ptmp.y, 0); i < fn.y; i++)
		{
			for (int j = ctmax(ptmp.x, 0); j < fn.x; j++)
			{
				maskBuffer[i][j]->setCovered(true);
				maskBuffer[i][j] = pan;
			}
		}
		for (int i = 0; i < ch->size(); i++)
		{
			(*ch)[i]->onResize();
			build((*ch)[i]);
		}
	}

	void CanvasPanel::redraw(Panel *p)
	{
		if (p->getCovered())
		{
			drawAll(p);
		}
		else
		{
			drawRaw(p);
		}
	}
}
