#pragma once

#include "../../HuEngine.h"
#include "CardData.h"

class DiscardManager {
public:
	void SetDiscard(CardData nowdiscard);
	CardData GetCurrentDisCards(int index) const { return currentDiscard_[index]; } // ’¼‘O‚ÌÌ‚ÄD‚ğæ“¾ 
	CardData GetDiscard(int index) const { return discard_[index]; } // Ì‚ÄD‚ğæ“¾
	int GetDiscardCount() const { return discardCount_; } // Ì‚ÄD‚Ì–‡”‚ğæ“¾
	int GetCurrentDiscardCount() const { return currentDiscardCount_; } // Œ»İ‚ÌÌ‚ÄD‚Ì–‡”‚ğæ“¾
	void ClearDiscard();  // Ì‚ÄD‚ğƒNƒŠƒA
	void ClearCurrentDiscard();// Œ»İ‚ÌÌ‚ÄD‚Ì–‡”‚ğƒŠƒZƒbƒg

private:
	int currentDiscardCount_ = 0; // Œ»İ‚ÌÌ‚ÄD‚Ì–‡”
	int discardCount_ = 0; // Œ»İ‚ÌÌ‚ÄD‚Ì–‡”	
	CardData currentDiscard_[4]; // ’¼‘O‚ÌÌ‚ÄD
	CardData discard_[52];//Ì‚ÄD
};