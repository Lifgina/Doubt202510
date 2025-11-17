//
// TurnPlayerView.cpp
//

#include "TurnPlayerView.h"

using namespace HE;

void TurnPlayerView::Load()
{
	turnPlayerFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
}

void TurnPlayerView::Initialize()
{
	turnPlayerFont_.params.size = 36; // フォントサイズを設定
	turnPlayerFont_.params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
	turnPlayerFont_.params.posX = 900.0f; 
	turnPlayerFont_.params.posY = 50.0f; 
	RenderingPath->AddFont(&turnPlayerFont_, 1000); // レンダリングパスに追加
}

void TurnPlayerView::UpdateTurnPlayerView(int turnPlayerID)
{
	turnPlayerFont_.SetText(L"プレイヤー" + std::to_wstring(turnPlayerID + 1)+L"の番"); // 現在の手番のプレイヤーIDを表示
}