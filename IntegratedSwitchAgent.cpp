#include "IntegratedSwitchAgent.hpp"

IntegratedSwitchAgent::IntegratedSwitchAgent(IDBWrapper* wrapper) : wrapper_(wrapper)
{
    //ctor
}

IntegratedSwitchAgent::~IntegratedSwitchAgent()
{
    //dtor
}
void IntegratedSwitchAgent::createISObjects()
{
    intSw1_ = wrapper_->createObject("CAR/IDM/INTEGRATED_SWITCH_1", "Online", "Enabled");
    wrapper_->expandObject(&intSw1_, {"Label", "position"}, {"LIGHTS", "off"});
    intSw2_ = wrapper_->createObject("CAR/IDM/INTEGRATED_SWITCH_2", "Online", "Enabled");
    wrapper_->expandObject(&intSw2_, {"Label", "position"}, {"WIPERS", "auto"});
}
