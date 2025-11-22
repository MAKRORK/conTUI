#include "ImageTUI.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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

	char ImageTUI::getCharFromBrigth(int br)
	{
		int n = (int)(((double)br / 255.0) * (int)gradient.size());
		return gradient[n];
	}

	getImResult ImageTUI::getTextImage(std::string path, vec2 size, bool monochrome, ConColor monochromeColor)
	{
		int w, h, b;
		unsigned char *input = stbi_load(path.c_str(), &w, &h, &b, 0);
		// std::cout << size.x << ", " << size.y << '\n';
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

		txtImgPix **it = new txtImgPix *[nsize.y];
		// std::cout << "Ok 0.0.0\n";
		for (int y = 0; y < nsize.y; ++y)
		{
			// std::cout << "Ok y = " << y << '\n';
			it[y] = new txtImgPix[nsize.x];
			for (int x = 0; x < nsize.x; ++x)
			{
				// std::cout << "Ok x = " << x << '\n';
				size_t base = (size_t)(y * nsize.x + x) * b;

				int a = 1;
				if (b == 4 && data[base + 3] <= 100)
				{
					a = 0;
				}

				it[y][x].chr = getCharFromBrigth(((data[base] + data[base + 1] + data[base + 2]) / 3) * a);
				if (monochrome)
				{
					it[y][x].col = monochromeColor;
				}
				else
				{
					it[y][x].col = ConColor::getColorFromRGB(data[base], data[base + 1], data[base + 2]);
				}
			}
		}
		return getImResult(Err::Ok, it, nsize);
		// stbi_write_png("E:/MyProjects/CPPProjects/tmpassets/resized.png", nsize.x, nsize.y, b, data, nsize.x * b);

		return getImResult(Err::cantLoadImage);
	}
	//{
	//	vips::VImage img = vips::VImage::new_from_file(path.c_str());
	//	vec2 nsize = vec2(0);
	//	if (img.width() > img.height())
	//	{
	//		nsize.x = size.x;
	//		nsize.y = (int)(((double)nsize.x / img.width()) * (double)img.height() / 2.0);
	//		if (nsize.y > size.y)
	//		{
	//			nsize.y = size.y;
	//			nsize.x = (int)(((double)nsize.y / img.height()) * (double)img.width() * 2.0);
	//		}
	//	}
	//	else
	//	{
	//		nsize.y = size.y;
	//		nsize.x = (int)(((double)nsize.y / img.height()) * (double)img.width() * 2.0);
	//		if (nsize.x > size.x)
	//		{
	//			nsize.x = size.x;
	//			nsize.y = (int)(((double)nsize.x / img.width()) * (double)img.height() / 2.0);
	//		}
	//	}
	//	double scale_x = (double)nsize.x / img.width();
	//	double scale_y = (double)nsize.y / img.height();
	//	vips::VImage resized = img.resize(scale_x, vips::VImage::option()->set("vscale", scale_y));
	//	vips::VImage u = resized.cast(VIPS_FORMAT_UCHAR);

	//	int w = u.width();
	//	int h = u.height();
	//	int b = u.bands();

	//	size_t buf_size = 0;

	//	void *raw = u.write_to_memory(&buf_size);
	//	if (!raw || buf_size == 0)
	//	{
	//		return getImResult(Err::cantLoadImage);
	//	}

	//	std::vector<unsigned char> buf((unsigned char *)raw, (unsigned char *)raw + buf_size);

	//	g_free(raw);
	//	txtImgPix **it = new txtImgPix *[h];

	//	for (int y = 0; y < h; ++y)
	//	{
	//		it[y] = new txtImgPix[w];
	//		for (int x = 0; x < w; ++x)
	//		{
	//			size_t base = (size_t)(y * w + x) * b;
	//			if (b < 3)
	//			{
	//				it[y][x].chr = getCharFromBrigth(buf[base]);
	//				it[y][x].col = monochromeColor;
	//			}
	//			else
	//			{
	//				it[y][x].chr = getCharFromBrigth((buf[base] + buf[base + 1] + buf[base + 2]) / 3);
	//				if (monochrome)
	//				{
	//					it[y][x].col = monochromeColor;
	//				}
	//			}
	//		}
	//	}
	//	return getImResult(Err::Ok, it, vec2(w, h));
	//}
}