#include "PC.h"

PC::PC()
    : m_id(0),
      m_status(PCStatus::Available)
{
}

PC::PC(int id, const QString &name, PCStatus status)
    : m_id(id),
      m_name(name),
      m_status(status)
{
}

int PC::id() const
{
    return m_id;
}

void PC::setId(int id)
{
    m_id = id;
}

QString PC::name() const
{
    return m_name;
}

void PC::setName(const QString &name)
{
    m_name = name;
}

PCStatus PC::status() const
{
    return m_status;
}

void PC::setStatus(PCStatus status)
{
    m_status = status;
}

bool PC::isAvailable() const
{
    return m_status == PCStatus::Available;
}

bool PC::isLocked() const
{
    return m_status == PCStatus::Locked;
}

bool PC::canStartSession() const
{
    return m_status == PCStatus::Available;
}

QString PC::statusText() const
{
    return statusToString(m_status);
}

QString PC::statusToString(PCStatus status)
{
    switch (status) {
    case PCStatus::Available:
        return "Available";
    case PCStatus::InUse:
        return "InUse";
    case PCStatus::Locked:
        return "Locked";
    case PCStatus::Maintenance:
        return "Maintenance";
    }

    return "Available";
}

PCStatus PC::statusFromString(const QString &status)
{
    const QString value = status.trimmed().toLower();

    if (value == "inuse" || value == "in_use" || value == "in use") {
        return PCStatus::InUse;
    }

    if (value == "locked") {
        return PCStatus::Locked;
    }

    if (value == "maintenance") {
        return PCStatus::Maintenance;
    }

    return PCStatus::Available;
}
