#include "GameManager.h"
#include <random>

using namespace HE;

void GameManager::Load() {}

void GameManager::Initialize()
{
    m_myPlayerID = 0;
    m_discardPlayerID = -1;
    m_doubtPlayerID = -1;
    m_isDoubt = false;
    for (int i = 0; i < 4; i++) {
        m_playerDiscardIndex[i] = -1;
    }
    m_turnPlayerID = m_myPlayerID;
    m_cardDistributer.DistributeCards(m_player, m_playerCount);
    m_doubtJudgeNo = 1;
    m_winnerPlayerID = -1;
    m_isDiscardTurn = true;
    m_isInputed = false;
    m_doubtResult.reset();
    m_lastDoubtAction.reset();
}

void GameManager::Update()
{
    if (m_winnerPlayerID != -1) {
        return;
    }
    if (m_isDiscardTurn) {
        DiscardTurn();
    }
    else {
        DoubtTurn();
    }
}
void GameManager::DiscardTurn()
{
    m_cardDiscarder.Discard(
        m_player,
        m_playerCount,
        m_turnPlayerID,
        m_myPlayerID,
        m_doubtJudgeNo,
        m_playerDiscardIndex,
        m_isInputed,
        m_discardManager,
        m_randomCardSelect,
        m_isInputed,
        m_isDiscardTurn
    );
}

void GameManager::SetPlayerDiscard(int cardIndex[4])
{
    for (int i = 0; i < 4; ++i) {
        m_playerDiscardIndex[i] = cardIndex[i];
    }
    m_isInputed = true;
}

void GameManager::DoubtTurn()
{
    if (m_doubtPlayerID == -1) {
        m_doubtPlayerID = (m_turnPlayerID + 1) % m_playerCount;
        m_isInputed = false;
    }

    if (m_doubtPlayerID == m_myPlayerID) {
        if (!m_isInputed) {
            return;
        }
    }
    else if (!m_isInputed) {
        int hands = m_player[m_doubtPlayerID].GetPlayerHands();
        CardData handcards[52];
        for (int j = 0; j < hands; ++j) {
            handcards[j] = m_player[m_doubtPlayerID].GetCard(j);
        }
        int count = 0;
        for (int j = 0; j < hands; ++j) {
            if (handcards[j].GetRank() == m_doubtJudgeNo) {
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

        m_isDoubt = (dist(gen) < doubtProbability);
        m_isInputed = true;

        // 追加: AI/他プレイヤーのダウト/スルー宣言を記録
        m_lastDoubtAction = std::make_pair(m_doubtPlayerID, m_isDoubt);
    }

    if (m_isInputed) {
        if (m_isDoubt) {
            bool isSuccess = DoubtCheck(m_doubtPlayerID, m_turnPlayerID);
            SetDoubtResult(isSuccess);

            // ここで直近のダウト宣言者IDを保存
            m_lastDoubtPlayerID = m_doubtPlayerID;

            if (isSuccess) {
                Penalty(m_turnPlayerID);
            }
            else {
                Penalty(m_doubtPlayerID);
            }
            m_doubtPlayerID = -1;
            m_isDoubt = false;
            m_isInputed = false;
            if (m_player[m_turnPlayerID].GetPlayerHands() == 0) {
                m_winnerPlayerID = m_turnPlayerID;
                return;
            }
            m_turnPlayerID = (m_turnPlayerID + 1) % m_playerCount;
            m_doubtJudgeNo = (m_doubtJudgeNo % 13) + 1;
            m_isDiscardTurn = true;
            return;
        }
        else {
            m_doubtPlayerID = (m_doubtPlayerID + 1) % m_playerCount;
            m_isInputed = false;
            if (m_doubtPlayerID == m_turnPlayerID) {
                m_doubtPlayerID = -1;
                if (m_player[m_turnPlayerID].GetPlayerHands() == 0) {
                    m_winnerPlayerID = m_turnPlayerID;
                    return;
                }
                m_turnPlayerID = (m_turnPlayerID + 1) % m_playerCount;
                m_doubtJudgeNo = (m_doubtJudgeNo % 13) + 1;
                m_discardManager.ClearCurrentDiscard();
                m_isDiscardTurn = true;
            }
        }
    }
}

void GameManager::SetPlayerDoDoubt(bool isDoubt)
{
    m_isDoubt = isDoubt;
    m_isInputed = true;
    // プレイヤーのダウト/スルー宣言も記録
    m_lastDoubtAction = std::make_pair(m_myPlayerID, isDoubt);
}

bool GameManager::DoubtCheck(int doubtPlayerID, int discardPlayerID)
{
    for (int i = 0; i < 4; ++i) {
        CardData card = m_discardManager.GetCurrentDisCards(i);
        if (card.GetRank() == 0) continue;
        if (card.GetRank() != m_doubtJudgeNo) {
            return true;
        }
    }
    return false;
}

void GameManager::Penalty(int penaltyPlayer)
{
    std::vector<CardData> newHand;
    int handCount = m_player[penaltyPlayer].GetPlayerHands();
    for (int i = 0; i < handCount; ++i) {
        newHand.push_back(m_player[penaltyPlayer].GetCard(i));
    }
    for (int i = 0; i < m_discardManager.GetDiscardCount(); ++i) {
        newHand.push_back(m_discardManager.GetDiscard(i));
    }
    m_player[penaltyPlayer].SetHand(newHand);
    m_discardManager.ClearDiscard();
    m_discardManager.ClearCurrentDiscard();
}
