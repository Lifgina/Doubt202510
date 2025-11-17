//
// CardcountView.cpp
//

#include "CardcountView.h"

using namespace HE;

void CardcountView::Load()
{
	cardBackSprite_ = Sprite("CardBack2.png");
	RenderingPath->AddSprite(&cardBackSprite_, 0); // レンダリングパスに追加
	cardCountsFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	cardCountsFont_.params.size = 36; // フォントサイズを設定
	cardCountsFont_.params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
	RenderingPath->AddFont(&cardCountsFont_, 1000); // レンダリングパスに追加
}

void CardcountView::Initialize(Math::Vector2 position)
{
	cardBackSprite_.params.pos = position; // カードの裏面の位置を設定
	cardBackSprite_.params.siz = Math::Vector2(75.0f, 100.0f); // カードのサイズを設定
	cardCountsFont_.params.posX = position.x + 75.0f/2-18; // カードの枚数表示の位置を設定
	cardCountsFont_.params.posY = position.y + 100.0f/2-18; // カードの枚数表示の位置を設定

}

void CardcountView::SetPlayerID(int playerID)
{
	playerIDFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	playerIDFont_.params.size = 24; // フォントサイズを設定
	playerIDFont_.params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
	playerIDFont_.params.posX = cardBackSprite_.params.pos.x-5.0f ; // プレイヤーIDの位置を設定
	playerIDFont_.params.posY = cardBackSprite_.params.pos.y + 100.0f; // プレイヤーIDの位置を設定
	playerIDFont_.SetText(L"プレイヤー" + std::to_wstring(playerID + 1)); // プレイヤーIDを表示
	RenderingPath->AddFont(&playerIDFont_, 1000); // レンダリングパスに追加
}

void CardcountView::UpdateCardcount(int playerCardcount)
{
	cardCountsFont_.SetText(std::to_string(playerCardcount));
}