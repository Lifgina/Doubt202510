#pragma once

#include "../../HuEngine.h"

using namespace std;

class SpriteView {
public:
	void Load(string texturePath, int layer);
	void Initialize(HE::Math::Vector2 size, HE::Math::Vector2 rectSize,HE::Math::Vector2 initialPos);
	void UpdateSpritePos(HE::Math::Vector2 pos);


protected:
	HE::Sprite sprite;
};