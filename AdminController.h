#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include <string>
#include <vector>

struct DashboardData
{
    int totalCustomers;
    int onlinePCs;
    int offlinePCs;
    double todayRevenue;
};

class AdminController
{
public:
    AdminController();

    DashboardData getDashboardData();

    int getTotalCustomers();

    int getOnlinePCs();

    int getOfflinePCs();

    double getTodayRevenue();
};

#endif