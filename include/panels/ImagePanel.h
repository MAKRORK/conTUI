#pragma once
#include "Panel.h"
#include "ConColor.h"

namespace ctui
{
	struct txtImgPix
	{
		char chr;
		ConColor col;
	};

	class ImagePanel : public Panel
	{
	private:
		std::string imagePath;
		void loadImage();

	public:
		ImagePanel(vec2 _pos = vec2(0), vec2 _size = vec2(1), std::string _path = "") : Panel(_pos, _size)
		{
			if (_path != "")
			{
				imagePath = _path;
				loadImage();
			}
		}
		void setPath(std::string _path)
		{
			imagePath = _path;
			loadImage();
		}
		void setSize(vec2 _size) override;
		void setStyle(PositionType _posType) override;
		void setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV) override;
		void setPadding(int l, int t, int r, int b) override;
		void setPadding(int p) override;

		rawText *getRawText(vec2 offset, vec2 maxSize) override;
	};
}