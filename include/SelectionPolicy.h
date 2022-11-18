#pragma once
#include "Simulation.h"

class SelectionPolicy {
public:
    virtual int select(const Simulation &sim,const Agent &agent,const int partyId1,const int partyId2)=0;
    virtual SelectionPolicy * clone()=0;
    virtual ~SelectionPolicy(){};  
};

class MandatesSelectionPolicy: public SelectionPolicy{
public:
     int select(const Simulation &sim,const Agent &agent,const int partyId1,const int partyId2) override;
      SelectionPolicy * clone() override;

};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
public:
    int select(const Simulation &sim,const Agent &agent,const int partyId1,const int partyId2) override;
    SelectionPolicy * clone() override;



};