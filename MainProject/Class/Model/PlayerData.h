#pragma once

#include "../../HuEngine.h"
#include "CardData.h"

class PlayerData {
public:
    int GetPlayerID() const { return m_playerID; }
    void SetPlayerID(int id) { m_playerID = id; }
    void SetHand(const std::vector<CardData>& hand);
	int GetPlayerHands() const { return m_playerHands; }
	CardData GetCard(int index) const { return m_hand[index]; } // 手札のカードを取得
    void DisCard(int index);
	

private:
    int m_playerID; // プレイヤーのID
    int m_playerHands; // プレイヤーの手札の枚数
    CardData m_hand[52]; // プレイヤーの手札（最大52枚）
};
