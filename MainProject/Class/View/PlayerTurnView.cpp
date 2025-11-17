//
// PlayerTurnView.cpp
//

#include "PlayerTurnView.h"

using namespace HE;

void PlayerTurnView::Load()
{
	playerTurnFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	playerTurnFont_.params.size = 36; // フォントサイズを設定
	playerTurnFont_.params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
	RenderingPath->AddFont(&playerTurnFont_, 1000); // レンダリングパスに追加
}

void PlayerTurnView::Initialize()
{
	playerTurnFont_.params.posX = 430.0f; // プレイヤーのターンの案内の位置を設定
	playerTurnFont_.params.posY = 400.0f; // プレイヤーのターンの案内の位置を設定
}

void PlayerTurnView::ShowPlayerTurnUI()
{
	playerTurnFont_.SetText(L"カードを4枚まで選んで出そう！"); // プレイヤーのターンの案内を表示
}
void PlayerTurnView::HidePlayerTurnUI()
{
	playerTurnFont_.SetText(L""); // プレイヤーのターンの案内を非表示にする
}