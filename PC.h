#ifndef PC_H
#define PC_H

#include <QString>

enum class PCStatus {
    Available,
    InUse,
    Locked,
    Maintenance
};

class PC
{
public:
    PC();
    PC(int id, const QString &name, PCStatus status = PCStatus::Available);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    PCStatus status() const;
    void setStatus(PCStatus status);

    bool isAvailable() const;
    bool isLocked() const;
    bool canStartSession() const;

    QString statusText() const;
    static QString statusToString(PCStatus status);
    static PCStatus statusFromString(const QString &status);

private:
    int m_id;
    QString m_name;
    PCStatus m_status;
};

#endif
