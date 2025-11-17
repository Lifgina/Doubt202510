#pragma once

#include "../../HuEngine.h"

/// <summary>
/// カードのデータを記録するクラス
/// </summary>

class CardData {
public:
	int GetSuit() const { return suit; }
	int GetRank() const { return rank; }
	void SetSuit(int newSuit) { suit = newSuit; }
	void SetRank(int newRank) { rank = newRank; }

private:
	int suit; // 0: Spade, 1: Heart, 2: Diamond, 3: Club 
	int rank; // 1: Ace, 2-10: Number cards, 11: Jack, 12: Queen, 13: King
};