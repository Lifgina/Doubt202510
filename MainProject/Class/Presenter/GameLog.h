#pragma once

#include "../../HuEngine.h"
#include "../View/TextView.h"
#include <deque>
#include <string>
#include <cstddef>

class GameLog {
public:
    GameLog() = default;

    // View 配列をセット（MainScene から渡す）
    void SetViews(TextView* views, std::size_t count);

    // Presenter のログ API（文言生成）
    void DiscardLog(int playerID, int discardCount);
    void DoubtLog(int playerID, bool isDoubt);
    void PenaltyLog(int playerID, bool doubtCorrect);

private:
    void PushMessage(const std::wstring& msg);
    std::wstring FormatPlayer(int playerID) const;

    TextView* m_views[10]{};
    std::size_t m_viewCount{ 0 };
    std::deque<std::wstring> m_logs;
};