#pragma once
#include "PlayerData.h"
#include "DiscardManager.h"
#include "RandomCardSelect.h"

class CardDiscarder {
public:
    void Discard(
        PlayerData players[4],
        int playerCount,
        int turnPlayerID,
        int myPlayerID,
        int doubtJudgeNo,
        int playerDiscardIndex[4],
        bool isInputed,
        DiscardManager& discardManager,
        RandomCardSelect& randomCardSelect,
        bool& outIsInputed,
        bool& outIsDiscardTurn
    );
};
