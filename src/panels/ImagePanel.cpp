#include "panels/ImagePanel.h"

namespace ctui
{

	void ImagePanel::loadImage()
	{
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
		return this->r;
	}
}