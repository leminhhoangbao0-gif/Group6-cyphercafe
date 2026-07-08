#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "PC.h"
#include "Session.h"
#include "TimerService.h"
#include "session_repository.h"

#include <QObject>
#include <QHash>
#include <QList>

class SessionManager : public QObject
{
    Q_OBJECT

public:
    explicit SessionManager(SessionRepository *repository, QObject *parent = nullptr);

    QList<PC> pcs() const;
    QList<Session> activeSessions() const;

    void load();
    void addPc(const PC &pc);
    bool startSession(int pcId, int customerId, int durationMinutes);
    bool endSession(int pcId);
    bool lockPc(int pcId);
    bool unlockPc(int pcId);
    bool setMaintenance(int pcId, bool enabled);

    PC pcById(int pcId) const;
    Session sessionByPcId(int pcId) const;

signals:
    void pcsChanged();
    void sessionsChanged();
    void sessionExpired(int pcId);
    void errorOccurred(const QString &message);

private slots:
    void handleSessionExpired(int sessionId);

private:
    bool updatePcStatus(int pcId, PCStatus status);

    SessionRepository *m_repository;
    TimerService m_timerService;
    QHash<int, PC> m_pcs;
    QHash<int, Session> m_sessionsById;
    QHash<int, int> m_sessionIdByPcId;
};

#endif
