//
// TextView.cpp
//

#include "TextView.h"

using namespace HE;

void TextView::Load(int order, std::string FontAddress)
{
	textFont.params.style = Font::AddFontStyle(FontAddress);
	RenderingPath->AddFont(&textFont, order);
}

void TextView::Initialize(Math::Vector2 Pos, int RedValue, int GreenValue, int BlueValue, std::string InitialText, float Size)
{
	textFont.SetText(InitialText);
	textFont.params.posX = Pos.x;
	textFont.params.posY = Pos.y;
	textFont.params.color = Color(RedValue, GreenValue, BlueValue);
	textFont.params.size = Size;
}

void TextView::UpdateText(std::string NewText)
{
	textFont.SetText(NewText);
}