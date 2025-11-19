//
// TextView.cpp
//

#include "TextView.h"

using namespace HE;

void TextView::Load(int order, std::string FontAddress)
{
	m_textFont.params.style = Font::AddFontStyle(FontAddress);
	RenderingPath->AddFont(&m_textFont, order);
}

void TextView::Initialize(Math::Vector2 Pos, int RedValue, int GreenValue, int BlueValue, std::wstring InitialText, float Size)
{
	m_textFont.SetText(InitialText);
	m_textFont.params.posX = Pos.x;
	m_textFont.params.posY = Pos.y;
	m_textFont.params.color = Color(RedValue, GreenValue, BlueValue);
	m_textFont.params.size = Size;
}

void TextView::UpdateText(std::wstring NewText)
{
	m_textFont.SetText(NewText);
}