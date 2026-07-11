#include "ProfileManager.h"

ProfileManager::ProfileManager(UserRepository* repository,
                                 AuthController* authController,
                                 QObject* parent)
    : QObject(parent),
      m_repository(repository),
      m_authController(authController)
{
}

std::optional<User> ProfileManager::getProfile(int userId)
{
    return m_repository->findById(userId);
}

bool ProfileManager::updateProfile(int userId,
                                     const QString& fullName,
                                     const QString& email,
                                     const QString& phone,
                                     QString& errorMessage)
{
    auto userOpt = m_repository->findById(userId);
    if (!userOpt.has_value()) {
        errorMessage = "User not found.";
        return false;
    }

    // If the email is changing, make sure nobody else already has it.
    User user = userOpt.value();
    if (!email.isEmpty() && email != user.email() && m_repository->emailExists(email)) {
        errorMessage = "Email is already in use by another account.";
        return false;
    }

    user.setFullName(fullName);
    user.setEmail(email);
    user.setPhone(phone);

    if (!m_repository->updateProfile(user, errorMessage)) {
        return false;
    }

    emit profileUpdated(user);
    return true;
}

bool ProfileManager::changePassword(int userId,
                                      const QString& oldPassword,
                                      const QString& newPassword,
                                      QString& errorMessage)
{
    auto userOpt = m_repository->findById(userId);
    if (!userOpt.has_value()) {
        errorMessage = "User not found.";
        return false;
    }

    const User& user = userOpt.value();
    if (!AuthController::verifyPassword(oldPassword, user.passwordHash())) {
        errorMessage = "Current password is incorrect.";
        return false;
    }

    if (newPassword.length() < 6) {
        errorMessage = "New password must be at least 6 characters.";
        return false;
    }

    const QString salt = AuthController::generateSalt();
    const QString newHash = salt + "$" + AuthController::hashPassword(newPassword, salt);

    if (!m_repository->updatePasswordHash(userId, newHash, errorMessage)) {
        return false;
    }

    emit passwordChanged();
    return true;
}
