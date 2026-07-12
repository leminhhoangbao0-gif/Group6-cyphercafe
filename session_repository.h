#ifndef SESSION_REPOSITORY_H
#define SESSION_REPOSITORY_H

#include "PC.h"
#include "Session.h"

#include <QList>
#include <QSqlDatabase>
#include <QString>

class SessionRepository
{
public:
    explicit SessionRepository(const QSqlDatabase &database);

    bool initialize();
    QList<PC> loadPcs() const;
    QList<Session> loadActiveSessions() const;
    bool savePc(const PC &pc) const;
    bool createSession(Session &session) const;
    bool finishSession(const Session &session) const;
    QString lastError() const;

private:
    QSqlDatabase m_database;
    mutable QString m_lastError;
};

#endif
