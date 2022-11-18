#include "Party.h"
#include "JoinPolicy.h"
#include "Simulation.h"
Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),mTimer(0),mCoalition(
        nullptr),mAgentsOffersIds(),mCoalitionOptions()
{
    // You can change the implementation of the constructor, but not the signature!
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

//
void Party::step(Simulation &s)
{
    // TODO: implement this method
    // Waiting
    switch (mState) {
        // do nothing
        case State::Waiting:
            break;

        // do nothing
        case State::Joined:
            break;
        case State::CollectingOffers:

            mTimer+=1;

            // change state to joined
            if(mTimer==3){
                
                // choose the best offer
                const int bestOfferId=mJoinPolicy->join(s,mAgentsOffersIds);
                const int numberOfAgents=s.getAgents().size();
                 Coalition * coalition=s.getCoalitions()[bestOfferId];

                // clone agent
                Agent & agent =s.getAgents()[bestOfferId];
                Agent *agentClonePtr=agent.clone();
                const int  mAgentId=numberOfAgents+1;
                agentClonePtr->setId(mAgentId);

                // join coalition
                mCoalition=coalition;

                s.getAgents().push_back(*agentClonePtr);
                
                //
                setState(State::Waiting);

            }
            break;
    }
    // CollectingOffers
    // Joined
}

void Party::setCoalition(Coalition *coalition) {
    mCoalition=coalition;
}

bool Party::canOffer(int coalitionID) {
    auto it = mCoalitionOptions.find(coalitionID);
    return (it==mCoalitionOptions.end());
}

Coalition *Party::getCoalition()  {
    return mCoalition;
}

void Party::addOffer(Agent &agent, int coalitionID) {
    mCoalitionOptions.insert(coalitionID);
    mAgentsOffersIds.push_back(agent.getId());

    // change id case first one
    if(getState()==State::Waiting){
        setState(State::CollectingOffers);
    }


}



