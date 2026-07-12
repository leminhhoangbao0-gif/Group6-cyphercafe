#ifndef ADMIN_REPOSITORY_H
#define ADMIN_REPOSITORY_H

#include <string>
#include <vector>

struct Customer
{
    int id;
    std::string username;
    std::string fullName;
    double balance;
    std::string status;
};

class AdminRepository
{
public:
    AdminRepository();

    // Customer
    std::vector<Customer> getCustomers();

    bool deleteCustomer(int id);

    bool updateBalance(int id, double balance);

    int countCustomers();

    // Dashboard
    double getTodayRevenue();

    double getMonthRevenue();

    int getTotalSessions();

    // PC
    int getOnlinePCs();

    int getOfflinePCs();
};

#endif