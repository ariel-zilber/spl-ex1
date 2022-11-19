#include "Simulation.h"
#include "Coalition.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mCoalitions() {
    const int numberOfAgents = mAgents.size();
    for (int agentID = 0; agentID < numberOfAgents; agentID++) {

        // initialize a coalition
        auto *coalition = new Coalition(agentID);

        //  get the party associated with the agent
        const int partyId = mAgents[agentID].getPartyId();
        Party &party=mGraph.getParty(partyId);

        // adds the party to the coalition
        const int mandatesToAdd=party.getMandates();
        coalition->addMandates(mandatesToAdd);
        party.setCoalition(coalition);

        // add the coalition to the simulation
        mCoalitions.push_back(coalition);
    }
}

void Simulation::step() {

    // Agents  perform step:
    for (auto &mAgent: mAgents) {
        mAgent.step(*this);
    }

    // Parties perform step:
    for (int i = 0; i < mGraph.getNumVertices(); i++) {
        Party &party = mGraph.getParty(i);
        party.step(*this);
    }
}

bool Simulation::shouldTerminate() const {
    bool allJoined = true;
    bool atLeast61Mandates = false;

    // condition 1 check:majority
    for (auto c: mCoalitions) {
        if (c->getTotalMandates() >= 61) {
            atLeast61Mandates = true;
        }
    }

    // condition 2 check: all joined
    for (int i = 0; i < mGraph.getNumVertices(); i++) {
        const Party &party = mGraph.getParty(i);
        if (party.getState() != State::Joined) {
            allJoined = false;
        };
    }

    // should satisfy at least one condition
    return allJoined || atLeast61Mandates;
}

const Graph &Simulation::getGraph() const {
    return mGraph;
}

Graph &Simulation::getGraph() {
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const {
    return mAgents;
}

//
vector<Agent> &Simulation::getAgents() {
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const {
    return mGraph.getParty(partyId);
}

Party &Simulation::getParty(int partyId) {
    return mGraph.getParty(partyId);
}

vector<Coalition *> Simulation::getCoalitions() {
    return mCoalitions;
}

const vector<vector<int>> Simulation::getPartiesByCoalitions() const {

    // init a return vector of parties seperated by coaltions
    vector<vector<int>> partiesByCoalitions(mCoalitions.size());

    // iterate over all agents and add the agent id to the expected coalation index
    // The result will be vector [[agent0.partyId], [agent1.partyId], ...]
    for (const auto &agent: mAgents) {
        const int agentsPartyId=agent.getPartyId();
        const Party &party = mGraph.getParty(agentsPartyId);
        const int coalitionsId = party.getCoalition()->getId();
        partiesByCoalitions[coalitionsId].push_back(agent.getPartyId());
    }

    return partiesByCoalitions;
}

Simulation::~Simulation() {
    for (auto it: mCoalitions) {
        delete it;
    }
}
