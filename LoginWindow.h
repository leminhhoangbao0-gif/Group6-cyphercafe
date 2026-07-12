#pragma once

#include <QObject>
#include <QString>
#include <optional>

// Assuming these are your data/repository classes. 
// We must include User.h because std::optional requires the full type definition.
#include "User.h" 

class UserRepository;

class AuthController : public QObject
{
    Q_OBJECT

public:
    explicit AuthController(UserRepository* repository, QObject* parent = nullptr);

    // --- Register ---
    bool registerUser(const QString& username,
                      const QString& password,
                      const QString& fullName,
                      const QString& email,
                      const QString& phone,
                      QString& errorMessage);

    // --- Login / Logout ---
    bool login(const QString& username, const QString& password, QString& errorMessage);
    void logout();

    // --- State ---
    bool isLoggedIn() const;
    std::optional<User> currentUser() const;

signals:
    // Registration signals
    void registrationSucceeded(const User& user);
    void registrationFailed(const QString& errorMessage);

    // Login signals
    void loginSucceeded(const User& user);
    void loginFailed(const QString& errorMessage);
    void loggedOut();

private:
    // Password hashing helpers
    QString generateSalt();
    QString hashPassword(const QString& password, const QString& salt);
    bool verifyPassword(const QString& password, const QString& storedHash);

    // Member variables
    UserRepository* m_repository;
    std::optional<User> m_currentUser;
};