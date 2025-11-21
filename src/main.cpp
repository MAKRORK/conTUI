#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <iostream>
#include "windows.h"
#include "ConColor.h"
#include "Base.h"
#include "panels/CanvasPanel.h"
#include "panels/RectPanel.h"
#include "ConsoleBase.h"
#include "KeyTUI.h"
#include "boxes/VerticalBox.h"
#include "boxes/HorizontalBox.h"
#include <string>

#include <vips/vips8>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	if (VIPS_INIT("conTUI"))
		vips_error_exit(NULL);

	ctui::attribute a = ctui::attribute(ctui::ConColor::getBackColor(ctui::ConColor::purple));
	ctui::attribute a1 = ctui::attribute(0);
	system("cls");
	std::cout << ctui::ConsoleBase::getConsoleBase()->getConsoleSize().x << ", " << ctui::ConsoleBase::getConsoleBase()->getConsoleSize().y << '\n';
	ctui::CanvasPanel cp = ctui::CanvasPanel();

	ctui::VerticalBox vb = ctui::VerticalBox(ctui::vec2(2), ctui::vec2(20, 20));
	vb.setAutoSize(true);
	ctui::HorizontalBox hb = ctui::HorizontalBox(ctui::vec2(2), ctui::vec2(40, 20));
	hb.setAutoSize(true);
	ctui::ConColor cs[6] = {ctui::ConColor::red,
							ctui::ConColor::green,
							ctui::ConColor::blue,
							ctui::ConColor::yellow,
							ctui::ConColor::purple,
							ctui::ConColor::moonstone};
	for (int i = 0; i < 4; i++)
	{
		ctui::RectPanel *rp = new ctui::RectPanel(ctui::vec2(0), ctui::vec2(15, 5 + (i * 2)));
		rp->setBorder(true, cs[i], ctui::ConColor::black, 0x2502, 0x2500);
		rp->setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);
		hb.addChild(rp);
	}
	// ctui::RectPanel rp = ctui::RectPanel(ctui::vec2(0), ctui::vec2(30, 10));
	// rp.setBorder(true, ctui::ConColor::green, ctui::ConColor::black, 0x2502, 0x2500);
	// rp.setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);

	// rp.setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::FULL);
	// rp.setPadding(2, 1, 2, 1);
	// ctui::RectPanel rp1 = ctui::RectPanel(ctui::vec2(0), ctui::vec2(20, 20));
	// rp1.setBorder(true, ctui::ConColor::purple, ctui::ConColor::black, 0x2502, 0x2500);
	// rp1.setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);

	// rp1.setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::LEFT, ctui::AlignVertical::TOP);
	// rp1.setPadding(6, 3, 0, 0);
	// cp.addChild(&rp);
	// rp.addChild(&rp1);
	cp.addChild(&hb);
	cp.drawAll();
	while (true)
	{
		cp.getEventSystem()->update();
		if (cp.getEventSystem()->isKeyJustPressed(ctui::CTKey::CTK_ESC))
		{
			break;
		}
		Sleep(20);
	}

	system("cls");
	std::string s = "Hello world!🌍😃🚀✨";
	std::cout << s << '\n';
	vips_shutdown();
	return 0;
}