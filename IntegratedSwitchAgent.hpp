#ifndef INTEGRATEDSWITCHAGENT_H
#define INTEGRATEDSWITCHAGENT_H
#include "IDBWrapper.hpp"

class IntegratedSwitchAgent
{
    public:
        IntegratedSwitchAgent(IDBWrapper* wrapper);
        virtual ~IntegratedSwitchAgent();
        void createISObjects();
    protected:

    private:
        IDBWrapper* wrapper_;
        Mo intSw1_;
        Mo intSw2_;
};

#endif // INTEGRATEDSWITCHAGENT_H
