#pragma once

#include <QString>
#include <QDateTime>

class User
{
public:
    // Constructors
    User();
    User(int id,
         const QString& username,
         const QString& passwordHash,
         const QString& fullName,
         const QString& email,
         const QString& phone,
         double balance,
         const QString& role,
         const QDateTime& createdAt);

    // Getters
    int id() const;
    QString username() const;
    QString passwordHash() const;
    QString fullName() const;
    QString email() const;
    QString phone() const;
    double balance() const;
    QString role() const;
    QDateTime createdAt() const;

    // Setters
    void setId(int id);
    void setUsername(const QString& username);
    void setPasswordHash(const QString& passwordHash);
    void setFullName(const QString& fullName);
    void setEmail(const QString& email);
    void setPhone(const QString& phone);
    void setBalance(double balance);
    void setRole(const QString& role);
    void setCreatedAt(const QDateTime& createdAt);

    // Helper Methods
    bool isValid() const;
    bool isAdmin() const;

private:
    // Member Variables
    int m_id;
    QString m_username;
    QString m_passwordHash;
    QString m_fullName;
    QString m_email;
    QString m_phone;
    double m_balance;
    QString m_role;
    QDateTime m_createdAt;
};