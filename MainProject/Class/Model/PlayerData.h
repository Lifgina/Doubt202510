#pragma once

#include "../../HuEngine.h"
#include "CardData.h"

class PlayerData {
public:
    int GetPlayerID() const { return playerID_; }
    void SetPlayerID(int id) { playerID_ = id; }
    void SetHand(const std::vector<CardData>& hand);
	int GetPlayerHands() const { return playerHands_; }
	CardData GetCard(int index) const { return hand_[index]; } // 手札のカードを取得
    void DisCard(int index);
	

private:
    int playerID_; // プレイヤーのID
    int playerHands_; // プレイヤーの手札の枚数
    CardData hand_[52]; // プレイヤーの手札（最大52枚）
};
