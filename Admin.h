#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin
{
private:
    int id;
    std::string username;
    std::string password;
    std::string fullName;

public:
    Admin();

    Admin(int id,
          const std::string& username,
          const std::string& password,
          const std::string& fullName);

    // Getter
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;

    // Setter
    void setId(int id);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setFullName(const std::string& fullName);

    bool login(const std::string& user,
               const std::string& pass);
};

#endif