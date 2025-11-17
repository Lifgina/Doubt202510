#pragma once

#include "../../HuEngine.h"

class CardcountView {
public:
	void Load();
	void Initialize(HE::Math::Vector2 position);
	void SetPlayerID(int playerID);
	void UpdateCardcount(int playerCardcount);


private:
	HE::Sprite cardBackSprite_; // カードの裏面を表示するスプライト
	HE::SpriteFont cardCountsFont_;
	HE::SpriteFont playerIDFont_; // プレイヤーIDを表示するフォント
};