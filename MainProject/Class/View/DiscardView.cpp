//
// DiscardView.cpp
//

#include "DiscardView.h"
#include <numbers>

using namespace HE;

void DiscardView::Load()
{
	for (int i = 0; i < 52; i++) {
		cardSprite_[i] = Sprite("CardBack.png");
		cardSprite_[i].params.siz = Math::Vector2(100.0f, 150.0f); // カードのサイズを設定
		RenderingPath->AddSprite(&cardSprite_[i], 1000); // レンダリングパスに追加
	}
	discardFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	discardFont_.params.size = 36; // フォントサイズを設定
	discardFont_.params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
	RenderingPath->AddFont(&discardFont_, 1000); // レンダリングパスに追加
}

void DiscardView::Initialize(int playerCount, int myPlayerID)
{
	myPlayerID_ = myPlayerID; // 自分のプレイヤーIDを設定
	playerCount_ = playerCount; // プレイヤーの人数を設定
	for (int i = 0; i < 52; i++) {
		cardSprite_[i].params.pos = Math::Vector2(640.0f, 300.0f); // カードの位置を設定
		cardSprite_[i].params.pivot = Math::Vector2(0.5, 0.5); // カードのピボットを中央に設定
		cardSprite_[i].SetHidden(true); // 初期状態ではカードを非表示にする
	}
	discardFont_.params.posX = 350.0f; // 捨て札の枚数表示の位置を設定
	discardFont_.params.posY = 200.0f; // 捨て札の枚数表示の位置を設定
	discardFont_.SetText(L"捨て札:0枚"); // 捨て札の枚数表示をリセット
}

void DiscardView::Discard(int playerID, int currentDiscardCount)
{
	for (int i = 0; i < currentDiscardCount; i++)
	{
		discardCount_ += 1;
		cardSprite_[discardCount_].SetHidden(false);
		cardSprite_[discardCount_].params.pos.x = 640.0f - 20.0f*(currentDiscardCount-1) + 40.0f * (i); // カードの位置を設定
		cardSprite_[discardCount_].params.rotation = 2 * std::numbers::pi / playerCount_ * (playerID + playerCount_ - myPlayerID_ % playerCount_); // 回転角度を設定
	}
	discardFont_.SetText(L"捨て札:"+std::to_wstring(discardCount_)+L"枚"); // 捨て札の枚数を表示
}

void DiscardView::ResetDiscard()
{
	for (int i = 0; i < 52; i++) {
		cardSprite_[i].SetHidden(true); // 全てのカードを非表示にする
		cardSprite_[i].params.pos = Math::Vector2(640.0f, 300.0f); // カードの位置を初期化
	}
	discardCount_ = 0; // 捨て札の枚数をリセット
	discardFont_.SetText(L"捨て札:0枚"); // 捨て札の枚数表示をリセット
}