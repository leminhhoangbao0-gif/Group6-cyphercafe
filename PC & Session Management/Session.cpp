#include "Session.h"

#include <algorithm>

Session::Session()
    : m_id(0),
      m_pcId(0),
      m_customerId(0),
      m_durationMinutes(0),
      m_status(SessionStatus::Active)
{
}

Session::Session(int id,
                 int pcId,
                 int customerId,
                 const QDateTime &startTime,
                 int durationMinutes,
                 SessionStatus status)
    : m_id(id),
      m_pcId(pcId),
      m_customerId(customerId),
      m_startTime(startTime),
      m_durationMinutes(durationMinutes),
      m_status(status)
{
}

int Session::id() const
{
    return m_id;
}

void Session::setId(int id)
{
    m_id = id;
}

int Session::pcId() const
{
    return m_pcId;
}

void Session::setPcId(int pcId)
{
    m_pcId = pcId;
}

int Session::customerId() const
{
    return m_customerId;
}

void Session::setCustomerId(int customerId)
{
    m_customerId = customerId;
}

QDateTime Session::startTime() const
{
    return m_startTime;
}

void Session::setStartTime(const QDateTime &startTime)
{
    m_startTime = startTime;
}

QDateTime Session::endTime() const
{
    return m_endTime;
}

void Session::setEndTime(const QDateTime &endTime)
{
    m_endTime = endTime;
}

int Session::durationMinutes() const
{
    return m_durationMinutes;
}

void Session::setDurationMinutes(int durationMinutes)
{
    m_durationMinutes = std::max(0, durationMinutes);
}

SessionStatus Session::status() const
{
    return m_status;
}

void Session::setStatus(SessionStatus status)
{
    m_status = status;
}

bool Session::isActive() const
{
    return m_status == SessionStatus::Active;
}

bool Session::isExpired(const QDateTime &now) const
{
    return isActive() && remainingSeconds(now) == 0;
}

int Session::elapsedSeconds(const QDateTime &now) const
{
    if (!m_startTime.isValid()) {
        return 0;
    }

    return static_cast<int>(std::max<qint64>(0, m_startTime.secsTo(now)));
}

int Session::remainingSeconds(const QDateTime &now) const
{
    const int totalSeconds = m_durationMinutes * 60;
    return std::max(0, totalSeconds - elapsedSeconds(now));
}

void Session::finish(const QDateTime &endTime)
{
    m_endTime = endTime;
    m_status = SessionStatus::Finished;
}

QString Session::statusText() const
{
    return statusToString(m_status);
}

QString Session::statusToString(SessionStatus status)
{
    switch (status) {
    case SessionStatus::Active:
        return "Active";
    case SessionStatus::Paused:
        return "Paused";
    case SessionStatus::Finished:
        return "Finished";
    case SessionStatus::Expired:
        return "Expired";
    }

    return "Active";
}

SessionStatus Session::statusFromString(const QString &status)
{
    const QString value = status.trimmed().toLower();

    if (value == "paused") {
        return SessionStatus::Paused;
    }

    if (value == "finished") {
        return SessionStatus::Finished;
    }

    if (value == "expired") {
        return SessionStatus::Expired;
    }

    return SessionStatus::Active;
}
