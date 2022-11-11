#include "Agent.h"
#include "Simulation.h"
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method
    // choose party to join by selection policy
    //sim.getParty(mPartyId)
     Graph& graph=sim.getGraph();
    Party& party=graph.getParty(mPartyId);
    const State& partyState=party.getState();
    int bestPartyToOfferId=-1;
     for(int i=0;i<graph.getNumVertices();i++){
        const int weight=graph.getEdgeWeight(mPartyId,i);
        if(weight>0&&partyState==State::Waiting){
            mSelectionPolicy
            this->mSelectionPolicy()
            // waiting-> collecting
            party.setState(State::CollectingOffers);
            // todo: send id of coalition

        }
        // TODO:: handle third case!!
        if(weight>0&&partyState==State::CollectingOffers){

            // todo
        }
    }
}

