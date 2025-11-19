//
// SpriteView.cpp
//

#include "SpriteView.h"

using namespace HE;

void SpriteView::Load(string texturePath, int layer)
{
	m_sprite = Sprite(texturePath);
	RenderingPath->AddSprite(&m_sprite, layer);
}

void SpriteView::Initialize(Math::Vector2 size,Math::Vector2 rectSize, Math::Vector2 initialPos)
{
	m_sprite.params.siz = size;
	m_sprite.params.enableDrawRect(Rectf(0.0f, 0.0f, rectSize.x, rectSize.y));
	UpdateSpritePos(initialPos);

}

void SpriteView::UpdateSpritePos(Math::Vector2 pos)
{
	m_sprite.params.pos = pos;
}