#ifndef TIMERSERVICE_H
#define TIMERSERVICE_H

#include "Session.h"

#include <QObject>
#include <QHash>
#include <QList>
#include <QTimer>

class TimerService : public QObject
{
    Q_OBJECT

public:
    explicit TimerService(QObject *parent = nullptr);

    void addSession(const Session &session);
    void removeSession(int sessionId);
    void clear();
    bool hasSession(int sessionId) const;

signals:
    void sessionTick(int sessionId, int remainingSeconds);
    void sessionExpired(int sessionId);

private slots:
    void updateTimers();

private:
    QTimer m_tickTimer;
    QHash<int, Session> m_sessions;
};

#endif
