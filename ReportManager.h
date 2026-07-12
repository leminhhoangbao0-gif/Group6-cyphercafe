#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include <string>

struct Report
{
    double todayRevenue;
    double monthRevenue;
    int totalSessions;
    std::string topCustomer;
    std::string topPC;
};

class ReportManager
{
public:
    ReportManager();

    Report getReport();

    double getTodayRevenue();

    double getMonthRevenue();

    int getTotalSessions();

    std::string getTopCustomer();

    std::string getTopPC();
};

#endif