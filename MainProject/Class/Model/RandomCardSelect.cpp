//
// CardDate.cpp
//

#include "RandomCardSelect.h"
#include <random>
#include <vector>
#include <algorithm>

using namespace HE;

void RandomCardSelect::CardSelect(int hands,int judgeNo,CardData cards[])
{
    // ‚Ü‚¸‘S‚Ä-1‚Å‰Šú‰»
    for (int i = 0; i < 4; ++i) {
        selectedCardIndex_[i] = -1;
    }

    std::vector<int> correctIndices;
    for (int i = 0; i < hands; ++i) {
        if (cards[i].GetRank() == judgeNo) {
            correctIndices.push_back(i);
        }
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    if (!correctIndices.empty() && dist(gen) < correctDiscardRate_) {
        for (size_t i = 0; i < std::min<size_t>(correctIndices.size(), 4); ++i) {
            selectedCardIndex_[i] = correctIndices[i];
        }
    }
    else {
        float r = dist(gen);
        int numToSelect = 1;
        if (r < discard1Rate_) numToSelect = 1;
        else if (r < discard1Rate_ + discard2Rate_) numToSelect = 2;
        else if (r < discard1Rate_ + discard2Rate_ + discard3Rate_) numToSelect = 3;
        else numToSelect = 4;
        numToSelect = std::min(numToSelect, hands);

        std::vector<int> indices(hands);
        for (int i = 0; i < hands; ++i) indices[i] = i;
        std::shuffle(indices.begin(), indices.end(), gen);

        for (int i = 0; i < numToSelect; ++i) {
            selectedCardIndex_[i] = indices[i];
        }
    }
}

