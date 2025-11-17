#include "CardDistributer.h"
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace HE;

void CardDistributer::DistributeCards(PlayerData player[], int playerCount)
{
    // 52枚のカードを作成
    std::vector<CardData> deck;
    for (int suit = 0; suit < 4; ++suit) {
        for (int rank = 1; rank <= 13; ++rank) {
            CardData card;
            card.SetSuit(suit);
            card.SetRank(rank);
            deck.push_back(card);
        }
    }

    // シャッフル
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);

    // プレイヤー人数分配る
    int cardsPerPlayer = static_cast<int>(deck.size()) / playerCount;
    for (int i = 0; i < playerCount; ++i) {
        std::vector<CardData> hand(deck.begin() + i * cardsPerPlayer, deck.begin() + (i + 1) * cardsPerPlayer);
        player[i].SetHand(hand);
    }
}

