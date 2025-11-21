#include "boxes/VerticalBox.h"

namespace ctui
{
	vec2 VerticalBox::getPanelLocalPos(Panel *p)
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
			rp.y = n * (int)(s.y / ch->size());
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
		// std::cout << rp.x << ", " << rp.y << '\n';
		return rp;
	}
	vec2 VerticalBox::getPanelLocalSize(Panel *p)
	{
		vec2 s = getAbsoluteSize();
		vec2 rs = vec2(0);
		rs.x = s.x;
		if (getAutoSize())
		{
			rs.y = s.y / (int)getChilds()->size();
		}
		else
		{
			rs.y = p->getSize().y;
		}
		// std::cout << rs.x << ", " << rs.y << '\n';
		return rs;
	}
}