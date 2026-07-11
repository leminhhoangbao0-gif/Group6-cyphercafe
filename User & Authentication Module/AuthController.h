#include "User.h"

User::User()
    : m_id(-1),
      m_balance(0.0),
      m_role("customer")
{
}

User::User(int id,
            const QString& username,
            const QString& passwordHash,
            const QString& fullName,
            const QString& email,
            const QString& phone,
            double balance,
            const QString& role,
            const QDateTime& createdAt)
    : m_id(id),
      m_username(username),
      m_passwordHash(passwordHash),
      m_fullName(fullName),
      m_email(email),
      m_phone(phone),
      m_balance(balance),
      m_role(role),
      m_createdAt(createdAt)
{
}

int User::id() const { return m_id; }
QString User::username() const { return m_username; }
QString User::passwordHash() const { return m_passwordHash; }
QString User::fullName() const { return m_fullName; }
QString User::email() const { return m_email; }
QString User::phone() const { return m_phone; }
double User::balance() const { return m_balance; }
QString User::role() const { return m_role; }
QDateTime User::createdAt() const { return m_createdAt; }

void User::setId(int id) { m_id = id; }
void User::setUsername(const QString& username) { m_username = username; }
void User::setPasswordHash(const QString& passwordHash) { m_passwordHash = passwordHash; }
void User::setFullName(const QString& fullName) { m_fullName = fullName; }
void User::setEmail(const QString& email) { m_email = email; }
void User::setPhone(const QString& phone) { m_phone = phone; }
void User::setBalance(double balance) { m_balance = balance; }
void User::setRole(const QString& role) { m_role = role; }
void User::setCreatedAt(const QDateTime& createdAt) { m_createdAt = createdAt; }

bool User::isValid() const
{
    return m_id > 0;
}

bool User::isAdmin() const
{
    return m_role.compare("admin", Qt::CaseInsensitive) == 0;
}
