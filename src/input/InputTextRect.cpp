#include "input/InputTextRect.h"
#include "ConsoleBase.h"
#include "TUI.h"
#include "TextTUI.h"
#include <sstream>
#include <iomanip>

namespace ctui
{
	void InputTextRect::accept()
	{
		Input::setCurrentSelected(this);
		ConsoleBase *cb = ConsoleBase::getConsoleBase();
		cb->consoleEventsBufferClear();
		redraw();
		ConsoleBase::setCursorToPoint(getAbsolutePos() + tp->getPaddingLT() + realCursorPos);
	}

	void InputTextRect::setTextColor(ConColor col)
	{
		tp->setForeColor(col);
		textColor = col;
		tp->setBackColor(hoverRect.getBackFillColor());
	}

	void InputTextRect::setTextPadding(int p)
	{
		setTextPadding(p, p, p, p);
	}
	void InputTextRect::setTextPadding(int l, int t, int r, int b)
	{
		tp->setPadding(l, t, t, b);
	}

	int InputTextRect::getTextCursorPos(vec2 realPos, vec2 cps, std::vector<int> &lens, vec2 size)
	{
		int p = 0;
		realPos += cps;
		if (realPos.y < 0)
		{
			realPos.y = 0;
		}
		else if (realPos.y >= lens.size())
		{
			realPos.y = (int)lens.size() - 1;
		}
		if (realPos.x > size.x)
		{
			realPos.x = size.x;
		}
		for (int i = 0; i < realPos.y; i++)
		{
			if (lens.size() > i)
				p += lens[i];
		}
		if (lens.size() == 0)
			p += realPos.x;
		else
			p += ctmin(realPos.x, lens[realPos.y]);

		if (p < 0)
			p = 0;
		p = ctmin(p, (int)txtt.size());
		if (cps.y != 0 && p - 1 >= 0)
		{
			if (txtt[p - 1] == '\n' && realPos.x != 0)
			{
				p -= 1;
			}
		}
		return p;
	}

	vec2 InputTextRect::getRealCursorPos(int txtPos, std::vector<int> &lens)
	{
		vec2 p = 0;
		int n = txtPos;
		if (lens.size() == 0)
		{
			p.x = n;
			return p;
		}
		for (int i = 0; i < lens.size() - 1; i++)
		{

			if (n - lens[i] >= 0)
			{

				n -= lens[i];
				p.y++;
			}
			else
				break;
		}
		p.x = n;

		return p;
	}

	void InputTextRect::updateInput()
	{
		if (ConsoleBase::isKeyJustPressed(TUI::exit))
		{
			Input::disableCurrentSelected();
		}

		bool bps = false;
		bool del = false;
		bool selStart = false;
		vec2 cps = 0;
		int wps = 0;
		if (ConsoleBase::isKeyJustPressed(TUI::left))
		{
			cps.x -= 1;
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
				cps.x = 0;
			}
		}
		if (ConsoleBase::isKeyJustPressed(TUI::right))
		{
			cps.x += 1;
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
				cps.x = 0;
			}
		}
		if (ConsoleBase::isKeyJustPressed(TUI::up))
		{
			cps.y -= 1;
			if (ConsoleBase::isKeyPressed(TUI::selectButton))
			{
				selStart = true;
				if (!selectStarted)
				{
					selectStarted = true;
					selectStartPoint = txtCursorPos;
				}
			}
		}
		if (ConsoleBase::isKeyJustPressed(TUI::down))
		{
			cps.y += 1;
			if (ConsoleBase::isKeyPressed(TUI::selectButton))
			{
				selStart = true;
				if (!selectStarted)
				{
					selectStarted = true;
					selectStartPoint = txtCursorPos;
				}
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
		if (s != "" || cps.x != 0 || cps.y != 0 || (bps || del) || wps != 0)
		{
			vec2 sz = getAbsoluteSize() - (tp->getPaddingLT() + tp->getPaddingRB());
			vec2 pos = getAbsolutePos() + tp->getPaddingLT();
			bool rd = false;

			if (cps.x != 0 || cps.y != 0 || wps != 0)
			{
				txtCursorPos = getTextCursorPos(realCursorPos, cps, realLens, sz);
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

			if (rd)
			{

				realLens = std::vector<int>();
				// attribute as = attribute(ConColor::getForeColor(textColor));
				// as.addAttribute(ConColor::getBackColor(selectedColor));
				txt = chrsToStringWithSelected(txtt, selected, selectedTextStyle);

				// txt = chrsToString(txtt);

				rawText *rt = autoWrap(txt, sz.x, 0, vec2(sz.x, 10000), realLens, true, tp->getForeColor(), tp->getBackColor());
				rawText *rrr = new rawText(sz);

				attribute a = attribute(ConColor::getForeColor(tp->getForeColor()));
				a.addAttribute(ConColor::getBackColor(tp->getBackColor()));

				for (int i = 0; i < rrr->size.y; i++)
				{
					if (i < rt->size.y)
					{
						rrr->txt[i] += rt->txt[i];
						rrr->txt[i] += a.getAttributes();
						rrr->txt[i] += getLine(sz.x - realLens[i]);
						rrr->txt[i] += attribute::clear.getAttributes();
					}
					else
					{
						rrr->txt[i] += a.getAttributes();
						rrr->txt[i] += getLine(sz.x);
						rrr->txt[i] += attribute::clear.getAttributes();
					}
				}
				delete rt;
				tp->setRawText(rrr);
				tp->redraw();
			}
			realCursorPos = getRealCursorPos(txtCursorPos, realLens);
			ConsoleBase::setCursorToPoint(pos + realCursorPos);
		}
	}

	rawText *InputTextRect::getRawText(vec2 offset, vec2 maxSize)
	{
		if (r)
			delete r;
		r = nullptr;
		if (getIsActive())
		{
			r = hoverRect.getRawText(offset, maxSize, getAbsoluteSize());
		}
		else
			r = normalRect.getRawText(offset, maxSize, getAbsoluteSize());
		return r;
	}
}