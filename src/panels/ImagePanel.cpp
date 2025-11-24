#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "panels/ImagePanel.h"
#include "ConsoleBase.h"
#include "panels/CanvasEventSystem.h"
#include "boxes/Box.h"

namespace ctui
{

	void ImagePanel::loadImage()
	{
		if (it)
		{
			for (int i = 0; i < imSize.y; i++)
			{
				delete[] it[i];
			}
			delete[] it;
		}

		vec2 p = Panel::getAbsoluteSize();

		getImResult res = ImageTUI::getImt()->getTextImage(imagePath, Panel::getAbsoluteSize(), monochrome, inverted, monochromeColor);

		if (res.err != Err::Ok)
		{
			noImage = true;
			return;
		}

		noImage = false;
		this->it = res.it;
		this->imSize = res.size;
	}
	ImagePanel::~ImagePanel()
	{
		if (it)
		{
			for (int i = 0; i < imSize.y; i++)
			{
				delete[] it[i];
			}
			delete[] it;
		}
	}
	void ImagePanel::setImagetStyle(bool _monochrome, bool _inverted, ConColor _monochromeColor, ConColor _background)
	{
		monochrome = _monochrome;
		inverted = _inverted;
		monochromeColor = _monochromeColor;
		background = _background;
		loadImage();
	}
	void ImagePanel::onResize()
	{
		Box *b = dynamic_cast<Box *>(getParent());
		if (getStyle().posType == PositionType::Relative || b)
			loadImage();
	}

	void ImagePanel::setParent(Panel *p)
	{
		Panel::setParent(p);
		Box *b = dynamic_cast<Box *>(p);
		if (getStyle().posType == PositionType::Relative || b)
		{

			loadImage();
		}
	}

	void ImagePanel::setSize(vec2 _size)
	{
		Panel::setSize(_size);
		loadImage();
	}
	void ImagePanel::setStyle(PositionType _posType)
	{
		Panel::setStyle(_posType);
		loadImage();
	}
	void ImagePanel::setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV)
	{
		Panel::setStyle(_posType, _alignH, _alignV);
		loadImage();
	}
	void ImagePanel::setPadding(int l, int t, int r, int b)
	{
		Panel::setPadding(l, t, r, b);
		loadImage();
	}
	void ImagePanel::setPadding(int p)
	{
		Panel::setPadding(p);
		loadImage();
	}
	rawText *ImagePanel::getRawText(vec2 offset, vec2 maxSize)
	{
		if (r)
		{
			delete r;
		}
		if (noImage)
		{
			r = new rawText(vec2(getAbsoluteSize().x, 1));
			if (imagePath == "")
			{
				r->txt[0] += "No image";
			}
			else
			{
				ConsoleBase::addCharToString(r->txt[0], ImageTUI::noLoadedSym);
				r->txt[0] += "Load image error";
			}
			return r;
		}
		r = new rawText(imSize);
		ConColor lastColor = ConColor::none;
		for (int y = 0; y < maxSize.y; y++)
		{
			for (int x = 0; x < maxSize.x; x++)
			{
				if (it[y + offset.y][x + offset.x].col != lastColor)
				{
					if (x != 0)
					{
						r->txt[y] += attribute::clear.getAttributes();
					}
					lastColor = it[y + offset.y][x + offset.x].col;
					attribute a = attribute(ConColor::getForeColor(lastColor));
					a.addAttribute(ConColor::getBackColor(background));
					r->txt[y] += a.getAttributes();
				}
				else
				{
					if (x == 0)
					{
						attribute a = attribute(ConColor::getForeColor(lastColor));
						a.addAttribute(ConColor::getBackColor(background));
						r->txt[y] += a.getAttributes();
					}
				}
				r->txt[y] += it[y + offset.y][x + offset.x].chr;
			}
			r->txt[y] += attribute::clear.getAttributes();
		}
		return this->r;
	}
	vec2 ImagePanel::getSize()
	{
		vec2 s = Panel::getSize();
		// if (noImage)
		//{
		//	s.y = 1;
		//	return s;
		// }
		return s;
	}
	vec2 ImagePanel::getAbsoluteSize()
	{
		if (noImage)
		{
			return Panel::getAbsoluteSize();
		}
		return imSize;
	}
}