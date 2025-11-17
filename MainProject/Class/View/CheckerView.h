#pragma once

#include "../../HuEngine.h"

class CheckerView {
public:
	void Load();
	void UpdateChecker(HE::Math::Vector2 cardpos);
	void CheckerDelete();


private:
	
	HE::Sprite checkerSprite_; // チェッカーのスプライト	
};