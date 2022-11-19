#include <iostream>
#include "Party.h"
#include "JoinPolicy.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),mTimer(0),mCoalition(
        nullptr),mAgentsOffersIds(),mCoalitionOptions()
{

}

Party::Party(const Party &party)  : mId(party.mId), mName(party.mName), mMandates(party.mMandates), mState(party.mState),mTimer(party.mTimer),mCoalition(
        nullptr),mAgentsOffersIds(),mCoalitionOptions(){
    mJoinPolicy=party.mJoinPolicy->clone();
}

Party::Party(Party &&party): mId(party.mId), mName(party.mName), mMandates(party.mMandates), mState(party.mState),mTimer(party.mTimer),mCoalition(
        party.mCoalition),mAgentsOffersIds(),mCoalitionOptions(){
    // swap
    mJoinPolicy=party.mJoinPolicy;
    party.mJoinPolicy= nullptr;
}

Party &Party::operator=(const Party &party) {

    if(&party!= this){

        mId=party.mId;
        mName=party.mName;
        mMandates=party.mMandates;
        //
        mJoinPolicy=party.mJoinPolicy->clone();
        mState=party.mState;
        mTimer=party.mTimer;
        mCoalition=party.mCoalition;
        mAgentsOffersIds=party.mAgentsOffersIds;
        mCoalitionOptions=party.mCoalitionOptions;
    }
    return *this;
}

Party &Party::operator=(Party &&party) {


    if(&party!= this){

        mId=party.mId;
        mName=party.mName;
        mMandates=party.mMandates;
        mState=party.mState;
        mTimer=party.mTimer;
        mCoalition=party.mCoalition;
        mAgentsOffersIds=party.mAgentsOffersIds;
        mCoalitionOptions=party.mCoalitionOptions;

        mJoinPolicy=party.mJoinPolicy;
        party.mJoinPolicy= nullptr;

    }
    return *this;
}


Party::~Party()
{

    if(mJoinPolicy!= nullptr){
        delete mJoinPolicy;
        mJoinPolicy=nullptr;
    }
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

        case State::CollectingOffers:
            // change state to joined
            if(mTimer==3){
                // choose the best offer
                const int bestOfferId=mJoinPolicy->join(s,mAgentsOffersIds);

                const int numberOfAgents=s.getAgents().size();
                 Coalition * coalition=s.getCoalitions()[bestOfferId];

                // clone agent
                Agent & agent =s.getAgents()[bestOfferId];
                Agent agentClone=Agent(numberOfAgents,mId,agent.getSelectionPolicy()->clone());


                // join coalition
                mCoalition=coalition;
                mCoalition->setTotalMandates(mCoalition->getTotalMandates()+mMandates);
                s.getAgents().push_back(std::move(agentClone));
                setState(State::Joined);
                s.getAgents().back().step(s);
            }
            mTimer+=1;
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

Coalition *Party::getCoalition()  {
    return mCoalition;
}

const Coalition *Party::getCoalition()  const {
    return mCoalition;
}
void Party::addOffer(Agent &agent, int coalitionID) {
    mCoalitionOptions.insert(coalitionID);
    mAgentsOffersIds.push_back(coalitionID);

    // change id case first one
    if(getState()==State::Waiting){
        setState(State::CollectingOffers);
    }


}


