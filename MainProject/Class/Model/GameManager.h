#pragma once

#include <optional>
#include "../../HuEngine.h"
#include "CardDistributer.h"
#include "DiscardManager.h"
#include "CardDiscarder.h"
#include "RandomCardSelect.h"
#include "PlayerData.h"

class GameManager {
public:
    void Load();
    void Initialize();
    void Update();
    void DiscardTurn();
    void DoubtTurn();
    bool DoubtCheck(int doubtPlayerID, int discardPlayerID);
    void Penalty(int penaltyPlayer);
    void SetPlayerDiscard(int cardIndex[4]);
    void SetPlayerDoDoubt(bool isDoubt);
    int SetMyPlayerID(int playerID) {
        m_myPlayerID = playerID;
        return m_myPlayerID;
    }
    int SetPlayerCount(int playerCount) {
        m_playerCount = playerCount;
        return m_playerCount;
    }
    bool GetIsDiscardTurn() const { return m_isDiscardTurn; }
    bool GetIsInputed() const { return m_isInputed; }
    int GetTurnPlayerID() const { return m_turnPlayerID; }
    int GetDoubtJudgeNo() const { return m_doubtJudgeNo; }
    int GetDoubtPlayerID() const { return m_doubtPlayerID; }
    int GetWinnerPlayerID() const { return m_winnerPlayerID; }
    int GetDiscardCount() const { return m_discardManager.GetDiscardCount(); }
    PlayerData GetPlayerData(int playerID) const { return m_player[playerID]; }

    // ?_?E?g????????
    void SetDoubtResult(bool result) { m_doubtResult = result; }
    bool IsDoubtResultAvailable() const { return m_doubtResult.has_value(); }
    bool GetDoubtResult() const { return m_doubtResult.value_or(false); }
    void ResetDoubtResult() { m_doubtResult.reset(); }

    // ?????_?E?g/?X???[?????
    std::optional<std::pair<int, bool>> GetLastDoubtAction() const { return m_lastDoubtAction; }
    void ResetLastDoubtAction() { m_lastDoubtAction.reset(); }

    int GetLastDoubtPlayerID() const { return m_lastDoubtPlayerID; }
    void ResetLastDoubtPlayerID() { m_lastDoubtPlayerID = -1; }

private:
    int m_playerCount;
    PlayerData m_player[4];
    int m_playerDiscardIndex[4];
    int m_myPlayerID;
    int m_turnPlayerID;
    int m_discardPlayerID;
    int m_doubtJudgeNo;
    int m_doubtPlayerID;
    int m_winnerPlayerID;
    int m_lastDoubtPlayerID = -1; // ?????_?E?g????ID?iPenaltyLog?p?j
    bool m_isDiscardTurn;
    bool m_isInputed;
    bool m_isDoubt;
    std::optional<bool> m_doubtResult;

    // ???: ?????_?E?g/?X???[??
    std::optional<std::pair<int, bool>> m_lastDoubtAction;

    CardDistributer m_cardDistributer;
    CardDiscarder m_cardDiscarder;
    DiscardManager m_discardManager;
    RandomCardSelect m_randomCardSelect;
};
