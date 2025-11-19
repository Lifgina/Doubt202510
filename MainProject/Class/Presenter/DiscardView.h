#pragma once

#include "../../HuEngine.h"

class DiscardView {
public:
	void Load();
	void Initialize(int playerCount,int myPlayerID);
	void Discard(int playerID,int currentDiscardCount);
	void ResetDiscard();


private:
	int playerCount_;
	int myPlayerID_; // 自分のプレイヤーID
	int discardCount_;
	HE::Sprite cardSprite_[52]; // 捨て札のカードスプライト
	HE::SpriteFont discardFont_; // 捨て札の枚数を表示するフォント

};