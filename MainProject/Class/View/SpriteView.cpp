//
// SpriteView.cpp
//

#include "SpriteView.h"

using namespace HE;

void SpriteView::Load(string texturePath, int layer)
{
	sprite = Sprite(texturePath);
	RenderingPath->AddSprite(&sprite, layer);
}

void SpriteView::Initialize(Math::Vector2 size,Math::Vector2 rectSize, Math::Vector2 initialPos)
{
	sprite.params.siz = size;
	sprite.params.enableDrawRect(Rectf(0.0f, 0.0f, rectSize.x, rectSize.y));
	UpdateSpritePos(initialPos);

}

void SpriteView::UpdateSpritePos(Math::Vector2 pos)
{
	sprite.params.pos = pos;
}