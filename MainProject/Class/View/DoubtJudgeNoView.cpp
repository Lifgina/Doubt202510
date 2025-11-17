//
// DoubtJudgeNoView.cpp
//

#include "DoubtJudgeNoView.h"

using namespace HE;

void DoubtJudgeNoView::Load()
{
	sprite_ = Sprite("CardBack2.png");
	sprite_.params.siz = Math::Vector2(75.0f, 100.0f); // スプライトのサイズを設定
	font_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	font_.params.size = 36; // フォントサイズを設定
	font_.params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
	guideFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	guideFont_.params.size = 24; // ガイドフォントのサイズを設定
	guideFont_.params.color = Color(0.0f, 0.0f, 0.0f); // ガイドフォントの色を設定
	RenderingPath->AddSprite(&sprite_, 1000); // レンダリングパスに追加
	RenderingPath->AddFont(&font_, 1000); // フォントをレンダリングパスに追加
	RenderingPath->AddFont(&guideFont_, 1000); // ガイドフォントをレンダリングパスに追加
}

void DoubtJudgeNoView::Initialize()
{
	sprite_.params.pos = Math::Vector2(800.0f, 200.0f); // スプライトの位置を設定
	font_.params.posX = 800.0f+75.0f/2-9.0f; // フォントの位置を設定
	font_.params.posY = 200.0f+30.0f; // フォントの位置を設定
	guideFont_.params.posX = 815.0f; // フォントの位置を設定
	guideFont_.params.posY = 300.0f; // フォントの位置を設定
	guideFont_.SetText(L"Next"); // ガイドテキストを設定	
}

void DoubtJudgeNoView::UpdateDoubtJudgeNo(int doubtJudgeNo)
{
	if (2<=doubtJudgeNo&&doubtJudgeNo <= 10)
	{
		font_.SetText(std::to_wstring(doubtJudgeNo)); // ダウト判定のカード番号を表示
	}
	else if(doubtJudgeNo == 11)
	{
		font_.SetText(L"J"); // ジャックの場合
	}
	else if (doubtJudgeNo == 12)
	{
		font_.SetText(L"Q"); // クイーンの場合
	}
	else if (doubtJudgeNo == 13)
	{
		font_.SetText(L"K"); // キングの場合
	}
	else if (doubtJudgeNo == 1)
	{
		font_.SetText(L"A"); // エースの場合
	}
	else
	{
		font_.SetText(L""); // 無効な番号の場合は空にする
	}
	
}