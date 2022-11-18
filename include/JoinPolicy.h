#pragma once
#include "Simulation.h"

class JoinPolicy {
    public:
    virtual int join(Simulation &sim,std::vector<int> coalitionIdVector) =0;
    virtual JoinPolicy * clone()=0;
    virtual ~JoinPolicy(){};

};

class MandatesJoinPolicy : public JoinPolicy {
    public:

     int join(Simulation &sim,std::vector<int> coalitionIdVector) override;
    JoinPolicy * clone() override;

};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
    int join(Simulation &sim,std::vector<int> coalitionIdVector) override;
    JoinPolicy * clone() override;


};