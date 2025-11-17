//
// GameLog.cpp
//

#include "GameLog.h"

using namespace HE;

void GameLog::Load()
{
	for (int i = 0; i < 10; i++) {
		logText_[i].params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
		logText_[i].params.size = 20; // フォントサイズを設定
		logText_[i].params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
		RenderingPath->AddFont(&logText_[i], 1000); // レンダリングパスに追加
		logText_[i].params.posX = 1000.0f; // ログの位置を設定
		logText_[i].params.posY = 275.0f + i * 20.0f; // ログの位置を設定
		logText_[i].SetText(L""); // 初期状態では空のテキスト
	}
}


void GameLog::LogUpdate()
{
	// ログの更新処理
	for (int i = 9; i > 0; --i) {
		logText_[i].SetText(logText_[i - 1].GetText()); // 前のログを後ろにずらす
	}

}

void GameLog::DiscardLog(int playerID, int discardCount)
{
	LogUpdate(); // ログを更新
	logText_[0].SetText(L"プレイヤー" + std::to_wstring(playerID + 1) + L"はカードを" + std::to_wstring(discardCount) + L"枚捨てた。");
}

void GameLog::DoubtLog(int playerID, bool isDoubt)
{
	LogUpdate(); // ログを更新
	if (isDoubt) {
		logText_[0].SetText(L"プレイヤー" + std::to_wstring(playerID + 1) + L"はダウトを宣言した！");
	}
	else {
		logText_[0].SetText(L"プレイヤー" + std::to_wstring(playerID + 1) + L"はスルーした。");
	}
}

void GameLog::PenaltyLog(int playerID, bool doubtCorrect)
{
	LogUpdate(); // ログを更新
	if (doubtCorrect) {
		logText_[0].SetText(L"プレイヤー" + std::to_wstring(playerID + 1) + L"はダウトに成功！！");
	}
	else {
		logText_[0].SetText(L"プレイヤー" + std::to_wstring(playerID + 1) + L"はダウトに失敗！！");
	}
}