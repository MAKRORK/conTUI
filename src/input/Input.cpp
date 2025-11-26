#include "input/Input.h"
#include "ConsoleBase.h"
#include "TUI.h"
#include "Log.h"

namespace ctui
{
	std::vector<std::vector<Input *>> Input::inputGrid;
	vec2 Input::inputGridSize = vec2(0);
	vec2 Input::activeInput = vec2(-1);

	void Input::setActiveExist()
	{
		for (int x = 0; x < inputGrid.size(); x++)
		{
			for (int y = 0; y < inputGrid[x].size(); y++)
			{
				if (inputGrid[x][y])
				{
					inputGrid[x][y]->setActive();
					return;
				}
			}
		}
		activeInput = -1;
	}

	Input::~Input()
	{
		Log::getLog()->logString("Input destructed");
		if (activeInput.x == idGridInput.x && activeInput.y == idGridInput.y)
		{
			setActiveExist();
		}
		inputGrid[idGridInput.x][idGridInput.y] = nullptr;
	}

	void Input::update()
	{
		if (ConsoleBase::isKeyJustPressed(TUI::accept))
		{
			inputGrid[activeInput.x][activeInput.y]->accept();
			return;
		}
		int n = 0;
		Input *na = nullptr;
		vec2 idi = activeInput;
		if (activeInput.x != -1 && activeInput.y != -1)
		{
			if (ConsoleBase::isKeyJustPressed(TUI::left))
			{
				n -= 1;
			}
			if (ConsoleBase::isKeyJustPressed(TUI::right))
			{
				n += 1;
			}
			if (n != 0)
			{

				for (int i = 1; i < inputGrid.size(); i++)
				{
					int c = snake(n * i + activeInput.x, (int)inputGrid.size());
					if (inputGrid[c].size() > activeInput.y)
					{
						if (inputGrid[c][activeInput.y] != nullptr)
						{
							na = inputGrid[c][activeInput.y];
							activeInput = vec2(c, activeInput.y);
							break;
						}
					}
				}
			}
			n = 0;
			if (ConsoleBase::isKeyJustPressed(TUI::up))
			{
				n -= 1;
			}
			if (ConsoleBase::isKeyJustPressed(TUI::down))
			{
				n += 1;
			}
			if (n != 0)
			{

				for (int i = 1; i < inputGrid[activeInput.x].size(); i++)
				{

					int c = snake(n * i + activeInput.y, (int)inputGrid[activeInput.x].size());
					if (inputGrid[activeInput.x][c] != nullptr)
					{
						na = inputGrid[activeInput.x][c];
						activeInput = vec2(activeInput.x, c);
						break;
					}
				}
			}
			if (na)
			{

				inputGrid[idi.x][idi.y]->setDisActive();
				na->setActive();
			}
		}
	}

	void Input::setActive()
	{
		activeInput = idGridInput;
		isActive = true;
		startActive();
		redraw();
	}
	void Input::setDisActive()
	{
		isActive = false;
		startDisActive();
		redraw();
	}
	void Input::setGridInputSlot(vec2 _idGridInput)
	{
		idGridInput = _idGridInput;
		if (idGridInput.x <= inputGrid.size())
		{
			for (int i = (int)inputGrid.size(); i <= idGridInput.x; i++)
			{
				inputGrid.push_back(std::vector<Input *>());
			}
		}
		if (idGridInput.y <= inputGrid[idGridInput.x].size())
		{
			for (int i = (int)inputGrid[idGridInput.x].size(); i <= idGridInput.y; i++)
			{
				inputGrid[idGridInput.x].push_back(nullptr);
			}
		}

		inputGrid[_idGridInput.x][_idGridInput.y] = this;
		if (activeInput.x == -1 || activeInput.y == -1)
		{
			setActive();
		}
	}
}