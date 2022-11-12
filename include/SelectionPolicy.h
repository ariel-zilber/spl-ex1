#pragma once

class SelectionPolicy {
public:
    virtual int select(const Simulation &sim,const Agent &agent,const int partyId1,const int partyId2)=0;
};

class MandatesSelectionPolicy: public SelectionPolicy{
public:

    int select(const Simulation &sim,const Agent &agent,const int  agentId,const int partyId1,const int partyId2) override{
         const int mandatesParty1=sim.getParty(partyId1).getMandates();
         const int mandatesParty2=sim.getParty(partyId2).getMandates();
         if(mandatesParty1>=mandatesParty2){
             return partyId1;
         }else{return  partyId2;}
     };


};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
public:

    int select(const Simulation &sim,const Agent &agent,const int partyId1,const int partyId2) override{
       const int agentPartyId=agent.getPartyId();
        int weight1=sim.getGraph().getEdgeWeight(agentPartyId, partyId1);
        int weight2=sim.getGraph().getEdgeWeight(agentPartyId, partyId2);
        if(weight1>=weight2){
            return partyId1;
        }else{
            return partyId2;
        }

    };

};