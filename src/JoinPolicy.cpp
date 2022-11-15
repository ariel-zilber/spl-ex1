#include "../include/JoinPolicy.h"
#include "../include/Simulation.h"

int MandatesJoinPolicy::join(Simulation &sim, std::vector<int> agentIdVector) {
    
    int maxMandateCount=0;
    int bestPartyId=0;
    for(auto currAgentId:agentIdVector){
     const int currPartyId=sim.getAgents()[currAgentId].getPartyId();
     const int currCountMandate=sim.getGraph().getMandates(currPartyId);
     if(currCountMandate>maxMandateCount){
        maxMandateCount=currCountMandate;
        bestPartyId=currPartyId;
     }
    }
    return bestPartyId;
}

int LastOfferJoinPolicy::join(Simulation &sim, std::vector<int> agentIdVector) {
    return agentIdVector.back();
}
