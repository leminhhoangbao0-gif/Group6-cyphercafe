#ifndef PCMONITOR_H
#define PCMONITOR_H

#include <string>
#include <vector>

struct PCStatus
{
    int id;
    std::string pcName;
    std::string status;
    std::string currentUser;
    int sessionTime;
};

class PCMonitor
{
public:
    PCMonitor();

    std::vector<PCStatus> getAllPCs();

    int getOnlineCount();

    int getOfflineCount();

    int getBusyCount();

    void updateStatus(int id, const std::string& status);
};

#endif