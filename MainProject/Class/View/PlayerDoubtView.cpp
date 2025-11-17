//
// PlayerDoubtView.cpp
//

#include "PlayerDoubtView.h"

using namespace HE;

void PlayerDoubtView::Load()
{
	for (int i = 0; i < 3; i++) {
		doubtText_[i].params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
		doubtText_[i].params.size = 36; // フォントサイズを設定
		doubtText_[i].params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
		RenderingPath->AddFont(&doubtText_[i], 1000); // レンダリングパスに追加
	}
	doubtText_[0].params.posX = 600.0f; // ダウトメニューの位置を設定
	doubtText_[0].params.posY = 380.0f; // ダウトメニューの位置を設定
	doubtText_[1].params.posX = 600.0f; // ダウトメニューの位置を設定
	doubtText_[1].params.posY = 420.0f; // ダウトメニューの位置を設定
	doubtText_[2].params.posX = 600.0f; // ダウトメニューの位置を設定
	doubtText_[2].params.posY = 460.0f; // ダウトメニューの位置を設定
	
}

void PlayerDoubtView::ShowDoubtMenu()
{

	doubtText_[0].SetText(L"ダウトする?"); // ダウトメニューの位置を設定
	doubtText_[1].SetText(L"↑:ダウト");
	doubtText_[2].SetText(L"↓:スルー");
}

void PlayerDoubtView::HideDoubtMenu()
{
	for (int i = 0; i < 3; i++) {
		doubtText_[i].SetText(""); // ダウトメニューのテキストを空にする
	}
}