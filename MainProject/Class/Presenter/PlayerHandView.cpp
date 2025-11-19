//
// PlayerHandView.cpp
//

#include "PlayerHandView.h"

using namespace HE;

void PlayerHandView::Load()
{
	for (int i = 0; i < 52; i++) {
		playerHandSprites_[i]= Sprite("CardsFront.png");
		RenderingPath->AddSprite(&playerHandSprites_[i], 0); // レンダリングパスに追加
		playerHandSprites_[i].params.enableDrawRect(Rectf(
			0.0f, 0.0f, 100.0f, 150.0f
		));
		playerHandSprites_[i].params.siz = Math::Vector2(100.0f, 150.0f); // カードのサイズを設定
		playerHandSprites_[i].params.pos = Math::Vector2(-1000.0f, 0.0f); // カードの位置を初期化
	}
}

void PlayerHandView::UpdatePlayerHands(PlayerData playerdata_)
{
	// プレイヤーの手札を更新
	int playerHands = playerdata_.GetPlayerHands(); // プレイヤーの手札の枚数を取得
	for (int i = 0; i < 52; i++) {
		int rank = playerdata_.GetCard(i).GetRank(); // カードのランクを取得
		if (rank == 0) {
			playerHandSprites_[i].params.pos = Math::Vector2(-1000.0f, 0.0f); // カードの位置を初期化
		}
		else {
			if (i < 25) {
				playerHandSprites_[i].params.pos = Math::Vector2(50.0f * i, RenderingPath->GetLogicalHeight() - 200); // カードの位置を設定
			}
			else {
				playerHandSprites_[i].params.pos = Math::Vector2(50.0f * (i-25), RenderingPath->GetLogicalHeight() - 100); // カードの位置を設定
			}
			
			int suit = playerdata_.GetCard(i).GetSuit(); // カードのスートを取得
			playerHandSprites_[i].params.enableDrawRect(Rectf(
				100.0f * (rank - 1), 150.0f * (suit), 100.0f, 150.0f
			)); // カードの描画矩形を設定

		}

	}

}

Math::Vector2 PlayerHandView::GetCardPosition(int index)
{
	// 指定されたインデックスのカードの位置を取得
	if (index < 0 || index >= 52) {
		return Math::Vector2(-1000.0f, -1000.0f); // 無効なインデックスの場合は画面外の位置を返す
	}
	return Math::Vector2(playerHandSprites_[index].params.pos.x, playerHandSprites_[index].params.pos.y); // カードの位置を返す
}