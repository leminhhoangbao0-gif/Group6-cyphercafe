#ifndef SESSION_H
#define SESSION_H

#include <QDateTime>
#include <QString>

enum class SessionStatus {
    Active,
    Paused,
    Finished,
    Expired
};

class Session
{
public:
    Session();
    Session(int id,
            int pcId,
            int customerId,
            const QDateTime &startTime,
            int durationMinutes,
            SessionStatus status = SessionStatus::Active);

    int id() const;
    void setId(int id);

    int pcId() const;
    void setPcId(int pcId);

    int customerId() const;
    void setCustomerId(int customerId);

    QDateTime startTime() const;
    void setStartTime(const QDateTime &startTime);

    QDateTime endTime() const;
    void setEndTime(const QDateTime &endTime);

    int durationMinutes() const;
    void setDurationMinutes(int durationMinutes);

    SessionStatus status() const;
    void setStatus(SessionStatus status);

    bool isActive() const;
    bool isExpired(const QDateTime &now = QDateTime::currentDateTime()) const;
    int elapsedSeconds(const QDateTime &now = QDateTime::currentDateTime()) const;
    int remainingSeconds(const QDateTime &now = QDateTime::currentDateTime()) const;
    void finish(const QDateTime &endTime = QDateTime::currentDateTime());

    QString statusText() const;
    static QString statusToString(SessionStatus status);
    static SessionStatus statusFromString(const QString &status);

private:
    int m_id;
    int m_pcId;
    int m_customerId;
    QDateTime m_startTime;
    QDateTime m_endTime;
    int m_durationMinutes;
    SessionStatus m_status;
};

#endif
