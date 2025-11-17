#pragma once

#include "../../HuEngine.h"

class PlayerTurnView {
public:
	void Load();
	void Initialize();
	void ShowPlayerTurnUI();
	void HidePlayerTurnUI();


private:
	HE::SpriteFont playerTurnFont_; // プレイヤーのターンの案内を表示するフォント
};