#pragma once

#include "../../HuEngine.h"

class GameLog {
public:
	void Load();
	void LogUpdate();
	void DiscardLog(int playerID,int discardCount);
	void DoubtLog(int playerID,bool isDoubt);
	void PenaltyLog(int playerID,bool doubtCorrect);


private:
	HE::SpriteFont logText_[10]; // ゲームログを表示するフォント
};