#include "ImageTUI.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

namespace ctui
{
	ImageTUI *ImageTUI::imageTUI = nullptr;
	char32_t ImageTUI::noLoadedSym = 0x2327;
	ImageTUI::ImageTUI()
	{
	}
	ImageTUI::~ImageTUI()
	{
	}
	ImageTUI *ImageTUI::getImt()
	{
		if (!imageTUI)
			imageTUI = new ImageTUI();
		return imageTUI;
	}
	void ImageTUI::deinit()
	{
		if (imageTUI)
		{
			delete imageTUI;
			imageTUI = nullptr;
		}
	}

	char ImageTUI::getCharFromBrigth(int br, bool inverted)
	{
		int n = (int)(((double)br / 255.0) * ((int)gradient.size() - 1));
		if (inverted)
		{
			n = ((int)gradient.size() - 1) - n;
		}
		return gradient[n];
	}

	void ImageTUI::setGradient(std::string _gradient)
	{
		gradient = _gradient;
	}

	getImResult ImageTUI::getTextImage(std::string path, vec2 size, bool monochrome, bool inverted, ConColor monochromeColor)
	{
		int w, h, b;
		unsigned char *input = stbi_load(path.c_str(), &w, &h, &b, 0);
		if (!input)
		{
			return getImResult(Err::cantLoadImage);
		}

		vec2 nsize = vec2(0);
		if (w > h)
		{
			nsize.x = size.x;
			nsize.y = (int)(((double)nsize.x / w) * (double)h / 2.0);
			if (nsize.y > size.y)
			{
				nsize.y = size.y;
				nsize.x = (int)(((double)nsize.y / h) * (double)w * 2.0);
			}
		}
		else
		{
			nsize.y = size.y;
			nsize.x = (int)(((double)nsize.y / h) * (double)w * 2.0);
			if (nsize.x > size.x)
			{
				nsize.x = size.x;
				nsize.y = (int)(((double)nsize.x / w) * (double)h / 2.0);
			}
		}
		unsigned char *data = new unsigned char[nsize.x * nsize.y * b];
		stbir_pixel_layout layout =
			(b == 4 ? STBIR_RGBA : STBIR_RGB);

		stbir_resize_uint8_srgb(
			input, w, h, 0,
			data, nsize.x, nsize.y, 0,
			layout);
		// stbi_write_png("output.png", nsize.x, nsize.y, b, data, nsize.x * b);
		stbi_image_free(input);
		if (!data)
		{
			return getImResult(Err::cantLoadImage);
		}

		txtImgPix **it = new txtImgPix *[nsize.y];
		for (int y = 0; y < nsize.y; ++y)
		{

			it[y] = new txtImgPix[nsize.x];
			for (int x = 0; x < nsize.x; ++x)
			{

				size_t base = (size_t)(y * nsize.x + x) * b;

				int a = 1;

				if (b == 4 && data[base + 3] <= 100)
				{
					a = 0;
				}

				it[y][x].chr = getCharFromBrigth(((data[base] + data[base + 1] + data[base + 2]) / 3) * a, inverted);
				if (monochrome)
				{
					it[y][x].col = monochromeColor;
				}
				else
				{
					if (inverted)
						it[y][x].col = ConColor::getColorFromRGB(255 - data[base], 255 - data[base + 1], 255 - data[base + 2]);
					else
						it[y][x].col = ConColor::getColorFromRGB(data[base], data[base + 1], data[base + 2]);
				}
			}
		}
		delete[] data;
		return getImResult(Err::Ok, it, nsize);
	}

}