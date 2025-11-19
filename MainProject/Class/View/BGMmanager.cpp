//
// BGMmanager.cpp
//

#include "BGMmanager.h"

using namespace HE;

void BGMmanager::Load()
{
	m_bgm[0] = Sound("TitleBGM.wav",Sound::LoopCount::BGM);
	m_bgm[1] = Sound("MainBGM.wav", Sound::LoopCount::BGM);
	m_bgm[2] = Sound("WinBGM.wav", Sound::LoopCount::SE);

}

void BGMmanager::PlayBGMFromTop(int BGMID)
{
	if (BGMID < 0 || BGMID >= m_bgmCount) {
		return; // –³Œø‚ÈBGMID‚Ìê‡‚Í‰½‚à‚µ‚È‚¢
	}
	if (m_currentBGMID != -1) {
		m_bgm[m_currentBGMID].Stop(); // ‘O‚ÌBGM‚ğ’â~
	}
	
	m_bgm[BGMID].PlayFromTop(); // w’è‚³‚ê‚½BGM‚ğÄ¶
}