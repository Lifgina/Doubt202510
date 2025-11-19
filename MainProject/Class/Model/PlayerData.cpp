//
// PlayerDate.cpp
//

#include "PlayerData.h"

void PlayerData::SetHand(const std::vector<CardData>& hand) {
    m_playerHands = static_cast<int>(hand.size());
    for (int i = 0; i < m_playerHands; ++i) {
        m_hand[i] = hand[i];
    }
}
void PlayerData::DisCard(int index) {
	if (index < 0 || index >= m_playerHands) {
		return; // 無効なインデックス
	}
	// 手札からカードを削除
	for (int i = index; i < m_playerHands ; ++i) {
		m_hand[i] = m_hand[i + 1];
	}
	--m_playerHands; // 手札の枚数を減らす
}

