#include "Admin.h"

Admin::Admin()
{
    id = 0;
    username = "";
    password = "";
    fullName = "";
}

Admin::Admin(int id,
             const std::string& username,
             const std::string& password,
             const std::string& fullName)
{
    this->id = id;
    this->username = username;
    this->password = password;
    this->fullName = fullName;
}

int Admin::getId() const
{
    return id;
}

std::string Admin::getUsername() const
{
    return username;
}

std::string Admin::getPassword() const
{
    return password;
}

std::string Admin::getFullName() const
{
    return fullName;
}

void Admin::setId(int id)
{
    this->id = id;
}

void Admin::setUsername(const std::string& username)
{
    this->username = username;
}

void Admin::setPassword(const std::string& password)
{
    this->password = password;
}

void Admin::setFullName(const std::string& fullName)
{
    this->fullName = fullName;
}

bool Admin::login(const std::string& user,
                  const std::string& pass)
{
    return (user == username && pass == password);
}