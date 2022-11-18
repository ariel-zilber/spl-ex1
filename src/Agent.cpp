#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
}


Agent* Agent::clone(){
    return new Agent(mAgentId,mPartyId,mSelectionPolicy->clone());
}
void  Agent::setId(int value) 
{
    mAgentId=value;
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
     Graph& graph=sim.getGraph();

    // agent finds potential neightbor parties
    int bestPartyToOfferId=-1;
    Party& party=graph.getParty(mPartyId);
    const int coalitionID=sim.getParty(mPartyId).getCoalition()->getId();
    for(int i=0;i<graph.getNumVertices();i++){
         const State& partyState=party.getState();

         // condition 1: The party is a neighbor of the party to which the agent belongs.
         const bool isNeighbors=graph.getEdgeWeight(mPartyId,i)>0;

        // condition 2:
         const bool validPartyState=(partyState==State::Waiting||partyState==State::CollectingOffers);

        // condition 3: The party is in Waiting or in CollectingOffers state
         const bool canOffer=party.canOffer(coalitionID);

        // The party did not already receive an offer from any agent from the coalition to which
        // the agent belongs. That is, if an agent from a coalition offers a party to join, other
        // agents from the same coalition should not select the party (this might be a waste of an
        // offer). When there are no parties to select from, the agent is idle
         if(isNeighbors>0&& validPartyState &&canOffer){
            bestPartyToOfferId=this->mSelectionPolicy->select(sim, *this,mPartyId,i);
        }
    }
    // choose party to offer when possible
    if(bestPartyToOfferId!=-1){
        Party& bestParty=graph.getParty(bestPartyToOfferId);
        bestParty.addOffer(*this,coalitionID);
    }


}

