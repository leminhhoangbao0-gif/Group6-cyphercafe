#pragma once

#include <QSqlDatabase>
#include <QString>
#include <optional>
#include "User.h"

// UserRepository is the ONLY class allowed to write raw SQL for the
// "users" table. Everything else (AuthController, ProfileManager, UI)
// goes through this class. This keeps SQL in one place and makes it
// easy for Member 5 to swap the database backend later if needed.
class UserRepository
{
public:
    explicit UserRepository(QSqlDatabase db);

    // Creates the "users" table if it does not already exist.
    // Call this once at application startup.
    bool createTableIfNotExists();

    // Inserts a new user. On success, fills newId with the generated id.
    bool insertUser(const User& user, int& newId, QString& errorMessage);

    // Lookups. Returns std::nullopt if no matching row is found.
    std::optional<User> findByUsername(const QString& username);
    std::optional<User> findById(int id);
    std::optional<User> findByEmail(const QString& email);

    bool usernameExists(const QString& username);
    bool emailExists(const QString& email);

    // Updates. Return false + errorMessage on failure.
    bool updateProfile(const User& user, QString& errorMessage);
    bool updatePasswordHash(int userId, const QString& newHash, QString& errorMessage);
    bool updateBalance(int userId, double newBalance, QString& errorMessage);

private:
    QSqlDatabase m_db;

    // Helper: builds a User object from the current row of a SELECT query.
    User userFromQuery(const class QSqlQuery& query) const;
};
