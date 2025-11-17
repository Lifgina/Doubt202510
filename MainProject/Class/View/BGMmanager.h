#pragma once

#include "../../HuEngine.h"

class BGMmanager {
public:
	void Load(); // BGMをロードする関数
	void PlayBGMFromTop(int BGMID);

private:
	int bgmCount_ = 3; // 管理するBGMの数
	HE::Sound bgm_[3]; // BGMを管理するオブジェクト
	int currentBGMID_ = -1; // 現在再生中のBGMのIDを管理する変数
};