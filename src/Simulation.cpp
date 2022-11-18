#include <iostream>
#include "Simulation.h"
#include "Coalition.h"
Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) ,mCoalitions()
{
    const unsigned int numberOfAgents=mAgents.size();
    for(unsigned int agentID=0;agentID<numberOfAgents;agentID++){
        const int partyId=mAgents[agentID].getPartyId();
        Coalition *c=new Coalition(agentID);
        mGraph.getParty(partyId).setCoalition(c);
        const int numMandates=mGraph.getParty(partyId).getMandates();
        c->setTotalMandates(numMandates);
        mCoalitions.push_back(c);
    }
}

void Simulation::step()
{
    // TODO: implement this method
    std::cout<<"[DEBUG]"<<"Simulation::step():( num agents:"<<mAgents.size()<<")"<<std::endl;
    // step agents:
    for(auto & mAgent : mAgents){
        mAgent.step(*this);
    }

    for(int i=0;i<mGraph.getNumVertices();i++){
        Party  &party=  mGraph.getParty(i);
       party.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    bool allJoined= true;
    bool atleast61Mandates= false;

    // majority check
    for(auto c:mCoalitions){
        if(c->getTotalMandates()>=61){
            atleast61Mandates=true;
        }
    }

    // all joined check
    for(int i=0;i<mGraph.getNumVertices();i++){
        Party  party=  mGraph.getParty(i);
        if (party.getState()!=State::Joined){
            allJoined= false;
        };
    }
    std::cout<<"[DEBUG]"<<"Simulation::shouldTerminate():( allJoined:"<<allJoined<<"|,atleast61Mandates:"<<atleast61Mandates<<")"<<std::endl;


    return allJoined||atleast61Mandates;
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
    vector<vector<int>> partiesByCoalitions(mCoalitions.size());
    for(auto agent:mAgents){
        const Party &party=mGraph.getParty(agent.getPartyId());
        const int coalitionsId=party.getCoalition()->getId();
        partiesByCoalitions[coalitionsId].push_back(agent.getPartyId());
    }

    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return partiesByCoalitions;
}
