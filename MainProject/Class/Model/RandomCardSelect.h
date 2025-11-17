#pragma once

#include "../../HuEngine.h"
#include "CardData.h"

class RandomCardSelect {
public:
	void CardSelect(int hands,int judgeNo,CardData cards[]);
	int GetSelectedCardIndex(int index) const {
		return selectedCardIndex_[index];
	}

private:
	int selectedCardIndex_[4]; // 選択されたカードのインデックスを初期化
	float correctDiscardRate_ = 0.7; // 正しいカードをカードを出す確率
	float discard1Rate_ = 0.4; // 1枚捨てる確率
	float discard2Rate_ = 0.3; // 2枚捨てる確率
	float discard3Rate_ = 0.2; // 3枚捨てる確率
	//4枚捨てる確率は1 - (discard1Rate_ + discard2Rate_ + discard3Rate_)

};