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

		vec2 cps = 0;
		if (ConsoleBase::isKeyJustPressed(TUI::left))
		{
			cps.x -= 1;
		}
		if (ConsoleBase::isKeyJustPressed(TUI::right))
		{
			cps.x += 1;
		}
		if (ConsoleBase::isKeyJustPressed(TUI::up))
		{
			cps.y -= 1;
		}
		if (ConsoleBase::isKeyJustPressed(TUI::down))
		{
			cps.y += 1;
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
		if (s != "" || cps.x != 0 || cps.y != 0 || (bps || del))
		{
			vec2 sz = getAbsoluteSize() - (tp->getPaddingLT() + tp->getPaddingRB());
			vec2 pos = getAbsolutePos() + tp->getPaddingLT();
			bool rd = false;
			txtCursorPos = getTextCursorPos(realCursorPos, cps, realLens, sz);
			if (bps && txtCursorPos > 0)
			{
				txtt.erase(txtt.begin() + (size_t)(txtCursorPos - 1));
				txtCursorPos--;
				rd = true;
			}
			if (del && txtCursorPos < txtt.size())
			{
				txtt.erase(txtt.begin() + (size_t)(txtCursorPos));
				rd = true;
			}

			if (s != "")
			{
				std::vector<char32_t> chrs = stringToChars(s);
				txtt.insert((txtt.begin()) + (size_t)txtCursorPos, chrs.begin(), chrs.end());
				txtCursorPos += (int)chrs.size();
				rd = true;
			}
			realCursorPos = getRealCursorPos(txtCursorPos, realLens);
			if (rd)
			{
				realLens = std::vector<int>();
				txt = chrsToString(txtt);
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