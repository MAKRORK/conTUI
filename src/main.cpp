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
#include "panels/ImagePanel.h"
#include "panels/CanvasEventSystem.h"
#include <string>
#include "Log.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	ctui::attribute a = ctui::attribute(ctui::ConColor::getBackColor(ctui::ConColor::purple));
	ctui::attribute a1 = ctui::attribute(0);
	system("cls");
	std::cout << ctui::ConsoleBase::getConsoleBase()->getConsoleSize().x << ", " << ctui::ConsoleBase::getConsoleBase()->getConsoleSize().y << '\n';
	ctui::CanvasPanel cp = ctui::CanvasPanel();

	ctui::HorizontalBox hb = ctui::HorizontalBox(ctui::vec2(1), ctui::vec2(90, 30));
	hb.setAutoSize(true);
	hb.setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::FULL);
	ctui::ConColor cs[6] = {ctui::ConColor::red,
							ctui::ConColor::green,
							ctui::ConColor::blue,
							ctui::ConColor::yellow,
							ctui::ConColor::purple,
							ctui::ConColor::moonstone};
	ctui::ImagePanel im = ctui::ImagePanel(ctui::vec2(2), ctui::vec2(20, 20));
	im.setPath("C:/Users/user/Desktop/Things/im.jpg");

	hb.addChild(&im);
	for (int i = 0; i < 2; i++)
	{
		ctui::RectPanel *rp = new ctui::RectPanel(ctui::vec2(0), ctui::vec2(15, 5 + (i * 2)));
		rp->setBorder(true, cs[i], ctui::ConColor::black, 0x2502, 0x2500);
		rp->setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);
		rp->setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::FULL);
		hb.addChild(rp);
	}

	cp.addChild(&hb);
	cp.drawAll();
	ctui::CanvasEventSystem *es = ctui::CanvasEventSystem::getEventSystem();
	while (true)
	{
		es->update();
		if (es->isKeyJustPressed(ctui::CTKey::CTK_ESC))
		{
			break;
		}
		Sleep(20);
	}

	system("cls");
	std::string s = "Hello world!🌍😃🚀✨";
	std::cout << s << '\n';
	ctui::Log::deinit();
	return 0;
}