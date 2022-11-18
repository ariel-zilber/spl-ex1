#include <iostream>
#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"
#include "Coalition.h"

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

void  Agent::setPartyId(int value)
{
    mPartyId=value;
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

    // choose party to join by selection policy
     Graph& graph=sim.getGraph();

    // agent finds potential neightbor parties
    int bestPartyToOfferId=-1;
    const int coalitionID=sim.getParty(mPartyId).getCoalition()->getId();
    std::cout<<"[DEBUG]"<<"Agent::step()(id:"<<mAgentId<<",partyID:"<<mPartyId<<",coalitionID:"<<coalitionID<<")"<<std::endl;

    for(int i=0;i<graph.getNumVertices();i++){

         // condition 1: The party is a neighbor of the party to which the agent belongs.
         const bool isNeighbors=graph.getEdgeWeight(mPartyId,i)>0;
        Party& party=graph.getParty(i);
        const State& partyState=party.getState();

        // condition 2:
         const bool validPartyState=(partyState==State::Waiting||partyState==State::CollectingOffers);

        // condition 3: The party is in Waiting or in CollectingOffers state
         const bool canOffer=party.canOffer(coalitionID);
        std::cout<<"[DEBUG]"<<"Agent::step()(index:"<<i<<",isNeighbors:"<<isNeighbors<<",validPartyState:"<<validPartyState<<",canOffer:"<<canOffer<<")"<<std::endl;

        // The party did not already receive an offer from any agent from the coalition to which
        // the agent belongs. That is, if an agent from a coalition offers a party to join, other
        // agents from the same coalition should not select the party (this might be a waste of an
        // offer). When there are no parties to select from, the agent is idle
         if(isNeighbors&& validPartyState &&canOffer){
            bestPartyToOfferId=this->mSelectionPolicy->select(sim, *this,bestPartyToOfferId,i);
        }
    }



    // choose party to offer when possible
    if(bestPartyToOfferId!=-1){
        std::cout<<"[DEBUG]"<<"Agent::step() ofering!!!!!! (id:"<<mAgentId<<",bestPartyToOfferId:"<<bestPartyToOfferId<<",coalitionID:"<<coalitionID<<")"<<std::endl;
        Party& bestParty=graph.getParty(bestPartyToOfferId);
        bestParty.addOffer(*this,coalitionID);
    }else{
        std::cout<<"[DEBUG]"<<"Agent::step() NO offer ************"<<std::endl;

    }


}

