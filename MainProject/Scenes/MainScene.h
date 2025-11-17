#pragma once

#include "../HuEngine.h"
#include "../Class/Model/GameManager.h"
#include "../Class/View/PlayerHandView.h"
#include "../Class/View/CheckerView.h"
#include "../Class/View/CardCountView.h"
#include "../Class/View/WinnerView.h"
#include "../Class/View/PlayerDoubtView.h"
#include "../Class/View/DoubtJudgeNoView.h"
#include "../Class/View/DiscardView.h"
#include "../Class/View/PlayerTurnView.h"
#include "../Class/View/TurnPlayerView.h"
#include "../Class/View/GameLog.h"
#include "../Class/View/TextView.h"
#include "../Class/View/SpriteView.h"
#include "../Class/View/BGMmanager.h"



class MainScene : public HE::Scene
{
public:
	MainScene();
	virtual ~MainScene() { Terminate(); }

	void ResizeLayout() override;

	void Load() override;
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;

	void MonitorGameManager();
	void MonitorDiscard();
	void MyPlayerCardSelect();
	void MyPlayerCardSelectReset();
	void MyDoubtSelect();
	

private:
	GameManager gameManager_;
	PlayerHandView playerHandView_; // プレイヤーの手札を表示するクラス
	CheckerView checkerView_[4]; // チェッカーを表示するクラス
	CardcountView cardCountView_[4]; // カードの枚数を表示するクラス
	WinnerView winnerView_; // 勝者を表示するクラス
	PlayerDoubtView playerDoubtView_; // ダウトのメニューを表示するクラス
	DoubtJudgeNoView doubtJudgeNoView_; // ダウト判定のカード番号を表示するクラス
	DiscardView discardView_; // 捨て札を表示するクラス
	PlayerTurnView playerTurnView_; // プレイヤーのターンの案内を表示するクラス
	TurnPlayerView turnPlayerView_; // 現在の手番のプレイヤーを表示するクラス
	GameLog gameLog_; // ゲームのログを表示するクラス
	BGMmanager bgmManager_; // BGMを管理するクラス

	SpriteView m_bgSpriteView; // 背景スプライトを表示するクラス
	SpriteView m_markerView; // マーカーのスプライトを表示するクラス（SpriteViewを利用）
	SpriteView m_cardCountBGSpriteView[4]; // カード枚数表示の背景スプライトを表示するクラス


	int maxCardsOnScreen_ = 25; // 画面上に表示する最大のカード枚数

	int playerCount_; // プレイヤーの人数
	int myPlayerID_; // 自分のプレイヤーID
	int turnPlayerID_; // 現在のプレイヤーID
	int doubtPlayerID_; // ダウトを行うプレイヤーのID
	int winnerID_; // 勝者のプレイヤーID
	int doubtJudgeNo_; // ダウト判定のカード番号
	int selectingCardIndex_; // 選択中のカードのインデックス
	int selectedCardIndex_[4]; // 選択されたカードのインデックス
	int selectedCardCount_; // 選択されたカードの枚数
	int prevDiscardCount_ ; // 前回の捨て札の枚数
	int prevPlayerHands_; // 前フレームのプレイヤーの手札の枚数
	bool isDiscardTurn_ ; // 捨て札のターンかどうか
	bool isInputed_; // 入力がされたかどうか
	bool isPlayedAudio_ ; // オーディオが再生されたかどうか

	float stickDeadZone_ = 0.2f; // スティックのデッドゾーン
};
