#pragma once

#include "../../HuEngine.h"
#include "../Model/PlayerData.h"

class PlayerHandView {
public:
	void Load();
	void UpdatePlayerHands(PlayerData playerdata_);
	HE::Math::Vector2 GetCardPosition(int index);
	


private:
	HE::Sprite playerHandSprites_[52]; // プレイヤーの手札を表示するスプライト
};