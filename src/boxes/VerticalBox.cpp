#include "boxes/VerticalBox.h"
#include "Log.h"

namespace ctui
{
	vec2 VerticalBox::getPanelLocalPos(Panel *p)
	{
		vec2 rp = vec2(0);
		vec2 s = getAbsoluteSize();
		std::vector<Panel *> *ch = getChilds();
		int c = (int)ch->size();
		if (c == 0)
		{
			c = 1;
		}
		int d = (int)(s.y % c);
		Log::getLog()->logString("d = " + std::to_string(d));
		if (getAutoSize())
		{
			int n = 0;
			for (int i = 0; i < ch->size(); i++)
			{
				if ((*ch)[i] == p)
				{
					n = i;
					break;
				}
			}
			rp.y = n * (int)(s.y / c);
			if (c - n < d)
			{
				rp.y += n - (c - d);
			}
		}
		else
		{
			for (int n = 0; n < ch->size(); n++)
			{
				if ((*ch)[n] == p)
					break;
				rp.y += (*ch)[n]->getSize().y;
			}
		}

		return rp;
	}
	vec2 VerticalBox::getPanelLocalSize(Panel *p)
	{
		vec2 s = getAbsoluteSize();
		vec2 rs = vec2(0);
		rs.x = s.x;

		if (getAutoSize())
		{
			std::vector<Panel *> *ch = getChilds();
			int c = (int)ch->size();
			if (c == 0)
			{
				c = 1;
			}
			int d = (int)(s.y % c);
			rs.y = s.y / c;
			int n = 0;
			for (int i = 0; i < ch->size(); i++)
			{
				if ((*ch)[i] == p)
				{
					n = i;
					break;
				}
			}
			if (c - n <= d)
			{
				rs.y++;
			}
		}
		else
		{
			rs.y = p->getSize().y;
		}

		return rs;
	}
}