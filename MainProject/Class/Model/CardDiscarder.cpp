#include "CardDiscarder.h"
#include <vector>
#include <algorithm>

void CardDiscarder::Discard(
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
) {
    int discardIndex[4] = { -1, -1, -1, -1 };

    if (turnPlayerID == myPlayerID) {
        if (!isInputed) {
            return;
        }
        for (int i = 0; i < 4; ++i) {
            discardIndex[i] = playerDiscardIndex[i];
        }
    } else {
        int hands = players[turnPlayerID].GetPlayerHands();
        CardData handcards[52];
        for (int i = 0; i < hands; ++i) {
            handcards[i] = players[turnPlayerID].GetCard(i);
        }
        randomCardSelect.CardSelect(hands, doubtJudgeNo, handcards);
        for (int i = 0; i < 4; ++i) {
            discardIndex[i] = randomCardSelect.GetSelectedCardIndex(i);
        }
    }
    std::vector<int> sortedIndices;
    for (int i = 0; i < 4; ++i) {
        if (discardIndex[i] != -1) {
            sortedIndices.push_back(discardIndex[i]);
        }
    }
    std::sort(sortedIndices.rbegin(), sortedIndices.rend());
    for (int idx : sortedIndices) {
        discardManager.SetDiscard(players[turnPlayerID].GetCard(idx));
        players[turnPlayerID].DisCard(idx);
    }
    outIsInputed = false;
    outIsDiscardTurn = false;
}
