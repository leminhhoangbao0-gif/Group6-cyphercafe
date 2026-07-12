#include "PCMonitor.h"

PCMonitor::PCMonitor()
{

}

std::vector<PCStatus> PCMonitor::getAllPCs()
{
    std::vector<PCStatus> pcs;

    pcs.push_back({1,"PC01","Busy","lam123",3600});
    pcs.push_back({2,"PC02","Available","",0});
    pcs.push_back({3,"PC03","Offline","",0});
    pcs.push_back({4,"PC04","Busy","nam456",2100});
    pcs.push_back({5,"PC05","Available","",0});
    pcs.push_back({6,"PC06","Maintenance","",0});

    return pcs;
}

int PCMonitor::getOnlineCount()
{
    int count = 0;

    for(const auto& pc : getAllPCs())
    {
        if(pc.status == "Available" || pc.status == "Busy")
            count++;
    }

    return count;
}

int PCMonitor::getOfflineCount()
{
    int count = 0;

    for(const auto& pc : getAllPCs())
    {
        if(pc.status == "Offline")
            count++;
    }

    return count;
}

int PCMonitor::getBusyCount()
{
    int count = 0;

    for(const auto& pc : getAllPCs())
    {
        if(pc.status == "Busy")
            count++;
    }

    return count;
}

void PCMonitor::updateStatus(int id,const std::string& status)
{
    // TODO
    // Sau này cập nhật Database
}