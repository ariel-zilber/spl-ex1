#pragma once

class SelectionPolicy {
    virtual int select(const Simulation &sim,const int partyId1,const int partyId2)=0;
};

class MandatesSelectionPolicy: public SelectionPolicy{

     int select(const Simulation &sim,const int partyId1,const int partyId2) override{
         const int mandatesParty1=sim.getParty(partyId1).getMandates();
         const int mandatesParty2=sim.getParty(partyId2).getMandates();
         if(mandatesParty1>=mandatesParty2){
             return partyId1;
         }else{return  partyId2;}
     };


};

class EdgeWeightSelectionPolicy: public SelectionPolicy{

    int select(const Simulation &sim,const int partyId1,const int partyId2) override{
        int weight=sim.getGraph().getEdgeWeight(partyId1,partyId2);

    };

};