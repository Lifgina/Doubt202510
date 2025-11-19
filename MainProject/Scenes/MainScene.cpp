//
// MainScene.cpp
//

#include "MainScene.h"

using namespace HE;

// initialize member variables.
MainScene::MainScene()
{

}

// rearrange UI to fit the size.
void MainScene::ResizeLayout()
{
	Scene::ResizeLayout();

}

// load resources.
void MainScene::Load()
{
	m_gameManager.Load();
	m_playerHandView.Load();
	m_bgSpriteView.Load("BG.png", -100); // 背景スプライトのロード
	m_markerView.Load("Marker.png", 0); // マーカースプライトのロード (Marker.png を使用)
	m_winnerBGSpriteView.Load("WinnerBack.png", 1100); // 勝者表示の背景スプライトのロード
	m_winnerTextView.Load(1200, "Fonts/meiryob004.ttf"); // 勝者を表示するテキストビューのロード
	m_toTitleTextView.Load(1200, "Fonts/meiryob004.ttf"); // タイトルへ戻るテキストビューのロード
	m_doubtJudgeNoBGSpriteView.Load("CardBack2.png", 0); // ダウト判定のカード番号を表示するクラスのロード
	m_doubtJudgeNoTextView.Load(1000, "Fonts/meiryob004.ttf"); // ダウト判定のカード番号を表示するテキストビューのロード
	m_doubtJudgeNoGuideTextView.Load(1000, "Fonts/meiryob004.ttf"); // ダウト判定のカード番号のガイドテキストビューのロード
	m_bgmManager.Load(); // BGMを管理するクラスのロード
	m_playerTurnGuideTextView.Load(1000, "Fonts/meiryob004.ttf"); // プレイヤーのターンの案内を表示するテキストビューのロード
	m_turnPlayerView.Load(1000, "Fonts/meiryob004.ttf"); // ターンのプレイヤーを表示するテキストビューのロード
	for (int i = 0; i < 4; i++) {
		m_checkerView[i].Load("Checker.png",0); // チェッカー表示を管理する CheckerView 配列のロード
	}
	for  (int i = 0; i < 4; i++) {
		m_cardCountBGSpriteView[i].Load("CardBack2.png", 0); // カード枚数表示の背景スプライトのロード
		m_cardCountTextView[i].Load(1000, "Fonts/meiryob004.ttf"); // カード枚数を表示するテキストビューのロード
		m_playerNameTextView[i].Load(1000, "Fonts/meiryob004.ttf"); // プレイヤー名を表示するテキストビューのロード

	}
	for (int i = 0; i < 3; i++) {
		m_playerDoubtMenuTextView[i].Load(1000, "Fonts/meiryob004.ttf"); // プレイヤーのダウトメニューを表示するテキストビューのロード
	}
	for (int i = 0; i < 10; i++) {
		m_gamelogTextView[i].Load(1000, "Fonts/meiryob004.ttf"); // ゲームログを表示するテキストビューのロード
	}
	m_gameLog.SetViews(m_gamelogTextView, 10);
	m_discardView.Load(); // 捨て札を表示するクラスのロード
	

	Scene::Load();
}

// initialize a variables.
void MainScene::Initialize()
{
	m_myPlayerID = 0; // 自分のプレイヤーIDを設定
	m_playerCount = 4; // プレイヤーの人数を設定
	m_isPlayedAudio = false; // オーディオが再生されたかどうかを初期化
	m_gameManager.SetMyPlayerID(m_myPlayerID); // 自分のプレイヤーIDを設定
	m_gameManager.SetPlayerCount(m_playerCount); // プレイヤーの人数を設定
	m_gameManager.Initialize();
	m_playerHandView.UpdatePlayerHands(m_gameManager.GetPlayerData(m_myPlayerID)); // 自分の手札を更新

	// 背景およびマーカー初期化
	m_bgSpriteView.Initialize(Math::Vector2(1280.0f,720.0f), Math::Vector2(1280.0f,720.0f), Math::Vector2(0.0f, 0.0f)); // 背景スプライトの初期化
	m_markerView.Initialize(Math::Vector2(25.0f, 25.0f), Math::Vector2(50.0f,50.0f), Math::Vector2(-1000.0f, 0.0f));
	m_doubtJudgeNoBGSpriteView.Initialize(Math::Vector2(75.0f, 100.0f), Math::Vector2(1250.0f, 1935.0f), Math::Vector2(800.0f, 200.0f)); // ダウト判定のカード番号を表示するクラスの初期化
	m_doubtJudgeNoTextView.Initialize(Math::Vector2(800.0f + 75.0f / 2 - 9.0f, 200.0f + 30.0f), 0, 0, 0, L"", 36); // ダウト判定のカード番号を表示するテキストビューの初期化
	m_doubtJudgeNoGuideTextView.Initialize(Math::Vector2(815.0f, 300.0f), 0, 0, 0, L"Next", 24); // ダウト判定のカード番号のガイドテキストビューの初期化
	m_turnPlayerView.Initialize(Math::Vector2(900.0f, 50.0f), 0, 0, 0, L"", 36); // ターンのプレイヤーを表示するテキストビューの初期化
	m_discardView.Initialize(m_playerCount, m_myPlayerID); // 捨て札を表示するクラスの初期化
	CardCountViewInitialize(); // カード枚数表示の初期化
	m_winnerBGSpriteView.Initialize(Math::Vector2(800.0f, 450.0f), Math::Vector2(800.0f, 450.0f), Math::Vector2(-1000.0f,-1000.0f)); // 勝者表示の背景スプライトの初期化
	m_winnerTextView.Initialize(Math::Vector2(400.0f, 300.0f), 0, 0, 0, L"", 72); // 勝者を表示するテキストビューの初期化
	m_toTitleTextView.Initialize(Math::Vector2(420.0f, 500.0f), 0, 0, 0, L"", 48); // タイトルへ戻るテキストビューの初期化
	m_playerTurnGuideTextView.Initialize(Math::Vector2(430.0f, 400.0f), 0, 0, 0, L"", 36); // プレイヤーのターンの案内を表示するテキストビューの初期化
	for (int i = 0; i < 3; i++) {
		m_playerDoubtMenuTextView[i].Initialize(Math::Vector2(600.0f, 380.0f + i * 40.0f), 0, 0, 0, L"", 36); // プレイヤーのダウトメニューを表示するテキストビューの初期化
	}
	for (int i = 0; i < 10; i++) {
		m_gamelogTextView[i].Initialize(Math::Vector2(1000.0f, 275.0f + i * 20.0f), 0, 0, 0, L"", 20); // ゲームログを表示するテキストビューの初期化
	}

	// BGM とチェッカー初期化
	m_bgmManager.PlayBGMFromTop(1); // BGMを再生
	for (int i = 0; i < 4; i++) {
		m_checkerView[i].Initialize(Math::Vector2(25.0f, 25.0f), Math::Vector2(50.0f, 50.0f), Math::Vector2(-1000.0f, 0.0f)); // チェッカー表示を管理する CheckerView 配列の初期化
	}
	MyPlayerCardSelectReset();
}

void MainScene::CardCountViewInitialize()
{
	// プレイヤー毎の UI をループで初期化（重複コードを削減）
	const HE::Math::Vector2 cardBGSize(75.0f, 100.0f);
	const HE::Math::Vector2 cardBGRect(1250.0f, 1935.0f);
	const std::array<HE::Math::Vector2, 4> cardBGPositions = {
		HE::Math::Vector2(800.0f, 380.0f),
		HE::Math::Vector2(10.0f, 150.0f),
		HE::Math::Vector2(400.0f, 10.0f),
		HE::Math::Vector2(1170.0f, 150.0f)
	};
	const std::array<std::wstring, 4> playerNames = {
		L"プレイヤー1", L"プレイヤー2", L"プレイヤー3", L"プレイヤー4"
	};
	const float nameOffsetX = -5.0f;
	const float nameOffsetY = 100.0f;
	const float cardCountTextOffsetX = (cardBGSize.x / 2.0f) - 18.0f;
	const float cardCountTextOffsetY = (cardBGSize.y / 2.0f) - 18.0f;

	for (int i = 0; i < m_playerCount && i < 4; ++i) {
		// 背景スプライト初期化
		m_cardCountBGSpriteView[i].Initialize(cardBGSize, cardBGRect, cardBGPositions[i]);

		// プレイヤー名テキスト位置（背景位置を基準にオフセット）
		HE::Math::Vector2 namePos(cardBGPositions[i].x + nameOffsetX, cardBGPositions[i].y + nameOffsetY);
		m_playerNameTextView[i].Initialize(namePos, 0.0f, 0.0f, 0.0f, playerNames[i], 24);

		// カード枚数テキスト位置を背景中心付近に配置
		HE::Math::Vector2 countPos(cardBGPositions[i].x + cardCountTextOffsetX, cardBGPositions[i].y + cardCountTextOffsetY);
		m_cardCountTextView[i].Initialize(countPos, 0.0f, 0.0f, 0.0f, L"0", 36);
	}
}

// releasing resources required for termination.
void MainScene::Terminate()
{

}

// updates the scene.
void MainScene::Update(float deltaTime)
{
	static int prevTurnPlayerID = -1;
	m_gameManager.Update();
	MonitorGameManager();
	MonitorDiscard();
	m_turnPlayerView.UpdateText(L"プレイヤー"+std::to_wstring(m_turnPlayerID+1)+L"の番");
	for (int i = 0; i < 4; i++) {
		m_cardCountTextView[i].UpdateText(std::to_wstring(m_gameManager.GetPlayerData(i).GetPlayerHands())); // 各プレイヤーのカード枚数を更新
	}
	UpdateDoubtJudgeNoView();

	// ★ ダウト/スルー宣言ログ（宣言者IDを正しく渡す）
	auto lastDoubtAction = m_gameManager.GetLastDoubtAction();
	if (lastDoubtAction.has_value()) {
		int playerID = lastDoubtAction->first;
		bool isDoubt = lastDoubtAction->second;
		m_gameLog.DoubtLog(playerID, isDoubt);
		m_gameManager.ResetLastDoubtAction();
	}

	// ★ PenaltyLogの出力
	if (m_gameManager.IsDoubtResultAvailable()) {
		bool doubtCorrect = m_gameManager.GetDoubtResult();
		int doubtPlayerID = m_gameManager.GetLastDoubtPlayerID();
		if (doubtPlayerID != -1) {
			m_gameLog.PenaltyLog(doubtPlayerID, doubtCorrect);
			m_gameManager.ResetLastDoubtPlayerID();
		}
		m_gameManager.ResetDoubtResult();
	}

	if (m_winnerID != -1) {
		m_winnerBGSpriteView.UpdateSpritePos(Math::Vector2(240.0f, 360.0 - 225.0f)); // 勝者表示の背景スプライトを中央に移動
		m_winnerTextView.UpdateText(L"プレイヤー" + std::to_wstring(m_winnerID + 1) + L"の勝利！");
		m_toTitleTextView.UpdateText(L"決定ボタンでタイトルへ戻る");
		if (m_winnerID == m_myPlayerID) {
			if (!m_isPlayedAudio) {
				m_bgmManager.PlayBGMFromTop(2); // 勝利した場合、勝利BGMを再生
				m_isPlayedAudio = true; // オーディオが再生されたフラグを立てる
			}
		}
		else {
			if (!m_isPlayedAudio) {

				m_isPlayedAudio = true; // オーディオが再生されたフラグを立てる
			}
		}
		if (InputSystem.Keyboard.wasPressedThisFrame.Enter) {
			SceneManager.SetNextScene(NextScene::TitleScene, 2.0f, Color(0, 0, 0));
		}
		return;
	}
	if (m_isDiscardTurn && (m_turnPlayerID == m_myPlayerID)) {
		if (prevTurnPlayerID != m_turnPlayerID) {
			MyPlayerCardSelectReset();
		}
		m_playerTurnGuideTextView.UpdateText(L"カードを4枚まで選んで出そう！");
		MyPlayerCardSelect();
	}
	else if (m_doubtPlayerID == m_myPlayerID) {
		MyDoubtSelect();
	}
	else {
		m_playerTurnGuideTextView.UpdateText(L"");
	}
	prevTurnPlayerID = m_turnPlayerID;
	Scene::Update(deltaTime);
}



void MainScene::MonitorGameManager()
{
	//前フレームのプレイヤーの手札枚数と現在のプレイヤーの手札枚数を比較して、変化があった場合に手札を更新
	if (m_prevPlayerHands != m_gameManager.GetPlayerData(m_myPlayerID).GetPlayerHands()) {
		m_playerHandView.UpdatePlayerHands(m_gameManager.GetPlayerData(m_myPlayerID)); // 自分の手札を更新
		m_prevPlayerHands = m_gameManager.GetPlayerData(m_myPlayerID).GetPlayerHands(); // 前フレームの手札枚数を更新
	}
	m_isDiscardTurn = m_gameManager.GetIsDiscardTurn(); // 捨て札のターンかどうかを取得
	m_isInputed = m_gameManager.GetIsInputed(); // 入力がされたかどうかを取得
	m_turnPlayerID = m_gameManager.GetTurnPlayerID(); // 現在の手番のプレイヤーIDを取得
	m_doubtPlayerID = m_gameManager.GetDoubtPlayerID(); // ダウトを行うプレイヤーのIDを取得
	m_doubtJudgeNo = m_gameManager.GetDoubtJudgeNo(); // ダウト判定のカード番号を取得
	m_winnerID = m_gameManager.GetWinnerPlayerID(); // 勝者のプレイヤーIDを取得
}

void MainScene::MonitorDiscard() {
	if (m_prevDiscardCount != m_gameManager.GetDiscardCount()) {
		if (m_gameManager.GetDiscardCount() == 0)
		{
			m_discardView.ResetDiscard(); // 捨て札をクリア
		}
		else
		{
			int discardNum = m_gameManager.GetDiscardCount() - m_prevDiscardCount;
			m_discardView.Discard(m_turnPlayerID, discardNum); // 捨て札を更新
			m_gameLog.DiscardLog(m_turnPlayerID, discardNum); // ★ログ出力
		}
	}
	m_prevDiscardCount = m_gameManager.GetDiscardCount(); // 前回の捨て札の枚数を更新
}


void MainScene::MyPlayerCardSelect()
{
	int playerHands = m_gameManager.GetPlayerData(m_turnPlayerID).GetPlayerHands(); // 自分の手札の枚数を取得
	HE::Gamepad gamepad_ = InputSystem.Gamepad.ElementAtOrDefault(0);
    m_selectingCardIndex ;
	auto cardPos = m_playerHandView.GetCardPosition(m_selectingCardIndex);
	m_markerView.UpdateSpritePos(Math::Vector2(cardPos.x + 75.0f/8, cardPos.y - 25.0f)); // マーカーの位置を更新


	if (gamepad_.leftStick.x > m_stickDeadZone || InputSystem.Keyboard.wasPressedThisFrame.Right) {
		
		m_selectingCardIndex += 1; // 右に移動
		auto cardPosR = m_playerHandView.GetCardPosition(m_selectingCardIndex);
		m_markerView.UpdateSpritePos(Math::Vector2(cardPosR.x + 75.0f/8, cardPosR.y - 25.0f)); // マーカーの位置を更新
	}
	else if (gamepad_.leftStick.x < -m_stickDeadZone || InputSystem.Keyboard.wasPressedThisFrame.Left) {
	
		m_selectingCardIndex -= 1; // 左に移動
		auto cardPosL = m_playerHandView.GetCardPosition(m_selectingCardIndex);
		m_markerView.UpdateSpritePos(Math::Vector2(cardPosL.x + 75.0f/8, cardPosL.y - 25.0f)); // マーカーの位置を更新
	}
	if (m_selectingCardIndex < 0)
	{
		m_selectingCardIndex = playerHands - 1; // 左端を超えたら右端に戻る
		auto cardPosWrap = m_playerHandView.GetCardPosition(m_selectingCardIndex);
		m_markerView.UpdateSpritePos(Math::Vector2(cardPosWrap.x + 75.0f/8, cardPosWrap.y - 25.0f)); // マーカーの位置を更新
	}
	else if (m_selectingCardIndex >= playerHands)
	{
		m_selectingCardIndex = 0; // 右端を超えたら左端に戻る
		auto cardPosWrap2 = m_playerHandView.GetCardPosition(m_selectingCardIndex);
		m_markerView.UpdateSpritePos(Math::Vector2(cardPosWrap2.x + 75.0f/8, cardPosWrap2.y - 25.0f)); // マーカーの位置を更新
	}

	if (gamepad_.wasPressedThisFrame.Button2 || InputSystem.Keyboard.wasPressedThisFrame.Space) {

		//対応するボタンが押されたとき、m_selectedCardIndexの数値とm_selectedCardIndexの値を比較
		bool isAlreadySelected = false;
		for (int i = 0; i < m_selectedCardCount; i++) {
			if (m_selectedCardIndex[i] == m_selectingCardIndex) {
				isAlreadySelected = true; // 既に選択されているカードである
				break;
			}
		}
		// 既に選択されているカードでない場合、選択されたカードのインデックスを保存

		if (!isAlreadySelected && m_selectedCardCount < 4) {
			m_checkerView[m_selectedCardCount].UpdateSpritePos(m_playerHandView.GetCardPosition(m_selectingCardIndex)); // チェッカーの位置を更新
			m_selectedCardIndex[m_selectedCardCount] = m_selectingCardIndex; // 選択されたカードのインデックスを保存
			m_selectedCardCount++; // 選択されたカードの枚数を増やす
		}
		else if (isAlreadySelected) {
			// 既に選択されているカードであれば、選択を解除
			for (int i = 0; i < m_selectedCardCount; i++) {
				if (m_selectedCardIndex[i] == m_selectingCardIndex) {
					// 最後のチェッカーを現在の位置に移動
					if (i != m_selectedCardCount - 1) {
						m_checkerView[i].UpdateSpritePos(m_playerHandView.GetCardPosition(m_selectedCardIndex[m_selectedCardCount - 1]));
					}
					m_checkerView[m_selectedCardCount - 1].UpdateSpritePos(Math::Vector2(-1000.0f, 0.0f)); // チェッカーを画面外に移動

					// 配列も最後の要素で上書き
					m_selectedCardIndex[i] = m_selectedCardIndex[m_selectedCardCount - 1];
					m_selectedCardCount--;
					break;
				}
			}
		}
	
	}
	if (m_selectedCardCount >= 1) {
	if (gamepad_.wasPressedThisFrame.Button1 || InputSystem.Keyboard.wasPressedThisFrame.Enter)
	{
		m_playerHandView.UpdatePlayerHands(m_gameManager.GetPlayerData(m_myPlayerID)); // 自分の手札を更新
		for (int i = 0; i < 4; i++) {
			m_checkerView[i].UpdateSpritePos(Math::Vector2(-1000.0f, 0.0f)); // チェッカーを画面外に移動
		}
		m_gameManager.SetPlayerDiscard(m_selectedCardIndex); // 選択されたカードを捨て札に設定
	}
	}


}

void MainScene::MyPlayerCardSelectReset()
{
	m_selectingCardIndex = 0; // 選択中のカードのインデックスを初期化
	m_selectedCardCount = 0; // 選択されたカードの枚数を初期化
	for (int i = 0; i < 4; i++) {
		m_selectedCardIndex[i] = -1; // 選択されたカードのインデックスを初期化
	}
}

void MainScene::MyDoubtSelect()
{
	ShowPlayerDoubtMenu();
	HE::Gamepad gamepad_ = InputSystem.Gamepad.ElementAtOrDefault(0);
	if (gamepad_.leftStick.y >= 0.3 || InputSystem.Keyboard.wasPressedThisFrame.Up) {

		HidePlayerDoubtMenu(); // ダウトメニューを非表示
		m_gameManager.SetPlayerDoDoubt(true); // ダウトを行う
	}
	else if (gamepad_.leftStick.y <= -0.3 || InputSystem.Keyboard.wasPressedThisFrame.Down) {

		HidePlayerDoubtMenu(); // ダウトメニューを非表示
		m_gameManager.SetPlayerDoDoubt(false); // ダウトを行わない
	}
}

void MainScene::UpdateDoubtJudgeNoView()
{

	if (2 <= m_doubtJudgeNo && m_doubtJudgeNo <= 10)
	{
		m_doubtJudgeNoTextView.UpdateText(std::to_wstring(m_doubtJudgeNo)); // ダウト判定のカード番号を表示
	}
	else if (m_doubtJudgeNo == 11)
	{
		m_doubtJudgeNoTextView.UpdateText(L"J"); // ジャックの場合
	}
	else if (m_doubtJudgeNo == 12)
	{
		m_doubtJudgeNoTextView.UpdateText(L"Q"); // クイーンの場合
	}
	else if (m_doubtJudgeNo == 13)
	{
		m_doubtJudgeNoTextView.UpdateText(L"K"); // キングの場合
	}
	else if (m_doubtJudgeNo == 1)
	{
		m_doubtJudgeNoTextView.UpdateText(L"A"); // エースの場合
	}
	else
	{
		m_doubtJudgeNoTextView.UpdateText(L""); // 無効な番号の場合は空にする
	}
}

void MainScene::ShowPlayerDoubtMenu()
{
	m_playerDoubtMenuTextView[0].UpdateText(L"ダウトする?");
	m_playerDoubtMenuTextView[1].UpdateText(L"↑: ダウト");
	m_playerDoubtMenuTextView[2].UpdateText(L"↓: スルー");
}

void MainScene::HidePlayerDoubtMenu()
{
	for (int i = 0; i < 3; i++) {
		m_playerDoubtMenuTextView[i].UpdateText(L"");
	}
}
