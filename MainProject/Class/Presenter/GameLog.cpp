//
// GameLog.cpp
//

#include "GameLog.h"

using namespace HE;

void GameLog::SetViews(TextView* views, std::size_t count)
{
    m_viewCount = (count > 10) ? 10 : count;
    for (std::size_t i = 0; i < m_viewCount; ++i) {
        m_views[i] = &views[i];
    }

    m_logs.clear();
    for (std::size_t i = 0; i < m_viewCount; ++i) m_logs.push_back(L"");
    for (std::size_t i = 0; i < m_viewCount; ++i) {
        if (m_views[i]) m_views[i]->UpdateText(m_logs[i]);
    }
}

std::wstring GameLog::FormatPlayer(int playerID) const
{
    return L"プレイヤー" + std::to_wstring(playerID + 1);
}

void GameLog::PushMessage(const std::wstring& msg)
{
    m_logs.push_front(msg);
    if (m_logs.size() > m_viewCount) m_logs.pop_back();

    for (std::size_t i = 0; i < m_viewCount; ++i) {
        if (!m_views[i]) continue;
        std::wstring text = (i < m_logs.size()) ? m_logs[i] : L"";
        m_views[i]->UpdateText(text);
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