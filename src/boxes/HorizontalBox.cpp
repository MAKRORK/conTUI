#include "boxes/HorizontalBox.h"

namespace ctui
{
	vec2 HorizontalBox::getPanelLocalPos(Panel *p)
	{
		vec2 rp = vec2(0);
		vec2 s = getAbsoluteSize();
		std::vector<Panel *> *ch = getChilds();
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
			rp.x = n * (int)(s.x / ch->size());
		}
		else
		{
			for (int n = 0; n < ch->size(); n++)
			{
				if ((*ch)[n] == p)
					break;
				rp.x += (*ch)[n]->getSize().x;
			}
		}
		// std::cout << rp.x << ", " << rp.y << '\n';
		return rp;
	}
	vec2 HorizontalBox::getPanelLocalSize(Panel *p)
	{

		vec2 s = getAbsoluteSize();

		vec2 rs = vec2(0);
		rs.y = s.y;
		if (getAutoSize())
		{

			int c = (int)getChilds()->size();
			if (c == 0)
			{
				c = 1;
			}
			rs.x = s.x / c;
		}
		else
		{
			rs.x = p->getSize().x;
		}

		return rs;
	}
}