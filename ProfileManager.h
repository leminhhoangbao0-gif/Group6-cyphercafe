#pragma once

#include <QObject>
#include <QString>
#include <optional>
#include "User.h"
#include "user_repository.h"

// AuthController handles everything related to "logging in" as opposed
// to "storing data": login, register, logout, and password hashing.
// It keeps track of the currently logged-in user for the whole app
// (this is the "session login request" mentioned in the module spec).
class AuthController : public QObject
{
    Q_OBJECT

public:
    explicit AuthController(UserRepository* repository, QObject* parent = nullptr);

    // Creates a new account. Returns true on success.
    // On failure, errorMessage explains why (e.g. "Username already taken").
    bool registerUser(const QString& username,
                       const QString& password,
                       const QString& fullName,
                       const QString& email,
                       const QString& phone,
                       QString& errorMessage);

    // Attempts to log in. Returns true on success and sets the current user.
    bool login(const QString& username, const QString& password, QString& errorMessage);

    // Clears the current session.
    void logout();

    bool isLoggedIn() const;
    std::optional<User> currentUser() const;

    // --- Password helpers (also usable by ProfileManager) ---
    // Format stored in DB: "salt$hash"
    static QString hashPassword(const QString& password, const QString& salt);
    static QString generateSalt();
    static bool verifyPassword(const QString& password, const QString& storedHash);

signals:
    void loginSucceeded(const User& user);
    void loginFailed(const QString& reason);
    void registrationSucceeded(const User& user);
    void registrationFailed(const QString& reason);
    void loggedOut();

private:
    UserRepository* m_repository;
    std::optional<User> m_currentUser;
};
