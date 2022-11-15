#include "Simulation.h"
#include "Coalition.h"
Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    // You can change the implementation of the constructor, but not the signature!
    for(int agentID=0;agentID<mAgents.size();agentID++){
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

//
vector<Agent> &Simulation::getAgents() 
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
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
    for(int i=0;i<mCoalitions.size();i++){
        partiesByCoalitions.push_back(mCoalitions[i]->getPartiesIds());
    }
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return partiesByCoalitions;
}
