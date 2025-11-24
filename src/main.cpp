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
#include "panels/TextPanel.h"
#include <string>
#include "TextTUI.h"
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
	im.setImagetStyle(false, false, ctui::ConColor::white, ctui::ConColor::black);
	im.setPath("E:/MyProjects/CPPProjects/tmpassets/iii.jpg");

	std::cout << "Lol\n";
	hb.addChild(&im);

	ctui::RectPanel *rp = new ctui::RectPanel(ctui::vec2(0), ctui::vec2(15, 5));
	rp->setBorder(true, cs[0], ctui::ConColor::black, 0x2502, 0x2500);
	rp->setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);
	rp->setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::FULL);

	ctui::TextPanel *tb = new ctui::TextPanel(ctui::vec2(2, 1), ctui::vec2(20, 5));
	tb->setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::FULL);
	tb->setPadding(2, 2, 2, 2);
	tb->setText("Darkness\n blacker than \x1b[41mblack\x1b[0m and darker than dark, I beseech thee, combine with my deep crimson. The time of awakening cometh. Justice, fallen upon the infallible boundary");
	tb->setForeColor(ctui::ConColor::black);
	tb->setBackColor(ctui::ConColor::grey);
	rp->addChild(tb);

	hb.addChild(rp);
	ctui::VerticalBox vb = ctui::VerticalBox(ctui::vec2(1), ctui::vec2(90, 30));
	vb.setAutoSize(true);
	for (int i = 0; i < 3; i++)
	{
		ctui::RectPanel *rp1 = new ctui::RectPanel(ctui::vec2(0), ctui::vec2(15, 5));
		rp1->setBorder(true, cs[i + 1], ctui::ConColor::black, 0x2502, 0x2500);
		rp1->setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);
		vb.addChild(rp1);
	}
	hb.addChild(&vb);
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