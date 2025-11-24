#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#pragma once
#include "Panel.h"
#include "ConColor.h"
#include "ImageTUI.h"

namespace ctui
{

	class ImagePanel : public Panel
	{
	private:
		std::string imagePath;
		void loadImage();
		txtImgPix **it = nullptr;
		vec2 imSize = vec2(0);
		bool noImage = true;
		ConColor background = ConColor::black;
		bool monochrome = false;
		bool inverted = false;
		ConColor monochromeColor = ConColor::white;

	protected:
		void setParent(Panel *p) override;

	public:
		ImagePanel(vec2 _pos = vec2(0), vec2 _size = vec2(1), std::string _path = "") : Panel(_pos, _size)
		{
			debug_sym = U'I';
			if (_path != "")
			{
				imagePath = _path;
				loadImage();
			}
		}
		~ImagePanel();
		void setPath(std::string _path)
		{
			imagePath = _path;
			loadImage();
		}
		void setImagetStyle(bool _monochrome, bool _inverted = false, ConColor _monochromeColor = ConColor::white, ConColor _background = ConColor::black);

		void setSize(vec2 _size) override;
		void setStyle(PositionType _posType) override;
		void setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV) override;
		void setPadding(int l, int t, int r, int b) override;
		void setPadding(int p) override;

		rawText *getRawText(vec2 offset, vec2 maxSize) override;

		void onResize() override;

		vec2 getSize() override;
		vec2 getAbsoluteSize() override;
		bool getMonochrome() { return monochrome; }
		bool getInverted() { return inverted; }
		ConColor getMonochromeColor() { return monochromeColor; }
		ConColor getBackgroundColor() { return background; }
	};
}