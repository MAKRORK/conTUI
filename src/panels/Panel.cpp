#include "panels/Panel.h"
#include "panels/CanvasPanel.h"
#include "ConsoleBase.h"
#include "boxes/Box.h"
#include "Log.h"

namespace ctui
{

	Panel::~Panel()
	{
		if (r)
			delete r;
	}
	Err Panel::addChild(Panel *p)
	{
		if (dynamic_cast<CanvasPanel *>(p))
		{
			return Err::CanvasPanelCantBeChildError;
		}
		p->setParent(this);
		this->childs.push_back(p);
		return Err::Ok;
	}
	void Panel::removeChild(Panel *p)
	{
		auto it = std::find(this->childs.begin(), this->childs.end(), p);
		if (it != this->childs.end())
			this->childs.erase(it);
	}
	void Panel::setParent(Panel *p)
	{
		this->parent = p;
	}
	vec2 Panel::getAbsolutePos()
	{
		if (parent)
		{

			vec2 p = parent->getAbsolutePos();

			Box *b = dynamic_cast<Box *>(parent);
			if (b)
			{
				return p + b->getPanelLocalPos(this) + vec2(padding[0], padding[1]);
			}
			if (stl.posType == PositionType::Relative)
			{
				vec2 ptmp = p;
				vec2 s = getAbsoluteSize();
				vec2 sp = parent->getAbsoluteSize();
				if (stl.alignH == AlignHorizontal::RIGHT)
				{
					p.x = ptmp.x + sp.x - s.x - padding[2];
				}
				else if (stl.alignH == AlignHorizontal::CENTER)
				{
					p.x = ptmp.x + sp.x / 2 - s.x / 2;
				}
				else if (stl.alignH == AlignHorizontal::FULL)
				{
					p.x = ptmp.x + padding[0];
				}
				else
				{
					p.x = ptmp.x + padding[0];
				}

				if (stl.alignV == AlignVertical::BOTTOM)
				{
					p.y = ptmp.y + sp.y - s.y - padding[3];
				}
				else if (stl.alignV == AlignVertical::CENTER)
				{
					p.y = ptmp.y + sp.y / 2 - s.y / 2;
				}
				else if (stl.alignV == AlignVertical::FULL)
				{
					p.y = ptmp.y + padding[1];
				}
				else
				{
					p.y = ptmp.y + padding[1];
				}
				return p;
			}

			return p + pos;
		}

		return pos;
	}
	vec2 Panel::getAbsoluteSize()
	{
		vec2 s = getSize();

		if (parent)
		{
			Box *b = dynamic_cast<Box *>(parent);

			if (b)
			{

				return b->getPanelLocalSize(this) - vec2(padding[0] + padding[2], padding[1] + padding[3]);
			}

			if (stl.posType == PositionType::Relative)
			{
				if (stl.alignH == AlignHorizontal::FULL)
				{
					s.x = parent->getAbsoluteSize().x;
					s.x -= (padding[0] + padding[2]);
				}

				if (stl.alignV == AlignVertical::FULL)
				{
					s.y = parent->getAbsoluteSize().y;
					s.y -= (padding[1] + padding[3]);
				}
			}
		}
		if (s.x < 0 || s.y < 0)
		{
			return vec2(0);
		}

		return s;
	}
	void Panel::setStyle(PositionType _posType)
	{
		stl.posType = _posType;
		rebuild();
	}
	void Panel::setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV)
	{
		stl.posType = _posType;
		stl.alignH = _alignH;
		stl.alignV = _alignV;
		rebuild();
	}

	void Panel::setPadding(int l, int t, int r, int b)
	{
		padding[0] = l;
		padding[1] = t;
		padding[2] = r;
		padding[3] = b;
		rebuild();
	}
	void Panel::setPadding(int p)
	{
		setPadding(p, p, p, p);
	}

	void Panel::redraw(Panel *p)
	{
		if (parent)
		{
			if (!p)
				p = this;
			parent->redraw(p);
		}
	}
	void Panel::rebuild()
	{
		if (parent)
			parent->rebuild();
	}
}
