#include "JoinPolicy.h"
#include "Simulation.h"
#include "JoinPolicy.h"

#include <iostream>

int MandatesJoinPolicy::join(Simulation &sim, std::vector<int> coalitionIdVector) {
    std::cout<<"[DEBUG]"<<"MandatesJoinPolicy"<<std::endl;
    int bestCoalitionId=0;
    int currMaxMandates=-1;
    for(auto currId:coalitionIdVector){
        const int currTotalMandates=sim.getCoalitions()[currId]->getTotalMandates();
        if(currTotalMandates>currMaxMandates){
            currMaxMandates=currTotalMandates;
            bestCoalitionId=currId;
        }
        
    }
    return bestCoalitionId;

}

int LastOfferJoinPolicy::join(Simulation &sim, std::vector<int> coalitionIdVector) {
    std::cout<<"[DEBUG]"<<"LastOfferJoinPolicy"<<std::endl;
    for(auto i:coalitionIdVector){
        std::cout<<"[DEBUG]"<<"LastOfferJoinPolicy:"<<i<<std::endl;

    }
    return coalitionIdVector.back();
}

JoinPolicy *MandatesJoinPolicy::clone() {
    return new MandatesJoinPolicy();
}

JoinPolicy *LastOfferJoinPolicy::clone() {
    return new LastOfferJoinPolicy();
}
