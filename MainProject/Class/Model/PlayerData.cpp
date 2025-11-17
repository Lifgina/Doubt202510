//
// PlayerDate.cpp
//

#include "PlayerData.h"

void PlayerData::SetHand(const std::vector<CardData>& hand) {
    playerHands_ = static_cast<int>(hand.size());
    for (int i = 0; i < playerHands_; ++i) {
        hand_[i] = hand[i];
    }
}
void PlayerData::DisCard(int index) {
	if (index < 0 || index >= playerHands_) {
		return; // 無効なインデックス
	}
	// 手札からカードを削除
	for (int i = index; i < playerHands_ ; ++i) {
		hand_[i] = hand_[i + 1];
	}
	--playerHands_; // 手札の枚数を減らす
}

