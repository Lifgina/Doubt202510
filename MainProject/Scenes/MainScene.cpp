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
	gameManager_.Load();
	playerHandView_.Load();
	m_bgSpriteView.Load("BG.png", -100); // 背景スプライトのロード
	m_markerView.Load("Marker.png", 0); // マーカースプライトのロード (Marker.png を使用)
	winnerView_.Load(); 
	playerDoubtView_.Load(); 
	doubtJudgeNoView_.Load(); 
	bgmManager_.Load(); // BGMを管理するクラスのロード
	gameLog_.Load(); // ゲームのログを表示するクラスのロード
	playerTurnView_.Load(); // プレイヤーのターンの案内を表示するクラスのロード
	turnPlayerView_.Load(); // 現在の手番のプレイヤーを表示するクラスのロード
	for (int i = 0; i < 4; i++) {
		checkerView_[i].Load(); 
	}
	for  (int i = 0; i < 4; i++) {
		cardCountView_[i].Load(); // カードの枚数を表示するクラスのロード
	}
	discardView_.Load(); // 捨て札を表示するクラスのロード
	

	Scene::Load();
}

// initialize a variables.
void MainScene::Initialize()
{
	myPlayerID_ = 0; // 自分のプレイヤーIDを設定
	playerCount_ = 4; // プレイヤーの人数を設定
	isPlayedAudio_ = false; // オーディオが再生されたかどうかを初期化
	gameManager_.SetMyPlayerID(myPlayerID_); // 自分のプレイヤーIDを設定
	gameManager_.SetPlayerCount(playerCount_); // プレイヤーの人数を設定
	gameManager_.Initialize();
	playerHandView_.UpdatePlayerHands(gameManager_.GetPlayerData(myPlayerID_)); // 自分の手札を更新
	m_bgSpriteView.Initialize(Math::Vector2(1280.0f,720.0f),Math::Vector2(1280.0f,720.0f),Math::Vector2(0.0f, 0.0f)); // 背景スプライトの初期化
	m_markerView.Initialize(Math::Vector2(25.0f, 25.0f),Math::Vector2(50.0f,50.0f),Math::Vector2(-1000.0f, 0.0f));
	doubtJudgeNoView_.Initialize(); 
	turnPlayerView_.Initialize(); // 現在の手番のプレイヤーを表示するクラスの初期化
	playerTurnView_.Initialize(); // プレイヤーのターンの案内を表示するクラスの初期化
	discardView_.Initialize(playerCount_, myPlayerID_); // 捨て札を表示するクラスの初期化
	cardCountView_[0].Initialize(Math::Vector2(800.0f,380.0f)); 
	cardCountView_[1].Initialize(Math::Vector2(10.0, 150.0f));
	cardCountView_[2].Initialize(Math::Vector2(400.0f, 10.0f));
	cardCountView_[3].Initialize(Math::Vector2(1170.0f, 150.0f));
	bgmManager_.PlayBGMFromTop(1); // BGMを再生
	for (int i = 0; i < playerCount_; i++) {
		cardCountView_[i].SetPlayerID(i); // プレイヤーのIDを設定
	}
	MyPlayerCardSelectReset();
}

// releasing resources required for termination.
void MainScene::Terminate()
{

}

// updates the scene.
void MainScene::Update(float deltaTime)
{
	static int prevTurnPlayerID = -1;
	gameManager_.Update();
	MonitorGameManager();
	MonitorDiscard();
	turnPlayerView_.UpdateTurnPlayerView(turnPlayerID_);
	for (int i = 0; i < 4; i++) {
		cardCountView_[i].UpdateCardcount(gameManager_.GetPlayerData(i).GetPlayerHands());
	}
	doubtJudgeNoView_.UpdateDoubtJudgeNo(doubtJudgeNo_);

	// ★ ダウト/スルー宣言ログ（宣言者IDを正しく渡す）
	auto lastDoubtAction = gameManager_.GetLastDoubtAction();
	if (lastDoubtAction.has_value()) {
		int playerID = lastDoubtAction->first;
		bool isDoubt = lastDoubtAction->second;
		gameLog_.DoubtLog(playerID, isDoubt);
		gameManager_.ResetLastDoubtAction();
	}

	// ★ PenaltyLogの出力
	if (gameManager_.IsDoubtResultAvailable()) {
		bool doubtCorrect = gameManager_.GetDoubtResult();
		int doubtPlayerID = gameManager_.GetLastDoubtPlayerID();
		if (doubtPlayerID != -1) {
			gameLog_.PenaltyLog(doubtPlayerID, doubtCorrect);
			gameManager_.ResetLastDoubtPlayerID();
		}
		gameManager_.ResetDoubtResult();
	}

	if (winnerID_ != -1) {
		winnerView_.ShowWinner(winnerID_);
		if (winnerID_ == myPlayerID_) {
			if (!isPlayedAudio_) {
				bgmManager_.PlayBGMFromTop(2); // 勝利した場合、勝利BGMを再生
				isPlayedAudio_ = true; // オーディオが再生されたフラグを立てる
			}	
		}
		else {
			if (!isPlayedAudio_) {

				isPlayedAudio_ = true; // オーディオが再生されたフラグを立てる
			}	
		}
		if (InputSystem.Keyboard.wasPressedThisFrame.Enter) {
			SceneManager.SetNextScene(NextScene::TitleScene, 2.0f, Color(0, 0, 0));
		}
		return;
	}
	if (isDiscardTurn_ && (turnPlayerID_ == myPlayerID_)) {
		if (prevTurnPlayerID != turnPlayerID_) {
			MyPlayerCardSelectReset();
		}
		playerTurnView_.ShowPlayerTurnUI();
		MyPlayerCardSelect();
	}
	else if (doubtPlayerID_ == myPlayerID_) {
		MyDoubtSelect();
	}
	else {
		playerTurnView_.HidePlayerTurnUI();
	}
	prevTurnPlayerID = turnPlayerID_;
	Scene::Update(deltaTime);
}



void MainScene::MonitorGameManager()
{
	//前フレームのプレイヤーの手札枚数と現在のプレイヤーの手札枚数を比較して、変化があった場合に手札を更新
	if (prevPlayerHands_ != gameManager_.GetPlayerData(myPlayerID_).GetPlayerHands()) {
		playerHandView_.UpdatePlayerHands(gameManager_.GetPlayerData(myPlayerID_)); // 自分の手札を更新
		prevPlayerHands_ = gameManager_.GetPlayerData(myPlayerID_).GetPlayerHands(); // 前フレームの手札枚数を更新
	}
	isDiscardTurn_ = gameManager_.GetIsDiscardTurn(); // 捨て札のターンかどうかを取得
	isInputed_ = gameManager_.GetIsInputed(); // 入力がされたかどうかを取得
	turnPlayerID_ = gameManager_.GetTurnPlayerID(); // 現在の手番のプレイヤーIDを取得
	doubtPlayerID_ = gameManager_.GetDoubtPlayerID(); // ダウトを行うプレイヤーのIDを取得
	doubtJudgeNo_ = gameManager_.GetDoubtJudgeNo(); // ダウト判定のカード番号を取得
	winnerID_ = gameManager_.GetWinnerPlayerID(); // 勝者のプレイヤーIDを取得
}

void MainScene::MonitorDiscard() {
	if (prevDiscardCount_ != gameManager_.GetDiscardCount()) {
		if (gameManager_.GetDiscardCount() == 0)
		{
			discardView_.ResetDiscard(); // 捨て札をクリア
		}
		else
		{
			int discardNum = gameManager_.GetDiscardCount() - prevDiscardCount_;
			discardView_.Discard(turnPlayerID_, discardNum); // 捨て札を更新
			gameLog_.DiscardLog(turnPlayerID_, discardNum); // ★ログ出力
		}
	}
	prevDiscardCount_ = gameManager_.GetDiscardCount(); // 前回の捨て札の枚数を更新
}


void MainScene::MyPlayerCardSelect()
{
	int playerHands = gameManager_.GetPlayerData(turnPlayerID_).GetPlayerHands(); // 自分の手札の枚数を取得
	HE::Gamepad gamepad_ = InputSystem.Gamepad.ElementAtOrDefault(0);
    selectingCardIndex_ ;
	auto cardPos = playerHandView_.GetCardPosition(selectingCardIndex_);
	m_markerView.UpdateSpritePos(Math::Vector2(cardPos.x + 75.0f/8, cardPos.y - 25.0f)); // マーカーの位置を更新


	if (gamepad_.leftStick.x > stickDeadZone_ || InputSystem.Keyboard.wasPressedThisFrame.Right) {
		
		selectingCardIndex_ += 1; // 右に移動
		auto cardPosR = playerHandView_.GetCardPosition(selectingCardIndex_);
		m_markerView.UpdateSpritePos(Math::Vector2(cardPosR.x + 75.0f/8, cardPosR.y - 25.0f)); // マーカーの位置を更新
	}
	else if (gamepad_.leftStick.x < -stickDeadZone_ || InputSystem.Keyboard.wasPressedThisFrame.Left) {
	
		selectingCardIndex_ -= 1; // 左に移動
		auto cardPosL = playerHandView_.GetCardPosition(selectingCardIndex_);
		m_markerView.UpdateSpritePos(Math::Vector2(cardPosL.x + 75.0f/8, cardPosL.y - 25.0f)); // マーカーの位置を更新
	}
	if (selectingCardIndex_ < 0)
	{
		selectingCardIndex_ = playerHands - 1; // 左端を超えたら右端に戻る
		auto cardPosWrap = playerHandView_.GetCardPosition(selectingCardIndex_);
		m_markerView.UpdateSpritePos(Math::Vector2(cardPosWrap.x + 75.0f/8, cardPosWrap.y - 25.0f)); // マーカーの位置を更新
	}
	else if (selectingCardIndex_ >= playerHands)
	{
		selectingCardIndex_ = 0; // 右端を超えたら左端に戻る
		auto cardPosWrap2 = playerHandView_.GetCardPosition(selectingCardIndex_);
		m_markerView.UpdateSpritePos(Math::Vector2(cardPosWrap2.x + 75.0f/8, cardPosWrap2.y - 25.0f)); // マーカーの位置を更新
	}

	if (gamepad_.wasPressedThisFrame.Button2 || InputSystem.Keyboard.wasPressedThisFrame.Space) {

		//対応するボタンが押されたとき、selectedCardIndexの数値とselectedCardIndexの値を比較
		bool isAlreadySelected = false;
		for (int i = 0; i < selectedCardCount_; i++) {
			if (selectedCardIndex_[i] == selectingCardIndex_) {
				isAlreadySelected = true; // 既に選択されているカードである
				break;
			}
		}
		// 既に選択されているカードでない場合、選択されたカードのインデックスを保存

		if (!isAlreadySelected && selectedCardCount_ < 4) {
			checkerView_[selectedCardCount_].UpdateChecker(playerHandView_.GetCardPosition(selectingCardIndex_)); // チェッカーの位置を更新
			selectedCardIndex_[selectedCardCount_] = selectingCardIndex_; // 選択されたカードのインデックスを保存
			selectedCardCount_++; // 選択されたカードの枚数を増やす
		}
		else if (isAlreadySelected) {
			// 既に選択されているカードであれば、選択を解除
			for (int i = 0; i < selectedCardCount_; i++) {
				if (selectedCardIndex_[i] == selectingCardIndex_) {
					// 最後のチェッカーを現在の位置に移動
					if (i != selectedCardCount_ - 1) {
						checkerView_[i].UpdateChecker(playerHandView_.GetCardPosition(selectedCardIndex_[selectedCardCount_ - 1]));
					}
					checkerView_[selectedCardCount_ - 1].CheckerDelete(); // 最後のチェッカーを削除

					// 配列も最後の要素で上書き
					selectedCardIndex_[i] = selectedCardIndex_[selectedCardCount_ - 1];
					selectedCardCount_--;
					break;
				}
			}
		}
	
	}
	if (selectedCardCount_ >= 1) {
	if (gamepad_.wasPressedThisFrame.Button1 || InputSystem.Keyboard.wasPressedThisFrame.Enter)
	{
		playerHandView_.UpdatePlayerHands(gameManager_.GetPlayerData(myPlayerID_)); // 自分の手札を更新
		for (int i = 0; i < 4; i++) {
			checkerView_[i].CheckerDelete(); // チェッカーを削除
		}
		gameManager_.SetPlayerDiscard(selectedCardIndex_); // 選択されたカードを捨て札に設定
	}
	}


}

void MainScene::MyPlayerCardSelectReset()
{
	selectingCardIndex_ = 0; // 選択中のカードのインデックスを初期化
	selectedCardCount_ = 0; // 選択されたカードの枚数を初期化
	for (int i = 0; i < 4; i++) {
		selectedCardIndex_[i] = -1; // 選択されたカードのインデックスを初期化
	}
}

void MainScene::MyDoubtSelect()
{
	playerDoubtView_.ShowDoubtMenu(); // ダウトメニューを表示
	HE::Gamepad gamepad_ = InputSystem.Gamepad.ElementAtOrDefault(0);
	if (gamepad_.leftStick.y >= 0.3 || InputSystem.Keyboard.wasPressedThisFrame.Up) {

		playerDoubtView_.HideDoubtMenu(); // ダウトメニューを非表示
		gameManager_.SetPlayerDoDoubt(true); // ダウトを行う
	}
	else if (gamepad_.leftStick.y <= -0.3 || InputSystem.Keyboard.wasPressedThisFrame.Down) {

		playerDoubtView_.HideDoubtMenu(); // ダウトメニューを非表示
		gameManager_.SetPlayerDoDoubt(false); // ダウトを行わない
	}
}

