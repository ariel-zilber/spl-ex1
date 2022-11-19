#include <iostream>
#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"
#include "Coalition.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),
                                                                           mSelectionPolicy(selectionPolicy) {
}

Agent::Agent(const Agent &agent) : mAgentId(agent.mAgentId), mPartyId(agent.mPartyId),
                                   mSelectionPolicy(agent.mSelectionPolicy->clone()) {

}

Agent::Agent(Agent &&agent) : mAgentId(agent.mAgentId), mPartyId(agent.mPartyId) {

    // swap
    mSelectionPolicy = agent.mSelectionPolicy;
    agent.mSelectionPolicy = nullptr;
}

Agent &Agent::operator=(const Agent &other) {

    // self check
    if (&other != this) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy->clone();
    }
    return *this;
}

Agent &Agent::operator=(Agent &&other) {

    // self check
    if (&other != this) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy;
        other.mSelectionPolicy = nullptr;
    }
    return *this;
}


Agent::~Agent() {

    if (mSelectionPolicy != nullptr) {
        delete mSelectionPolicy;
        mSelectionPolicy = nullptr;
    }
}


int Agent::getId() const {
    return mAgentId;
}

int Agent::getPartyId() const {
    return mPartyId;
}

void Agent::step(Simulation &sim) {

    // choose party to join by selection policy
    Graph &graph = sim.getGraph();

    // agent finds potential neightbor parties
    int bestPartyToOfferId = mPartyId;
    const int coalitionID = sim.getParty(mPartyId).getCoalition()->getId();

    for (auto i = 0; i < graph.getNumVertices(); i++) {

        // condition 1: The party is a neighbor of the party to which the agent belongs.
        const bool isNeighbors = graph.getEdgeWeight(mPartyId, i) > 0;
        Party &party = graph.getParty(i);
        const State &partyState = party.getState();

        // condition 2:
        const bool validPartyState = (partyState == State::Waiting || partyState == State::CollectingOffers);

        // condition 3: The party is in Waiting or in CollectingOffers state
        const bool canOffer = party.canOffer(coalitionID);

        // check whenever can choose the party
        if (isNeighbors && validPartyState && canOffer) {
            bestPartyToOfferId = this->mSelectionPolicy->select(sim, *this, bestPartyToOfferId, i);
        }
    }

    // choose party to offer when possible
    if (bestPartyToOfferId != mPartyId) {
        Party &bestParty = graph.getParty(bestPartyToOfferId);
        bestParty.addOffer(*this, coalitionID);
    }
}

SelectionPolicy *Agent::getSelectionPolicy() {
    return mSelectionPolicy;
}
