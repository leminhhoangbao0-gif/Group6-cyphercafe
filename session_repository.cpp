#include "session_repository.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

SessionRepository::SessionRepository(const QSqlDatabase &database)
    : m_database(database)
{
}

bool SessionRepository::initialize()
{
    QSqlQuery query(m_database);

    if (!query.exec("CREATE TABLE IF NOT EXISTS pcs ("
                    "id INTEGER PRIMARY KEY,"
                    "name TEXT NOT NULL,"
                    "status TEXT NOT NULL)")) {
        m_lastError = query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS sessions ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "pc_id INTEGER NOT NULL,"
                    "customer_id INTEGER NOT NULL,"
                    "start_time TEXT NOT NULL,"
                    "end_time TEXT,"
                    "duration_minutes INTEGER NOT NULL,"
                    "status TEXT NOT NULL,"
                    "FOREIGN KEY(pc_id) REFERENCES pcs(id))")) {
        m_lastError = query.lastError().text();
        return false;
    }

    return true;
}

QList<PC> SessionRepository::loadPcs() const
{
    QList<PC> pcs;
    QSqlQuery query(m_database);

    if (!query.exec("SELECT id, name, status FROM pcs ORDER BY id")) {
        m_lastError = query.lastError().text();
        return pcs;
    }

    while (query.next()) {
        pcs.append(PC(query.value(0).toInt(),
                      query.value(1).toString(),
                      PC::statusFromString(query.value(2).toString())));
    }

    return pcs;
}

QList<Session> SessionRepository::loadActiveSessions() const
{
    QList<Session> sessions;
    QSqlQuery query(m_database);

    if (!query.exec("SELECT id, pc_id, customer_id, start_time, duration_minutes, status "
                    "FROM sessions WHERE status IN ('Active', 'Paused') ORDER BY id")) {
        m_lastError = query.lastError().text();
        return sessions;
    }

    while (query.next()) {
        sessions.append(Session(query.value(0).toInt(),
                                query.value(1).toInt(),
                                query.value(2).toInt(),
                                QDateTime::fromString(query.value(3).toString(), Qt::ISODate),
                                query.value(4).toInt(),
                                Session::statusFromString(query.value(5).toString())));
    }

    return sessions;
}

bool SessionRepository::savePc(const PC &pc) const
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO pcs (id, name, status) VALUES (:id, :name, :status) "
                  "ON CONFLICT(id) DO UPDATE SET name = excluded.name, status = excluded.status");
    query.bindValue(":id", pc.id());
    query.bindValue(":name", pc.name());
    query.bindValue(":status", pc.statusText());

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }

    return true;
}

bool SessionRepository::createSession(Session &session) const
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO sessions "
                  "(pc_id, customer_id, start_time, duration_minutes, status) "
                  "VALUES (:pc_id, :customer_id, :start_time, :duration_minutes, :status)");
    query.bindValue(":pc_id", session.pcId());
    query.bindValue(":customer_id", session.customerId());
    query.bindValue(":start_time", session.startTime().toString(Qt::ISODate));
    query.bindValue(":duration_minutes", session.durationMinutes());
    query.bindValue(":status", session.statusText());

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }

    session.setId(query.lastInsertId().toInt());
    return true;
}

bool SessionRepository::finishSession(const Session &session) const
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE sessions SET end_time = :end_time, status = :status WHERE id = :id");
    query.bindValue(":end_time", session.endTime().toString(Qt::ISODate));
    query.bindValue(":status", session.statusText());
    query.bindValue(":id", session.id());

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }

    return true;
}

QString SessionRepository::lastError() const
{
    return m_lastError;
}
