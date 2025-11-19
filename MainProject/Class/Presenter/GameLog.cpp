//
// GameLog.cpp
//

#include "GameLog.h"

using namespace HE;

void GameLog::SetViews(TextView* views, std::size_t count)
{
    viewCount_ = (count > 10) ? 10 : count;
    for (std::size_t i = 0; i < viewCount_; ++i) {
        views_[i] = &views[i];
    }

    logs_.clear();
    for (std::size_t i = 0; i < viewCount_; ++i) logs_.push_back(L"");
    for (std::size_t i = 0; i < viewCount_; ++i) {
        if (views_[i]) views_[i]->UpdateText(logs_[i]);
    }
}

std::wstring GameLog::FormatPlayer(int playerID) const
{
    return L"プレイヤー" + std::to_wstring(playerID + 1);
}

void GameLog::PushMessage(const std::wstring& msg)
{
    logs_.push_front(msg);
    if (logs_.size() > viewCount_) logs_.pop_back();

    for (std::size_t i = 0; i < viewCount_; ++i) {
        if (!views_[i]) continue;
        std::wstring text = (i < logs_.size()) ? logs_[i] : L"";
        views_[i]->UpdateText(text);
    }
}

void GameLog::DiscardLog(int playerID, int discardCount)
{
    PushMessage(FormatPlayer(playerID) + L"はカードを" + std::to_wstring(discardCount) + L"枚捨てた。");
}

void GameLog::DoubtLog(int playerID, bool isDoubt)
{
    if (isDoubt) PushMessage(FormatPlayer(playerID) + L"はダウトを宣言した！");
    else PushMessage(FormatPlayer(playerID) + L"はスルーした。");
}

void GameLog::PenaltyLog(int playerID, bool doubtCorrect)
{
    if (doubtCorrect) PushMessage(FormatPlayer(playerID) + L"はダウトに成功！！");
    else PushMessage(FormatPlayer(playerID) + L"はダウトに失敗！！");
}