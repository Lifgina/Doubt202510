#pragma once

#include "../../HuEngine.h"

class WinnerView {
public:
	void Load();
	void ShowWinner(int winnerPlayerID); // 勝者を表示する関数


private:
	HE::SpriteFont winnerFont_; // 勝者を表示するフォント
	HE::SpriteFont toTitleFont_; // タイトルへ戻るフォント
	HE::Sprite winnerBack_; // 勝者表示の背景スプライト
};