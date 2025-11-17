//
// BGMmanager.cpp
//

#include "BGMmanager.h"

using namespace HE;

void BGMmanager::Load()
{
	bgm_[0] = Sound("TitleBGM.wav",Sound::LoopCount::BGM);
	bgm_[1] = Sound("MainBGM.wav", Sound::LoopCount::BGM);
	bgm_[2] = Sound("WinBGM.wav", Sound::LoopCount::SE);

}

void BGMmanager::PlayBGMFromTop(int BGMID)
{
	if (BGMID < 0 || BGMID >= bgmCount_) {
		return; // –³Œø‚ÈBGMID‚Ìê‡‚Í‰½‚à‚µ‚È‚¢
	}
	if (currentBGMID_ != -1) {
		bgm_[currentBGMID_].Stop(); // ‘O‚ÌBGM‚ğ’â~
	}
	
	bgm_[BGMID].PlayFromTop(); // w’è‚³‚ê‚½BGM‚ğÄ¶
}