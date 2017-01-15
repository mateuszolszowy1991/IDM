#ifndef CHAIRSAGENT_H
#define CHAIRSAGENT_H
#include "IDBWrapper.hpp"
#include <vector>
#include <string>

using namespace std;
class ChairsAgent
{
    public:
        ChairsAgent(IDBWrapper* wrapper);
        virtual ~ChairsAgent();
        void initialize();
    protected:

    private:
        IDBWrapper* wrapper_;
        Mo chairContainterMo_;
        Mo chairControllerSwitch_;
        vector<Mo> chairMos_;
        vector<string> chairLabels_ = {"FRONT_LEFT", "FRONT_RIGHT", "BACK_LEFT", "BACK_RIGHT", "CENTER"};

        void createChairObjects();
};

#endif // CHAIRSAGENT_H
