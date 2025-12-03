#include "input/InputTextLine.h"
#include "ConsoleBase.h"
#include "TUI.h"
#include "TextTUI.h"

namespace ctui
{
	rawText *InputTextLine::getRawText(vec2 offset, vec2 maxSize)
	{
		if (r)
			delete r;
		r = oneLine.getRawText(offset, maxSize, getAbsoluteSize());
		return r;
	}

	std::vector<char32_t> InputTextLine::getTextWithOffset(std::vector<char32_t> &txtv, int offset, int maxLength)
	{
		std::vector<char32_t> tttt;
		for (int i = offset; i < ctmin((int)txtv.size(), offset + maxLength); i++)
		{
			tttt.push_back(txtv[i]);
		}
		return tttt;
	}

	void InputTextLine::accept()
	{
		Input::setCurrentSelected(this);
		ConsoleBase *cb = ConsoleBase::getConsoleBase();
		cb->consoleEventsBufferClear();
		oneLine.setForeColor(foreColor);
		oneLine.setBackColor(backColor);
		redraw();
		ConsoleBase::setCursorToPoint(getAbsolutePos());
	}

	void InputTextLine::startActive()
	{
		oneLine.setForeColor(hoverForeColor);
		oneLine.setBackColor(hoverBackColor);
	}

	void InputTextLine::startDisActive()
	{
		oneLine.setForeColor(foreColor);
		oneLine.setBackColor(backColor);
	}
	void InputTextLine::setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV)
	{
		if (_alignV == AlignVertical::FULL)
		{
			_alignV = AlignVertical::CENTER;
		}
		Panel::setStyle(_posType, _alignH, _alignV);
	}

	void InputTextLine::updateInput()
	{

		if (ConsoleBase::isKeyJustPressed(TUI::exit))
		{
			Input::disableCurrentSelected();
		}

		bool bps = false;
		bool del = false;
		bool selStart = false;
		int cps = 0;
		int wps = 0;
		if (ConsoleBase::isKeyJustPressed(TUI::left))
		{
			cps -= 1;
			if (ConsoleBase::isKeyPressed(TUI::selectButton))
			{
				selStart = true;
				if (!selectStarted)
				{
					selectStarted = true;
					selectStartPoint = txtCursorPos;
				}
			}
			if (ConsoleBase::isKeyPressed(TUI::wordJampButton))
			{
				wps += -1;
				cps = 0;
			}
		}
		if (ConsoleBase::isKeyJustPressed(TUI::right))
		{
			cps += 1;
			if (ConsoleBase::isKeyPressed(TUI::selectButton))
			{
				selStart = true;
				if (!selectStarted)
				{
					selectStarted = true;
					selectStartPoint = txtCursorPos;
				}
			}
			if (ConsoleBase::isKeyPressed(TUI::wordJampButton) || wps != 0)
			{
				wps += 1;
				cps = 0;
			}
		}
		if (ConsoleBase::isKeyJustPressed(CTKey::CTK_BACKSPACE))
		{
			bps = true;
		}
		if (ConsoleBase::isKeyJustPressed(CTKey::CTK_DELETE))
		{
			del = true;
		}

		ConsoleBase *cb = ConsoleBase::getConsoleBase();
		std::string st = cb->getEnterText();
		std::string s = "";
		for (int i = 0; i < st.size(); i++)
		{
			if (st[i] == '\r')
			{
				s += '\n';
			}
			else if (st[i] == '\t')
			{
				s += ' ';
			}
			else if (st[i] == '\b')
				continue;
			else
			{
				s += st[i];
			}
		}
		if (s != "" || cps != 0 || (bps || del) || wps != 0)
		{
			vec2 sz = getAbsoluteSize();
			vec2 pos = getAbsolutePos();
			bool rd = false;

			if (cps != 0 || wps != 0)
			{
				txtCursorPos = clamp(txtCursorPos + cps, 0, (int)txtt.size());

				if (wps != 0)
				{
					txtCursorPos = findLastDiv(txtt, txtCursorPos, wps);
				}
				if (selectStarted && selStart)
				{
					selected.x = ctmin(txtCursorPos, selectStartPoint);
					selected.y = ctmax(txtCursorPos, selectStartPoint);
					rd = true;
				}
			}
			if (bps)
			{
				if (selected.x - selected.y != 0)
				{
					txtt.erase(txtt.begin() + selected.x, txtt.begin() + selected.y);
					txtCursorPos = selected.x;
					selectStarted = false;
					selectStartPoint = -1;
					selected = 0;
					rd = true;
				}
				else if (txtCursorPos > 0)
				{
					txtt.erase(txtt.begin() + (size_t)(txtCursorPos - 1));
					txtCursorPos--;
					rd = true;
				}
			}
			if (del && txtCursorPos < txtt.size())
			{
				if (selected.x - selected.y != 0)
				{
					txtt.erase(txtt.begin() + selected.x, txtt.begin() + selected.y);
					txtCursorPos = selected.x;
					selectStarted = false;
					selectStartPoint = -1;
					selected = 0;
				}
				else
					txtt.erase(txtt.begin() + (size_t)(txtCursorPos));
				rd = true;
			}

			if (s != "")
			{
				std::vector<char32_t> chrs = stringToChars(s);
				if (selected.x - selected.y != 0)
				{
					txtt.erase(txtt.begin() + selected.x, txtt.begin() + selected.y);
					txtt.insert((txtt.begin()) + (size_t)selected.x, chrs.begin(), chrs.end());
					txtCursorPos = selected.x;
					selectStarted = false;
					selectStartPoint = -1;
					selected = 0;
				}
				else
					txtt.insert((txtt.begin()) + (size_t)txtCursorPos, chrs.begin(), chrs.end());
				txtCursorPos += (int)chrs.size();

				rd = true;
			}
			if (selectStarted && !selStart)
			{
				selectStarted = false;
				selectStartPoint = -1;
				selected = 0;

				rd = true;
			}

			if (txtCursorPos - textHorizontalOffset >= sz.x)
			{
				textHorizontalOffset += (txtCursorPos - textHorizontalOffset) - sz.x + 1;
				rd = true;
			}
			else if (txtCursorPos - textHorizontalOffset < 0)
			{
				textHorizontalOffset += txtCursorPos - textHorizontalOffset;
				rd = true;
			}

			if (rd)
			{
				if (txtt.size() - textHorizontalOffset >= sz.x)
				{
					textHorizontalOffset += ((int)txtt.size() - textHorizontalOffset) - sz.x + 1;
				}
				oneLine.setLineText(chrsToStringWithSelected(getTextWithOffset(txtt, textHorizontalOffset, sz.x), selected, selectedTextStyle));
				redraw();
			}
			ConsoleBase::setCursorToPoint((pos + vec2(txtCursorPos - textHorizontalOffset, 0)));
		}
	}
}