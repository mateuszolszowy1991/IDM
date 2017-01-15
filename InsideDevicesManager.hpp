#ifndef INSIDEDEVICESMANAGER_H
#define INSIDEDEVICESMANAGER_H
#include "IDBWrapper.hpp"
#include "IntegratedSwitchAgent.hpp"
#include "ChairsAgent.hpp"
#include "CardPortAgent.hpp"
#include <memory>
#define START_BUTTON_TRIGGER    "0x51"

using namespace std;

class InsideDevicesManager
{
    public:
        InsideDevicesManager(IDBWrapper* wrapper);
        virtual ~InsideDevicesManager();
        void initialize();
        void setReady();
        bool waitForSignal();
        void startSignalProccessing();
    protected:

    private:
        string signal_;
        Mo idmMo_;
        Mo hornMo_;
        Mo stereMo_;
        Mo startButtonMo_;
        vector<Mo> windowSwitchMos_;
        vector<Mo> mirroSwitchMos_;
        IDBWrapper* wrapper_;
        IntegratedSwitchAgent* iSA_;
        ChairsAgent* cA_;
        CardPortAgent* cPA_;
        void initWinSwitchAgent();
        void initMirrorSwitchAgent();
        void initLeftSiteAgent();
        void initCenterSiteAgent();
        void initISAgent();
        void initStereAgent();
        void initChairAgent();
        int checkPredicates();
        bool areClutchAndBreakPedalsPushed(vector<Mo*> pedals);
};

#endif // INSIDEDEVICESMANAGER_H
