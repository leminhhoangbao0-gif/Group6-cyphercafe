#include "TimerService.h"

TimerService::TimerService(QObject *parent)
    : QObject(parent)
{
    connect(&m_tickTimer, &QTimer::timeout, this, &TimerService::updateTimers);
    m_tickTimer.setInterval(1000);
    m_tickTimer.start();
}

void TimerService::addSession(const Session &session)
{
    if (session.id() <= 0) {
        return;
    }

    m_sessions.insert(session.id(), session);
}

void TimerService::removeSession(int sessionId)
{
    m_sessions.remove(sessionId);
}

void TimerService::clear()
{
    m_sessions.clear();
}

bool TimerService::hasSession(int sessionId) const
{
    return m_sessions.contains(sessionId);
}

void TimerService::updateTimers()
{
    QList<int> expiredIds;
    const QDateTime now = QDateTime::currentDateTime();

    for (auto it = m_sessions.cbegin(); it != m_sessions.cend(); ++it) {
        const int remaining = it.value().remainingSeconds(now);
        emit sessionTick(it.key(), remaining);

        if (remaining == 0) {
            expiredIds.append(it.key());
        }
    }

    for (int sessionId : expiredIds) {
        m_sessions.remove(sessionId);
        emit sessionExpired(sessionId);
    }
}
