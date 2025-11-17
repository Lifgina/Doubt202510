#pragma once

#include "../../HuEngine.h"

class PlayerDoubtView {
public:
	void Load();
	void ShowDoubtMenu();
	void HideDoubtMenu();


private:
	HE::SpriteFont doubtText_[3]; // ダウトのテキストを表示するフォント
};