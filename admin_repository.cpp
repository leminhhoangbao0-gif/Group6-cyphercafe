#include "admin_repository.h"

AdminRepository::AdminRepository()
{

}

std::vector<Customer> AdminRepository::getCustomers()
{
    std::vector<Customer> customers;

    customers.push_back(
        {1,"lam123","Vu Binh Lam",150000,"Online"}
    );

    customers.push_back(
        {2,"nam456","Nguyen Van Nam",85000,"Offline"}
    );

    customers.push_back(
        {3,"hoa789","Tran Thi Hoa",230000,"Online"}
    );

    customers.push_back(
        {4,"minh001","Le Minh",120000,"Offline"}
    );

    return customers;
}

bool AdminRepository::deleteCustomer(int id)
{
    // TODO
    return true;
}

bool AdminRepository::updateBalance(int id,double balance)
{
    // TODO
    return true;
}

int AdminRepository::countCustomers()
{
    return getCustomers().size();
}

double AdminRepository::getTodayRevenue()
{
    return 2450000;
}

double AdminRepository::getMonthRevenue()
{
    return 68500000;
}

int AdminRepository::getTotalSessions()
{
    return 385;
}

int AdminRepository::getOnlinePCs()
{
    return 22;
}

int AdminRepository::getOfflinePCs()
{
    return 8;
}