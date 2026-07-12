#include "AdminController.h"

AdminController::AdminController()
{

}

DashboardData AdminController::getDashboardData()
{
    DashboardData data;

    data.totalCustomers = getTotalCustomers();
    data.onlinePCs = getOnlinePCs();
    data.offlinePCs = getOfflinePCs();
    data.todayRevenue = getTodayRevenue();

    return data;
}

int AdminController::getTotalCustomers()
{
    // TODO:
    // Sau này đọc từ Database

    return 150;
}

int AdminController::getOnlinePCs()
{
    return 22;
}

int AdminController::getOfflinePCs()
{
    return 8;
}

double AdminController::getTodayRevenue()
{
    return 2450000;
} 