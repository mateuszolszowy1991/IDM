#include "CardPortAgent.hpp"

CardPortAgent::CardPortAgent(IDBWrapper* wrapper) : wrapper_(wrapper)
{
    Logger::saveToFile("IDM/INF: CardPortAgent: start");
    cardPortMo_ = wrapper_->createObject("CAR/IDM/CARD_PORT", "Online", "Empty");
    //waitForCard();
}

CardPortAgent::~CardPortAgent()
{
    Logger::saveToFile("IDM/INF: CardPortAgent: teardown");
}
//Should be started when CAR is Ready_For_Run
void CardPortAgent::waitForCard()
{
    while(!isCardInserted())
    {
        continue;
    }
    Logger::saveToFile("IDM/INF: CardPortAgent: waitForCard: card has been inserted");
    wrapper_->setProceduralState(&cardPortMo_, "Ready");
}

bool CardPortAgent::isCardInserted()
{
    //TODO file checking for signal
    return false;
}
