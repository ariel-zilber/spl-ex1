#pragma once

class SelectionPolicy {
public:
    virtual int select(const Simulation &sim,const Agent &agent,const int partyId1,const int partyId2)=0;
};

class MandatesSelectionPolicy: public SelectionPolicy{
public:
     int select(const Simulation &sim,const Agent &agent,const int partyId1,const int partyId2) override;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
public:
    int select(const Simulation &sim,const Agent &agent,const int partyId1,const int partyId2) override;



};