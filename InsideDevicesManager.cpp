#include "InsideDevicesManager.hpp"

InsideDevicesManager::InsideDevicesManager(IDBWrapper* wrapper) : wrapper_(wrapper)
{
    //ctor
}

InsideDevicesManager::~InsideDevicesManager()
{
    //dtor
}

void InsideDevicesManager::initialize()
{
    idmMo_ = wrapper_->createObject("CAR/IDM", "Online", "Configuring");
    initISAgent();
    initLeftSiteAgent();
    initChairAgent();
    initCenterSiteAgent();
}

void InsideDevicesManager::setReady()
{
    wrapper_->setProceduralState(&idmMo_, "Configured");
    waitForSignal();
}

bool InsideDevicesManager::waitForSignal()
{
    ifstream infile("/home/mato3/OSCAR/SYS/sigs/USER_SIG.dat");
    if(infile.good())
    {
        Logger::saveToFile("BDM/INF: RCDM: USER_SIG.dat found" );
        fstream sig( "/home/mato3/OSCAR/SYS/sigs/USER_SIG.dat", std::ios::in );
        getline(sig, signal_);
        sig.close();
        Logger::saveToFile("BDM/INF: RemoteControllerDeviceManager: waitForSignal: received signal: " + signal_ );
        return infile.good();
    }
    //cout << "RC_SIG not found" <<endl;
    return false;
}

void InsideDevicesManager::startSignalProccessing()
{
    if(signal_ == START_BUTTON_TRIGGER)
    {
        Mo mdmStartSignal = wrapper_->createObject("CAR/MDM/START_ENGINE_REQ", "NA", "NA");
        //if(checkPredicates() == 1)
        //{

        //}
        Mo result = wrapper_->setObserverForObjectCreate("CAR/MDM/START_ENGINE_REQ/RESULT");
        wrapper_->deleteObject(mdmStartSignal.distname);
        delete &mdmStartSignal;
        delete &result;
        remove("/home/mato3/OSCAR/SYS/sigs/USER_SIG.dat");

    }

}

int InsideDevicesManager::checkPredicates()
{
    Mo breakPedal = wrapper_->getObject("CAR/IDM/PEDALS/BREAK_PEDALS");
    Mo clutchPedal = wrapper_->getObject("CAR/IDM/PEDALS/CLUTCH_PEDALS");
    if(areClutchAndBreakPedalsPushed({&breakPedal, &clutchPedal}))
    {
        return 1;
    }
    /*if(isClutchPushed(&clutchPedal))
    {
        return 2;
    }
    if(isBreakPushed(&breakPedal))
    {
        return 3;
    }*/
}

bool InsideDevicesManager::areClutchAndBreakPedalsPushed(vector<Mo*> pedals)
{
    for(const auto &pedal : pedals)
    {
        if(pedal->proceduralState != "Pushed")
        {
            return false;
        }
    }
    return true;
}

void InsideDevicesManager::initISAgent()
{
    iSA_ = new IntegratedSwitchAgent(wrapper_);
    iSA_->createISObjects();


}

void InsideDevicesManager::initChairAgent()
{
    cA_ = new ChairsAgent(wrapper_);
    cA_->initialize();
}

void InsideDevicesManager::initWinSwitchAgent()
{
   Mo winSwitchMo = wrapper_->createObject("CAR/IDM/WINDOW_SWITCH_1", "Online", "Enabled");
    wrapper_->expandObject(&winSwitchMo, {"Label"}, {"FRONT_LEFT"});
    windowSwitchMos_.push_back(winSwitchMo);
    winSwitchMo = wrapper_->createObject("CAR/IDM/WINDOW_SWITCH_2", "Online", "Enabled");
    wrapper_->expandObject(&winSwitchMo, {"Label"}, {"FRONT_RIGHT"});
    windowSwitchMos_.push_back(winSwitchMo);
    winSwitchMo = wrapper_->createObject("CAR/IDM/WINDOW_SWITCH_3", "Online", "Enabled");
    wrapper_->expandObject(&winSwitchMo, {"Label"}, {"BACK_LEFT"});
    windowSwitchMos_.push_back(winSwitchMo);
    winSwitchMo = wrapper_->createObject("CAR/IDM/WINDOW_SWITCH_4", "Online", "Enabled");
    wrapper_->expandObject(&winSwitchMo, {"Label"}, {"BACK_RIGHT"});
    windowSwitchMos_.push_back(winSwitchMo);
}

void InsideDevicesManager::initLeftSiteAgent()
{
    hornMo_ = wrapper_->createObject("CAR/IDM/HORN", "Online", "Enabled");
    initWinSwitchAgent();
    initMirrorSwitchAgent();
    initStereAgent();
}

void InsideDevicesManager::initMirrorSwitchAgent()
{
    Mo mirrorSwitchMo = wrapper_->createObject("CAR/IDM/MIRROR_SWITCH", "Online", "Enabled");
    wrapper_->expandObject(&mirrorSwitchMo, {"position"}, {"NONE"});
    Mo mirrorChooserMo = wrapper_->createObject("CAR/IDM/MIRROR_SWITCH/MIRROR_CHOOSER", "Online", "Enabled");
    wrapper_->expandObject(&mirrorChooserMo, {"chosenMirror"}, {"Neutral"});
    mirroSwitchMos_.push_back(mirrorSwitchMo);
}

void InsideDevicesManager::initStereAgent()
{
    stereMo_ = wrapper_->createObject("CAR/IDM/STERE", "Online", "Idle");
    wrapper_->expandObject(&stereMo_, {"angle"}, {"0"});
}

void InsideDevicesManager::initCenterSiteAgent()
{
    cPA_ = new CardPortAgent(wrapper_);
    startButtonMo_ = wrapper_->createObject("CAR/IDM/START_BUTTON", "Online", "Off");
}
