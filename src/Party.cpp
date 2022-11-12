#include "Party.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),mTimer(0),mCoalition(
        nullptr),mAgentsOffersIds()
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

void Party::step(Simulation &s)
{
    // TODO: implement this method
    // Waiting
    switch (mState) {
        case State::CollectingOffers:

            mTimer+=1;

            // change state to joined
            if(mTimer==3){

            }
            break;
        case State::Waiting:
            break;
        case State::Joined:
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

Coalition *Party::getCoalition() const {
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
