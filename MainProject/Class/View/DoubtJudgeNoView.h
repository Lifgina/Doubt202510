#pragma once

#include "../../HuEngine.h"

class DoubtJudgeNoView {
public:
	void Load();
	void Initialize();
	void UpdateDoubtJudgeNo(int doubtJudgeNo);


private:
	HE::Sprite sprite_; 
	HE::SpriteFont font_; 
	HE::SpriteFont guideFont_; // ガイド用のフォント
};