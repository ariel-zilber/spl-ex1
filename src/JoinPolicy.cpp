#include "JoinPolicy.h"
#include "Simulation.h"

#include <iostream>

int MandatesJoinPolicy::join(Simulation &sim, std::vector<int> coalitionIdVector) {
    int bestCoalitionId = 0;
    int currMaxMandates = -1;
    for (auto currId: coalitionIdVector) {
        const int currTotalMandates = sim.getCoalitions()[currId]->getTotalMandates();
        if (currTotalMandates > currMaxMandates) {
            currMaxMandates = currTotalMandates;
            bestCoalitionId = currId;
        }
    }
    return bestCoalitionId;

}

int LastOfferJoinPolicy::join(Simulation &sim, std::vector<int> coalitionIdVector) {
    return coalitionIdVector.back();
}

JoinPolicy *MandatesJoinPolicy::clone() {
    return new MandatesJoinPolicy();
}

JoinPolicy *LastOfferJoinPolicy::clone() {
    return new LastOfferJoinPolicy();
}
