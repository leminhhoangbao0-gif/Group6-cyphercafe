#include "user_repository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QVariant>

UserRepository::UserRepository(QSqlDatabase db)
    : m_db(db)
{
}

bool UserRepository::createTableIfNotExists()
{
    QSqlQuery query(m_db);
    // MySQL syntax: AUTO_INCREMENT (not AUTOINCREMENT), VARCHAR for any
    // column that needs UNIQUE (MySQL can't put UNIQUE on a plain TEXT
    // column without a key-length prefix), DECIMAL for money, DATETIME
    // for timestamps.
    const QString sql = R"(
        CREATE TABLE IF NOT EXISTS users (
            id            INT AUTO_INCREMENT PRIMARY KEY,
            username      VARCHAR(50) UNIQUE NOT NULL,
            password_hash VARCHAR(255) NOT NULL,
            full_name     VARCHAR(100),
            email         VARCHAR(150) UNIQUE,
            phone         VARCHAR(20),
            balance       DECIMAL(10,2) DEFAULT 0,
            role          VARCHAR(20) DEFAULT 'customer',
            created_at    DATETIME NOT NULL
        ) ENGINE=InnoDB
    )";

    if (!query.exec(sql)) {
        return false;
    }
    return true;
}

User UserRepository::userFromQuery(const QSqlQuery& query) const
{
    User user;
    user.setId(query.value("id").toInt());
    user.setUsername(query.value("username").toString());
    user.setPasswordHash(query.value("password_hash").toString());
    user.setFullName(query.value("full_name").toString());
    user.setEmail(query.value("email").toString());
    user.setPhone(query.value("phone").toString());
    user.setBalance(query.value("balance").toDouble());
    user.setRole(query.value("role").toString());
    user.setCreatedAt(query.value("created_at").toDateTime());
    return user;
}

bool UserRepository::insertUser(const User& user, int& newId, QString& errorMessage)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        INSERT INTO users (username, password_hash, full_name, email, phone, balance, role, created_at)
        VALUES (:username, :password_hash, :full_name, :email, :phone, :balance, :role, :created_at)
    )");

    query.bindValue(":username", user.username());
    query.bindValue(":password_hash", user.passwordHash());
    query.bindValue(":full_name", user.fullName());
    query.bindValue(":email", user.email());
    query.bindValue(":phone", user.phone());
    query.bindValue(":balance", user.balance());
    query.bindValue(":role", user.role().isEmpty() ? "customer" : user.role());
    query.bindValue(":created_at", user.createdAt());

    if (!query.exec()) {
        errorMessage = query.lastError().text();
        return false;
    }

    newId = query.lastInsertId().toInt();
    return true;
}

std::optional<User> UserRepository::findByUsername(const QString& username)
{
    QSqlQuery query(m_db);

    query.prepare(
        "SELECT id, username, password_hash, full_name, email, phone, balance, role, created_at "
        "FROM users "
        "WHERE username = :username "
        "LIMIT 1");

    query.bindValue(":username", username);

    if (!query.exec())
    {
        return std::nullopt;
    }

    if (!query.next())
    {
        return std::nullopt;
    }

    return userFromQuery(query);
}

std::optional<User> UserRepository::findById(int id)
{
    QSqlQuery query(m_db);

    query.prepare(
        "SELECT id, username, password_hash, full_name, email, phone, balance, role, created_at "
        "FROM users "
        "WHERE id = :id "
        "LIMIT 1");

    query.bindValue(":id", id);

    if (!query.exec())
    {
        return std::nullopt;
    }

    if (!query.next())
    {
        return std::nullopt;
    }

    return userFromQuery(query);
}

std::optional<User> UserRepository::findByEmail(const QString& email)
{
    QSqlQuery query(m_db);

    query.prepare(
        "SELECT id, username, password_hash, full_name, email, phone, balance, role, created_at "
        "FROM users "
        "WHERE email = :email "
        "LIMIT 1");

    query.bindValue(":email", email);

    if (!query.exec())
    {
        return std::nullopt;
    }

    if (!query.next())
    {
        return std::nullopt;
    }

    return userFromQuery(query);
}

bool UserRepository::usernameExists(const QString& username)
{
    return findByUsername(username).has_value();
}

bool UserRepository::emailExists(const QString& email)
{
    if (email.isEmpty()) return false; // email is optional
    return findByEmail(email).has_value();
}

bool UserRepository::updateProfile(const User& user, QString& errorMessage)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE users
        SET full_name = :full_name, email = :email, phone = :phone
        WHERE id = :id
    )");
    query.bindValue(":full_name", user.fullName());
    query.bindValue(":email", user.email());
    query.bindValue(":phone", user.phone());
    query.bindValue(":id", user.id());

    if (!query.exec()) {
        errorMessage = query.lastError().text();
        return false;
    }
    return true;
}

bool UserRepository::updatePasswordHash(int userId, const QString& newHash, QString& errorMessage)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE users SET password_hash = :hash WHERE id = :id");
    query.bindValue(":hash", newHash);
    query.bindValue(":id", userId);

    if (!query.exec()) {
        errorMessage = query.lastError().text();
        return false;
    }
    return true;
}

bool UserRepository::updateBalance(int userId, double newBalance, QString& errorMessage)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE users SET balance = :balance WHERE id = :id");
    query.bindValue(":balance", newBalance);
    query.bindValue(":id", userId);

    if (!query.exec()) {
        errorMessage = query.lastError().text();
        return false;
    }
    return true;
}
