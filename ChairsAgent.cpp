#include "ChairsAgent.hpp"

ChairsAgent::ChairsAgent(IDBWrapper* wrapper) : wrapper_(wrapper)
{
    //ctor
}

ChairsAgent::~ChairsAgent()
{
    //dtor
}

void ChairsAgent::initialize()
{
    Logger::saveToFile("IDM/DBG: ChairsAgent: initialize");
    chairContainterMo_ = wrapper_->createObject("CAR/IDM/CHAIRS", "Online", "Enabled");
    Logger::saveToFile("IDM/DBG: ChairsAgent: chairsContainer created");
    createChairObjects();
}

void ChairsAgent::createChairObjects()
{
    int i = 1;
    for(const auto &label : chairLabels_)
    {
        Mo chairMo = wrapper_->createObject("CAR/IDM/CHAIRS/CHAIR_" + to_string(i), "Online", "Enabled");
        wrapper_->expandObject(&chairMo, {"Label"}, {label});
        Mo belt = wrapper_->createObject(chairMo.distname + "/BELT", "Online", "Empty");
        chairControllerSwitch_ = wrapper_->createObject(chairMo.distname + "/SWITCH", "Online", "Enabled");
        wrapper_->expandObject(&chairControllerSwitch_, {"position"}, {"NONE"});
        Mo axisChooser = wrapper_->createObject(chairMo.distname + "/AXIS_CHOOSER", "Online", "Enabled");
        wrapper_->expandObject(&axisChooser, {"position"}, {"NONE"});

        chairMos_.push_back(chairMo);
        i++;
    }
}

