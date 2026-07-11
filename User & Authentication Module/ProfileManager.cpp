#pragma once

#include <QObject>
#include <QString>
#include <optional>
#include "User.h"
#include "user_repository.h"
#include "AuthController.h"

// ProfileManager handles changes to an EXISTING account:
// editing profile info and changing the password.
// (AuthController handles creating the account and logging in.)
class ProfileManager : public QObject
{
    Q_OBJECT

public:
    explicit ProfileManager(UserRepository* repository,
                             AuthController* authController,
                             QObject* parent = nullptr);

    // Updates name/email/phone for the given user.
    bool updateProfile(int userId,
                        const QString& fullName,
                        const QString& email,
                        const QString& phone,
                        QString& errorMessage);

    // Verifies oldPassword, then sets newPassword if it's valid.
    bool changePassword(int userId,
                         const QString& oldPassword,
                         const QString& newPassword,
                         QString& errorMessage);

    std::optional<User> getProfile(int userId);

signals:
    void profileUpdated(const User& user);
    void passwordChanged();

private:
    UserRepository* m_repository;
    AuthController* m_authController;
};
