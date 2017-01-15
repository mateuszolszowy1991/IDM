#include <iostream>
#include "IDBWrapper.hpp"
#include "Logger.hpp"
#include "IntegratedSwitchAgent.hpp"
#include "InsideDevicesManager.hpp"
#
using namespace std;

int main()
{
    Logger::clearLogs();
    Logger::saveToFile("IDM: Application started");
    Client* client = new Client();
    IDBWrapper* wrapper = new IDBWrapper(client, "IDM");
    wrapper->welcome();
    InsideDevicesManager* iDM = new InsideDevicesManager(wrapper);
    iDM->initialize();
    iDM->setReady();
    while(true)
    {
        if(iDM->waitForSignal())
        {
            iDM->startSignalProccessing();
        }
    }



    getchar();
    return 0;
}
