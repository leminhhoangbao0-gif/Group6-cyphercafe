#include "AuthController.h"

#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QDateTime>

AuthController::AuthController(UserRepository* repository, QObject* parent)
    : QObject(parent),
      m_repository(repository)
{
}

// --- Password hashing --------------------------------------------------
// We never store plain-text passwords. Each user gets a random salt,
// and we hash (salt + password) with SHA-256. The stored string looks
// like:  "3f9a1b2c...$a91cddef..."   (salt $ hash)

QString AuthController::generateSalt()
{
    const QString chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString salt;
    for (int i = 0; i < 16; ++i) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        salt.append(chars.at(index));
    }
    return salt;
}

QString AuthController::hashPassword(const QString& password, const QString& salt)
{
    QByteArray data = (salt + password).toUtf8();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
    return QString::fromUtf8(hash.toHex());
}

bool AuthController::verifyPassword(const QString& password, const QString& storedHash)
{
    // storedHash format: "salt$hash"
    const QStringList parts = storedHash.split('$');
    if (parts.size() != 2) {
        return false; // malformed stored hash
    }
    const QString salt = parts.at(0);
    const QString expectedHash = parts.at(1);
    const QString actualHash = hashPassword(password, salt);
    return actualHash == expectedHash;
}

// --- Register ------------------------------------------------------------

bool AuthController::registerUser(const QString& username,
                                    const QString& password,
                                    const QString& fullName,
                                    const QString& email,
                                    const QString& phone,
                                    QString& errorMessage)
{
    if (username.trimmed().isEmpty() || password.isEmpty()) {
        errorMessage = "Username and password are required.";
        emit registrationFailed(errorMessage);
        return false;
    }

    if (password.length() < 6) {
        errorMessage = "Password must be at least 6 characters.";
        emit registrationFailed(errorMessage);
        return false;
    }

    if (m_repository->usernameExists(username)) {
        errorMessage = "Username is already taken.";
        emit registrationFailed(errorMessage);
        return false;
    }

    if (!email.isEmpty() && m_repository->emailExists(email)) {
        errorMessage = "Email is already registered.";
        emit registrationFailed(errorMessage);
        return false;
    }

    const QString salt = generateSalt();
    const QString hash = salt + "$" + hashPassword(password, salt);

    User newUser;
    newUser.setUsername(username);
    newUser.setPasswordHash(hash);
    newUser.setFullName(fullName);
    newUser.setEmail(email);
    newUser.setPhone(phone);
    newUser.setBalance(0.0);
    newUser.setRole("customer");
    newUser.setCreatedAt(QDateTime::currentDateTime());

    int newId = -1;
    if (!m_repository->insertUser(newUser, newId, errorMessage)) {
        emit registrationFailed(errorMessage);
        return false;
    }

    newUser.setId(newId);
    emit registrationSucceeded(newUser);
    return true;
}

// --- Login / Logout -------------------------------------------------------

bool AuthController::login(const QString& username, const QString& password, QString& errorMessage)
{
    auto userOpt = m_repository->findByUsername(username);
    if (!userOpt.has_value()) {
        errorMessage = "Invalid username or password.";
        emit loginFailed(errorMessage);
        return false;
    }

    const User& user = userOpt.value();
    if (!verifyPassword(password, user.passwordHash())) {
        errorMessage = "Invalid username or password.";
        emit loginFailed(errorMessage);
        return false;
    }

    m_currentUser = user;
    emit loginSucceeded(user);
    return true;
}

void AuthController::logout()
{
    m_currentUser.reset();
    emit loggedOut();
}

bool AuthController::isLoggedIn() const
{
    return m_currentUser.has_value();
}

std::optional<User> AuthController::currentUser() const
{
    return m_currentUser;
}
