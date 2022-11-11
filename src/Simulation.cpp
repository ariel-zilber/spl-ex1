#include "Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    // You can change the implementation of the constructor, but not the signature!
}

void Simulation::step()
{
    // TODO: implement this method
    // step agents:
    for(int i=0;i<mAgents.size();i++){
        mAgents[i].step(*this);
    }

    // for each agent
    // do step
    // step parties:
    // for every parry
    for(int i=0;i<mGraph.getNumVertices();i++){
        Party  party=  mGraph.getParty(i);
       party.step(*this);
    }
    // do step
}

bool Simulation::shouldTerminate() const
{
    // TODO implement this method
    return true;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}
 Graph &Simulation::getGraph()
{
    return mGraph;
}
const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return vector<vector<int>>();
}
