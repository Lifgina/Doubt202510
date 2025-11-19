#pragma once

#include "../HuEngine.h"
#include "../Class/Model/GameManager.h"
#include "../Class/Presenter/PlayerHandView.h"
#include "../Class/Presenter/DiscardView.h"
#include "../Class/Presenter/GameLog.h"
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

	void CardCountViewInitialize();
	void UpdateDoubtJudgeNoView();
	void ShowPlayerDoubtMenu();
	void HidePlayerDoubtMenu();

	GameManager m_gameManager;
	PlayerHandView m_playerHandView; // プレイヤーの手札を表示するクラス
	DiscardView m_discardView; // 捨て札を表示するクラス
	GameLog m_gameLog; // ゲームのログを表示するクラス
	BGMmanager m_bgmManager; // BGMを管理するクラス

	SpriteView m_bgSpriteView; // 背景スプライトを表示するクラス
	SpriteView m_markerView; // マーカーのスプライトを表示するクラス（SpriteViewを利用）
	SpriteView m_cardCountBGSpriteView[4]; // カード枚数表示の背景スプライトを表示するクラス
	SpriteView m_checkerView[4]; // チェッカーのスプライトを表示するクラス
	TextView m_playerNameTextView[4]; // プレイヤー名を表示するテキストビュー
	TextView m_cardCountTextView[4]; // カード枚数を表示するテキストビュー
	TextView m_turnPlayerView; // ターンのプレイヤーを表示するテキストビュー
	SpriteView m_doubtJudgeNoBGSpriteView; // ダウト判定のカード番号を表示するクラス
	TextView m_doubtJudgeNoTextView; // ダウト判定のカード番号を表示するテキストビュー
	TextView m_doubtJudgeNoGuideTextView; // ダウト判定のカード番号のガイドテキストビュー
	SpriteView m_winnerBGSpriteView; // 勝者表示の背景スプライトを表示するクラス
	TextView m_winnerTextView; // 勝者を表示するテキストビュー
	TextView m_toTitleTextView; // タイトルへ戻るテキストビュー
	TextView m_playerTurnGuideTextView; // プレイヤーのターンの案内を表示するテキストビュー
	TextView m_playerDoubtMenuTextView[3]; // プレイヤーのダウトメニューを表示するテキストビュー
	TextView m_gamelogTextView[10]; // ゲームログを表示するテキストビュー


	int m_maxCardsOnScreen = 25; // 画面上に表示する最大のカード枚数

	int m_playerCount; // プレイヤーの人数
	int m_myPlayerID; // 自分のプレイヤーID
	int m_turnPlayerID; // 現在のプレイヤーID
	int m_doubtPlayerID; // ダウトを行うプレイヤーのID
	int m_winnerID; // 勝者のプレイヤーID
	int m_doubtJudgeNo; // ダウト判定のカード番号
	int m_selectingCardIndex; // 選択中のカードのインデックス
	int m_selectedCardIndex[4]; // 選択されたカードのインデックス
	int m_selectedCardCount; // 選択されたカードの枚数
	int m_prevDiscardCount; // 前回の捨て札の枚数
	int m_prevPlayerHands; // 前フレームのプレイヤーの手札の枚数
	bool m_isDiscardTurn; // 捨て札のターンかどうか
	bool m_isInputed; // 入力がされたかどうか
	bool m_isPlayedAudio; // オーディオが再生されたかどうか

	float m_stickDeadZone = 0.2f; // スティックのデッドゾーン
};
