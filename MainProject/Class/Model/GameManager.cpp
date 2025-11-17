#include "GameManager.h"
#include <random>

using namespace HE;

void GameManager::Load() {}

void GameManager::Initialize()
{
    myPlayerID_ = 0;
    discardPlayerID_ = -1;
    doubtplayerID_ = -1;
    isDoubt_ = false;
    for (int i = 0; i < 4; i++) {
        playerDiscardIndex_[i] = -1;
    }
    turnPlayerID_ = myPlayerID_;
    cardDistributer_.DistributeCards(player_, playerCount_);
    doubtJudgeNo_ = 1;
    winnerPlayerID_ = -1;
    isDiscardTurn_ = true;
    isInputed_ = false;
    doubtResult_.reset();
    lastDoubtAction_.reset();
}

void GameManager::Update()
{
    if (winnerPlayerID_ != -1) {
        return;
    }
    if (isDiscardTurn_) {
        DiscardTurn();
    }
    else {
        DoubtTurn();
    }
}
void GameManager::DiscardTurn()
{
    cardDiscarder_.Discard(
        player_,
        playerCount_,
        turnPlayerID_,
        myPlayerID_,
        doubtJudgeNo_,
        playerDiscardIndex_,
        isInputed_,
        discardManager_,
        randomCardSelect_,
        isInputed_,
        isDiscardTurn_
    );
}

void GameManager::SetPlayerDiscard(int cardIndex[4])
{
    for (int i = 0; i < 4; ++i) {
        playerDiscardIndex_[i] = cardIndex[i];
    }
    isInputed_ = true;
}

void GameManager::DoubtTurn()
{
    if (doubtplayerID_ == -1) {
        doubtplayerID_ = (turnPlayerID_ + 1) % playerCount_;
        isInputed_ = false;
    }

    if (doubtplayerID_ == myPlayerID_) {
        if (!isInputed_) {
            return;
        }
    }
    else if (!isInputed_) {
        int hands = player_[doubtplayerID_].GetPlayerHands();
        CardData handcards[52];
        for (int j = 0; j < hands; ++j) {
            handcards[j] = player_[doubtplayerID_].GetCard(j);
        }
        int count = 0;
        for (int j = 0; j < hands; ++j) {
            if (handcards[j].GetRank() == doubtJudgeNo_) {
                count++;
            }
        }
        float doubtProbability = 0.0f;
        if (count == 0) {
            doubtProbability = 0.05f;
        }
        else if (count == 1) {
            doubtProbability = 0.1f;
        }
        else if (count == 2) {
            doubtProbability = 0.3f;
        }
        else if (count == 3) {
            doubtProbability = 0.8f;
        }
        else {
            doubtProbability = 1.0f;
        }

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        isDoubt_ = (dist(gen) < doubtProbability);
        isInputed_ = true;

        // 追加: AI/他プレイヤーのダウト/スルー宣言を記録
        lastDoubtAction_ = std::make_pair(doubtplayerID_, isDoubt_);
    }

    if (isInputed_) {
        if (isDoubt_) {
            bool isSuccess = DoubtCheck(doubtplayerID_, turnPlayerID_);
            SetDoubtResult(isSuccess);

            // ここで直近のダウト宣言者IDを保存
            lastDoubtPlayerID_ = doubtplayerID_;

            if (isSuccess) {
                Penalty(turnPlayerID_);
            }
            else {
                Penalty(doubtplayerID_);
            }
            doubtplayerID_ = -1;
            isDoubt_ = false;
            isInputed_ = false;
            if (player_[turnPlayerID_].GetPlayerHands() == 0) {
                winnerPlayerID_ = turnPlayerID_;
                return;
            }
            turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_;
            doubtJudgeNo_ = (doubtJudgeNo_ % 13) + 1;
            isDiscardTurn_ = true;
            return;
        }
        else {
            doubtplayerID_ = (doubtplayerID_ + 1) % playerCount_;
            isInputed_ = false;
            if (doubtplayerID_ == turnPlayerID_) {
                doubtplayerID_ = -1;
                if (player_[turnPlayerID_].GetPlayerHands() == 0) {
                    winnerPlayerID_ = turnPlayerID_;
                    return;
                }
                turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_;
                doubtJudgeNo_ = (doubtJudgeNo_ % 13) + 1;
                discardManager_.ClearCurrentDiscard();
                isDiscardTurn_ = true;
            }
        }
    }
}

void GameManager::SetPlayerDoDoubt(bool isDoubt)
{
    isDoubt_ = isDoubt;
    isInputed_ = true;
    // プレイヤーのダウト/スルー宣言も記録
    lastDoubtAction_ = std::make_pair(myPlayerID_, isDoubt_);
}

bool GameManager::DoubtCheck(int doubtPlayerID, int discardPlayerID)
{
    for (int i = 0; i < 4; ++i) {
        CardData card = discardManager_.GetCurrentDisCards(i);
        if (card.GetRank() == 0) continue;
        if (card.GetRank() != doubtJudgeNo_) {
            return true;
        }
    }
    return false;
}

void GameManager::Penalty(int penaltyPlayer)
{
    std::vector<CardData> newHand;
    int handCount = player_[penaltyPlayer].GetPlayerHands();
    for (int i = 0; i < handCount; ++i) {
        newHand.push_back(player_[penaltyPlayer].GetCard(i));
    }
    for (int i = 0; i < discardManager_.GetDiscardCount(); ++i) {
        newHand.push_back(discardManager_.GetDiscard(i));
    }
    player_[penaltyPlayer].SetHand(newHand);
    discardManager_.ClearDiscard();
    discardManager_.ClearCurrentDiscard();
}
