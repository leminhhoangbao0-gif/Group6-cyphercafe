#include "ReportManager.h"

ReportManager::ReportManager()
{

}

Report ReportManager::getReport()
{
    Report report;

    report.todayRevenue = getTodayRevenue();
    report.monthRevenue = getMonthRevenue();
    report.totalSessions = getTotalSessions();
    report.topCustomer = getTopCustomer();
    report.topPC = getTopPC();

    return report;
}

double ReportManager::getTodayRevenue()
{
    // TODO: Lấy từ Database
    return 2450000;
}

double ReportManager::getMonthRevenue()
{
    // TODO: Lấy từ Database
    return 68500000;
}

int ReportManager::getTotalSessions()
{
    // TODO: Đếm số phiên sử dụng
    return 385;
}

std::string ReportManager::getTopCustomer()
{
    // TODO: Khách sử dụng nhiều nhất
    return "lam123";
}

std::string ReportManager::getTopPC()
{
    // TODO: Máy được sử dụng nhiều nhất
    return "PC05";
}