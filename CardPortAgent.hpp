#ifndef CARDPORTAGENT_H
#define CARDPORTAGENT_H
#include "IDBWrapper.hpp"
#include "Logger.hpp"

class CardPortAgent
{
    public:
        CardPortAgent(IDBWrapper* wrapper);
        virtual ~CardPortAgent();
        void waitForCard();
    protected:

    private:
        IDBWrapper* wrapper_;
        Mo cardPortMo_ ;

        bool isCardInserted();
};

#endif // CARDPORTAGENT_H
