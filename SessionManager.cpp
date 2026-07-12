#include "SessionManager.h"

#include <algorithm>

SessionManager::SessionManager(SessionRepository *repository, QObject *parent)
    : QObject(parent),
      m_repository(repository),
      m_timerService(this)
{
    connect(&m_timerService,
            &TimerService::sessionExpired,
            this,
            &SessionManager::handleSessionExpired);
}

QList<PC> SessionManager::pcs() const
{
    QList<PC> result = m_pcs.values();
    std::sort(result.begin(), result.end(), [](const PC &left, const PC &right) {
        return left.id() < right.id();
    });
    return result;
}

QList<Session> SessionManager::activeSessions() const
{
    QList<Session> result = m_sessionsById.values();
    std::sort(result.begin(), result.end(), [](const Session &left, const Session &right) {
        return left.id() < right.id();
    });
    return result;
}

void SessionManager::load()
{
    if (!m_repository) {
        emit errorOccurred("Session repository is not configured.");
        return;
    }

    m_pcs.clear();
    m_sessionsById.clear();
    m_sessionIdByPcId.clear();
    m_timerService.clear();

    for (const PC &pc : m_repository->loadPcs()) {
        m_pcs.insert(pc.id(), pc);
    }

    for (const Session &session : m_repository->loadActiveSessions()) {
        m_sessionsById.insert(session.id(), session);
        m_sessionIdByPcId.insert(session.pcId(), session.id());
        m_timerService.addSession(session);
    }

    emit pcsChanged();
    emit sessionsChanged();
}

void SessionManager::addPc(const PC &pc)
{
    if (pc.id() <= 0) {
        emit errorOccurred("PC id must be greater than zero.");
        return;
    }

    m_pcs.insert(pc.id(), pc);

    if (m_repository) {
        m_repository->savePc(pc);
    }

    emit pcsChanged();
}

bool SessionManager::startSession(int pcId, int customerId, int durationMinutes)
{
    if (!m_pcs.contains(pcId)) {
        emit errorOccurred("PC does not exist.");
        return false;
    }

    if (!m_pcs.value(pcId).canStartSession()) {
        emit errorOccurred("PC is not available.");
        return false;
    }

    if (durationMinutes <= 0) {
        emit errorOccurred("Duration must be greater than zero.");
        return false;
    }

    Session session(0, pcId, customerId, QDateTime::currentDateTime(), durationMinutes);

    if (m_repository && !m_repository->createSession(session)) {
        emit errorOccurred("Cannot create session.");
        return false;
    }

    if (session.id() <= 0) {
        int nextId = 1;
        for (const int id : m_sessionsById.keys()) {
            nextId = std::max(nextId, id + 1);
        }
        session.setId(nextId);
    }

    m_sessionsById.insert(session.id(), session);
    m_sessionIdByPcId.insert(pcId, session.id());
    m_timerService.addSession(session);
    updatePcStatus(pcId, PCStatus::InUse);

    emit sessionsChanged();
    return true;
}

bool SessionManager::endSession(int pcId)
{
    if (!m_sessionIdByPcId.contains(pcId)) {
        emit errorOccurred("This PC has no active session.");
        return false;
    }

    const int sessionId = m_sessionIdByPcId.value(pcId);
    Session session = m_sessionsById.value(sessionId);
    session.finish();

    if (m_repository && !m_repository->finishSession(session)) {
        emit errorOccurred("Cannot finish session.");
        return false;
    }

    m_sessionsById.remove(sessionId);
    m_sessionIdByPcId.remove(pcId);
    m_timerService.removeSession(sessionId);
    updatePcStatus(pcId, PCStatus::Available);

    emit sessionsChanged();
    return true;
}

bool SessionManager::lockPc(int pcId)
{
    if (!m_pcs.contains(pcId)) {
        emit errorOccurred("PC does not exist.");
        return false;
    }

    return updatePcStatus(pcId, PCStatus::Locked);
}

bool SessionManager::unlockPc(int pcId)
{
    if (!m_pcs.contains(pcId)) {
        emit errorOccurred("PC does not exist.");
        return false;
    }

    const PCStatus status = m_sessionIdByPcId.contains(pcId)
        ? PCStatus::InUse
        : PCStatus::Available;

    return updatePcStatus(pcId, status);
}

bool SessionManager::setMaintenance(int pcId, bool enabled)
{
    if (!m_pcs.contains(pcId)) {
        emit errorOccurred("PC does not exist.");
        return false;
    }

    return updatePcStatus(pcId, enabled ? PCStatus::Maintenance : PCStatus::Available);
}

PC SessionManager::pcById(int pcId) const
{
    return m_pcs.value(pcId);
}

Session SessionManager::sessionByPcId(int pcId) const
{
    return m_sessionsById.value(m_sessionIdByPcId.value(pcId));
}

void SessionManager::handleSessionExpired(int sessionId)
{
    if (!m_sessionsById.contains(sessionId)) {
        return;
    }

    Session session = m_sessionsById.value(sessionId);
    session.setStatus(SessionStatus::Expired);
    session.setEndTime(QDateTime::currentDateTime());

    if (m_repository) {
        m_repository->finishSession(session);
    }

    const int pcId = session.pcId();
    m_sessionsById.remove(sessionId);
    m_sessionIdByPcId.remove(pcId);
    updatePcStatus(pcId, PCStatus::Locked);

    emit sessionExpired(pcId);
    emit sessionsChanged();
}

bool SessionManager::updatePcStatus(int pcId, PCStatus status)
{
    PC pc = m_pcs.value(pcId);
    pc.setStatus(status);
    m_pcs.insert(pcId, pc);

    if (m_repository && !m_repository->savePc(pc)) {
        emit errorOccurred("Cannot update PC status.");
        return false;
    }

    emit pcsChanged();
    return true;
}
