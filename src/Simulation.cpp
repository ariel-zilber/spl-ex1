#include "Simulation.h"
#include "Coalition.h"
Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) ,mCoalitions()
{
    const unsigned int numberOfAgents=mAgents.size();
    for(unsigned int agentID=0;agentID<numberOfAgents;agentID++){
        const int partyId=mAgents[agentID].getPartyId();
        Coalition *c=new Coalition(agentID);
        mGraph.getParty(partyId).setCoalition(c);
        mCoalitions.push_back(c);
    }
}

void Simulation::step()
{
    // TODO: implement this method
    // step agents:
    for(auto & mAgent : mAgents){
        mAgent.step(*this);
    }

    for(int i=0;i<mGraph.getNumVertices();i++){
        Party  party=  mGraph.getParty(i);
       party.step(*this);
    }
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

//
vector<Agent> &Simulation::getAgents() 
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

  Party &Simulation::getParty(int partyId)
{
    return mGraph.getParty(partyId);
}
vector<Coalition *>  Simulation::getCoalitions() {
    return mCoalitions;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> partiesByCoalitions;
    const unsigned int numberOfCoalitions=mCoalitions.size();
    for(unsigned int i=0;i<numberOfCoalitions;i++){
        partiesByCoalitions.push_back(mCoalitions[i]->getPartiesIds());
    }
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return partiesByCoalitions;
}
