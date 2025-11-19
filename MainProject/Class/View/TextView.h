#pragma once

#include "../../HuEngine.h"

class TextView {
public:
	void Load(int order, std::string FontAddress);
	void Initialize(HE::Math::Vector2 Pos, int RedValue, int GreenValue, int BlueValue, std::wstring InitialText, float size);
	void UpdateText(std::wstring NewText);
	void UpdatePos(HE::Math::Vector2 Pos) { textFont.params.posX = Pos.x; textFont.params.posY = Pos.y; }


private:
	HE::SpriteFont textFont;

};