#pragma once
#include "panels/Panel.h"

namespace ctui
{
	class Input : public Panel
	{
	private:
		static std::vector<std::vector<Input *>> inputGrid;
		static vec2 inputGridSize;
		static vec2 activeInput;
		vec2 idGridInput;
		bool isActive = false;
		void setGridInputSlot(vec2 _idGridInput);

	public:
			static void update();

		Input(vec2 _idGridInput, vec2 _pos = vec2(0), vec2 _size = vec2(0)) : Panel(_pos, _size)
		{
			setGridInputSlot(_idGridInput);
		}

		virtual void setActive();
		virtual void setDisActive();

		virtual void startActive() {}
		virtual void startDisActive() {}
		virtual void accept() {}

		bool getIsActive() { return isActive; }
	};
}