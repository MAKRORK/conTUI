#pragma once
#include "Base.h"
#include "Error.h"
#include "ConColor.h"

namespace ctui
{
	struct txtImgPix
	{
		char chr;
		ConColor col;
	};

	struct getImResult
	{
		Err err = Err::Ok;
		txtImgPix **it = nullptr;
		vec2 size = vec2(0);
		getImResult(Err _err, txtImgPix **_it = nullptr, vec2 _size = vec2(0)) : err(_err), it(_it), size(_size) {}
	};

	class ImageTUI
	{
	private:
		static ImageTUI *imageTUI;
		ImageTUI();
		~ImageTUI();
		char getCharFromBrigth(int br, bool inverted = false);
		std::string gradient = " .:-=+*#%@";

	public:
		static ImageTUI *getImt();
		static void deinit();
		getImResult getTextImage(std::string path, vec2 size, bool monochrome = false, bool inverted = false, ConColor monochromeColor = ConColor::white);
		void setGradient(std::string _gradient);
		static char32_t noLoadedSym;
	};
}