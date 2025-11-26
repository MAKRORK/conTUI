#include "Panel.h"
#include "OneLine.h"

namespace ctui
{
	class OneLineText : public Panel
	{
	private:
		OneLine oneLine = OneLine();

	public:
		OneLineText(vec2 _pos, int length) : Panel(_pos, vec2(length, 1))
		{
			debug_sym = 'O';
		}
		rawText *getRawText(vec2 offset, vec2 maxSize) override;
		OneLine *getStyleLine() { return &oneLine; }
		void setLineText(std::string str) { oneLine.setLineText(str); }

		void setStyle(PositionType _posType, AlignHorizontal _alignH, AlignVertical _alignV) override;
	};
}