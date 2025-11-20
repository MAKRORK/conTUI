#include <iostream>
#include "windows.h"
#include "ConColor.h"
#include "Base.h"
#include "panels/CanvasPanel.h"
#include "panels/RectPanel.h"
#include "ConsoleBase.h"
#include "KeyTUI.h"
#include <string>

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	ctui::attribute a = ctui::attribute(ctui::ConColor::getBackColor(ctui::ConColor::purple));
	ctui::attribute a1 = ctui::attribute(0);
	system("cls");
	std::cout << ctui::ConsoleBase::getConsoleBase()->getConsoleSize().x << ", " << ctui::ConsoleBase::getConsoleBase()->getConsoleSize().y << '\n';
	ctui::CanvasPanel cp = ctui::CanvasPanel();
	ctui::RectPanel rp = ctui::RectPanel(ctui::vec2(0), ctui::vec2(30, 10));
	rp.setBorder(true, ctui::ConColor::green, ctui::ConColor::black, 0x2502, 0x2500);
	rp.setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);

	rp.setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::FULL);
	rp.setPadding(2, 1, 2, 1);
	ctui::RectPanel rp1 = ctui::RectPanel(ctui::vec2(0), ctui::vec2(20, 20));
	rp1.setBorder(true, ctui::ConColor::purple, ctui::ConColor::black, 0x2502, 0x2500);
	rp1.setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);

	rp1.setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::LEFT, ctui::AlignVertical::TOP);
	rp1.setPadding(6, 3, 0, 0);
	cp.addChild(&rp);
	rp.addChild(&rp1);
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
	return 0;
}