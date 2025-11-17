//
// WinnerView.cpp
//

#include "WinnerView.h"

using namespace HE;

void WinnerView::Load()
{
	
	winnerFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	winnerFont_.params.size = 72; // フォントサイズを設定
	winnerFont_.params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
	RenderingPath->AddFont(&winnerFont_, 1200); // レンダリングパスに追加
	winnerFont_.params.posX = 400.0f; // 勝者表示の位置を設定
	winnerFont_.params.posY = 200.0f; // 勝者表示の位置を設定
	toTitleFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	toTitleFont_.params.size = 36; // タイトルへ戻るフォントのサイズを設定
	toTitleFont_.params.color = Color(0.0f, 0.0f, 0.0f); // タイトルへ戻るフォントの色を設定
	toTitleFont_.params.posX = 500.0f; // タイトルへ戻るフォントの位置を設定
	toTitleFont_.params.posY = 400.0f; // タイトルへ戻るフォントの位置を設定
	RenderingPath->AddFont(&toTitleFont_, 1200); // タイトルへ戻るフォントをレンダリングパスに追加
	winnerBack_ = Sprite("WinnerBack.png"); // 勝者表示の背景スプライトを読み込む
	winnerBack_.params.siz = Math::Vector2(800.0f, 450.0f); // 背景のサイズを設定
	winnerBack_.params.pos = Math::Vector2(240.0f, 360.0-225.0f); // 背景の位置を設定
	winnerBack_.SetHidden(true); // 初期状態では背景を非表示にする
	RenderingPath->AddSprite(&winnerBack_, 1100); // 背景スプライトをレンダリングパスに追加

	
}


void WinnerView::ShowWinner(int winnerID)
{
	if (winnerID < 0 || winnerID >= 4) {
		return; // 無効なプレイヤーID
	}
	winnerFont_.SetText(L"Winner: Player " + std::to_wstring(winnerID + 1)); // 勝者のプレイヤーIDを表示
	toTitleFont_.SetText(L"決定ボタンでタイトルへ戻る"); // タイトルへ戻るメッセージを表示
	winnerBack_.SetHidden(false); // 背景を表示
	
	

}