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
#include "panels/OneLineText.h"
#include <string>
#include "TextTUI.h"
#include "input/RectButton.h"
#include "Log.h"
#include "input/OneLineButton.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	ctui::Log::init();

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
	tb->setText("Мрак чернее чёрной и темнее тёмной, Умоляю тебя, соединись с моим глубоким багрянцем. Время пробуждения настало. Справедливость, павшая на непогрешимую границу, явись сейчас как неосязаемые искажения! Я желаю для своего потока силы разрушительной силы: разрушительной силы, равной которой нет! Обрати всё творение в пепел, и явись из бездны! Взрыв!\nDarkness\n blacker than \x1b[41mblack\x1b[0m and darker than dark, I beseech thee, combine with my deep crimson. The time of awakening cometh. Justice, fallen upon the infallible boundary, appear now as an intangible distortion! Explosion!");
	tb->setForeColor(ctui::ConColor::black);
	tb->setBackColor(ctui::ConColor::grey);
	tb->setTextAlignVertical(ctui::AlignVertical::TOP);
	tb->setTextAlignHorizontal(ctui::AlignHorizontal::CENTER);
	rp->addChild(tb);

	hb.addChild(rp);
	ctui::VerticalBox vb = ctui::VerticalBox(ctui::vec2(1), ctui::vec2(90, 30));
	vb.setAutoSize(true);
	for (int i = 0; i < 2; i++)
	{
		ctui::RectPanel *rp1 = new ctui::RectPanel(ctui::vec2(0), ctui::vec2(15, 5), U' ', ctui::ConColor::black, ctui::ConColor::black);
		rp1->setBorder(true, cs[i + 1], ctui::ConColor::black, 0x2502, 0x2500);
		rp1->setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);
		ctui::RectButton *rb = new ctui::RectButton(ctui::vec2(0, i), ctui::vec2(0), ctui::vec2(3));
		rb->getNormalStyleRect()->setFillStyle(' ', cs[i + 1], cs[i + 1]);
		rb->getHoverStyleRect()->setFillStyle(' ', ctui::ConColor::white, ctui::ConColor::white);
		rb->setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::FULL);
		rb->setPadding(4, 2, 4, 2);
		ctui::TextPanel *tb1 = new ctui::TextPanel(ctui::vec2(2, 1), ctui::vec2(20, 5));
		tb1->setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::FULL);
		tb1->setPadding(2, 1, 2, 1);
		tb1->setText("It is button " + std::to_string(i + 1));
		tb1->setForeColor(ctui::ConColor::black);
		tb1->setBackColor(ctui::ConColor::grey);
		tb1->setTextAlignVertical(ctui::AlignVertical::CENTER);
		tb1->setTextAlignHorizontal(ctui::AlignHorizontal::CENTER);
		rb->addChild(tb1);
		rp1->addChild(rb);
		vb.addChild(rp1);
	}
	ctui::RectPanel *rp1 = new ctui::RectPanel(ctui::vec2(0), ctui::vec2(15, 5), U' ', ctui::ConColor::black, ctui::ConColor::black);
	rp1->setBorder(true, cs[3], ctui::ConColor::black, 0x2502, 0x2500);
	rp1->setUniqueCorners(true, 0x256D, 0x256E, 0x2570, 0x256F);

	ctui::OneLineText *ot = new ctui::OneLineText(ctui::vec2(3, 2), 20);
	ot->setLineText("I like ANIME!");
	ot->setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::TOP);
	ot->getStyleLine()->setTextAlign(ctui::AlignHorizontal::CENTER);
	ot->getStyleLine()->setForeColor(ctui::ConColor::ligth_red);
	ot->getStyleLine()->setBackColor(ctui::ConColor::white);
	ot->setPadding(4, 2, 4, 2);
	rp1->addChild(ot);
	vb.addChild(rp1);

	ctui::VerticalBox vb1 = ctui::VerticalBox(ctui::vec2(1), ctui::vec2(90, 30));
	vb1.setAutoSize(false);
	vb1.setStyle(ctui::PositionType::Relative, ctui::AlignHorizontal::FULL, ctui::AlignVertical::FULL);
	vb1.setPadding(4, 4, 4, 2);
	for (int i = 0; i < 3; i++)
	{
		ctui::OneLineButton *ob = new ctui::OneLineButton(ctui::vec2(0, i + 2), ctui::vec2(3, 2), 20);
		ob->setLineText("Line Button " + std::to_string(i));
		ob->setHoverBackColor(ctui::ConColor::cyan);
		vb1.addChild(ob);
	}
	rp1->addChild(&vb1);
	hb.addChild(&vb);
	cp.addChild(&hb);
	ctui::Panel::setRoot(&cp);
	cp.drawAll();
	ctui::CanvasEventSystem *es = ctui::CanvasEventSystem::getEventSystem();
	ctui::Log::getLog()->logString("Lol");
	while (true)
	{
		es->update();
		if (ctui::ConsoleBase::isKeyJustPressed(ctui::CTKey::CTK_ESC))
		{
			break;
		}
		ctui::Input::update();
		Sleep(20);
	}
	cp.destruct();
	system("cls");
	std::string s = "Hello world!🌍😃🚀✨";
	std::cout << s << '\n';
	ctui::Log::deinit();
	return 0;
}