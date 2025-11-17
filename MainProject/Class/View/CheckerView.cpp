//
// ClassTemplete.cpp
//

#include "CheckerView.h"

using namespace HE;

void CheckerView::Load()
{
	checkerSprite_ = Sprite("Checker.png");
	RenderingPath->AddSprite(&checkerSprite_, 0); // レンダリングパスに追加
	checkerSprite_.params.siz = Math::Vector2(25.0f, 25.0f); // チェッカーのサイズを設定
	checkerSprite_.params.pos = Math::Vector2(-1000.0f, 0.0f); // 初期位置を設定
}


void CheckerView::UpdateChecker(Math::Vector2 cardpos)
{
	checkerSprite_.params.pos = Math::Vector2(cardpos.x + 75.0f / 8, cardpos.y+5.0f ); // チェッカーの位置を更新
}

void CheckerView::CheckerDelete()
{
	checkerSprite_.params.pos = Math::Vector2(-1000.0f, 0.0f); // チェッカーの位置を初期化
}