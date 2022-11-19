#include "SelectionPolicy.h"
#include <iostream>


int  EdgeWeightSelectionPolicy::select(const Simulation &sim, const Agent &agent, const int partyId1, const int partyId2) {

    int agentPartyId = agent.getPartyId();
    int weight1 = sim.getGraph().getEdgeWeight(agentPartyId, partyId1);
    int weight2 = sim.getGraph().getEdgeWeight(agentPartyId, partyId2);
    if (weight1 >= weight2) {
        return partyId1;
    } else {
        return partyId2;
    }

};


int MandatesSelectionPolicy::select(const Simulation &sim, const Agent &agent, const int partyId1, const int partyId2) {

    const int mandatesParty1 = sim.getParty(partyId1).getMandates();
    const int mandatesParty2 = sim.getParty(partyId2).getMandates();
    if (mandatesParty1 >= mandatesParty2) {
        return partyId1;
    } else { return partyId2; }
}



SelectionPolicy* EdgeWeightSelectionPolicy::clone(){
    return new EdgeWeightSelectionPolicy();
}

SelectionPolicy* MandatesSelectionPolicy::clone(){
    return new MandatesSelectionPolicy();
}