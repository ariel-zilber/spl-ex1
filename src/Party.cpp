#include <iostream>
#include "Party.h"
#include "JoinPolicy.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),mTimer(0),mCoalition(
        nullptr),mAgentsOffersIds(),mCoalitionOptions()
{
    std::cout<<"[DEBUG]"<<"cntr: Party()(id:"<<mId<<",state:"<<mState<<",mTimer:"<<mTimer<<")"<<std::endl;

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
    std::cout<<"[DEBUG]"<<"~Party()(id:"<<mId<<",state:"<<mState<<",mTimer:"<<mTimer<<")"<<std::endl;

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
    std::cout<<"[DEBUG]"<<"Party::step()(id:"<<mId<<",state:"<<mState<<",mTimer:"<<mTimer<<")"<<std::endl;

    // TODO: implement this method
    // Waiting
    switch (mState) {
        // do nothing
        case State::Waiting:
            std::cout<<"[DEBUG]"<<"Party::step()"<<"(id:"<<mId<<",Waiting"<<std::endl;

            break;

        case State::CollectingOffers:
            std::cout<<"[DEBUG]"<<"Party::step():CollectingOffers:"<<mTimer<<std::endl;

            // change state to joined
            if(mTimer==3){
                // choose the best offer
                const int bestOfferId=mJoinPolicy->join(s,mAgentsOffersIds);
                std::cout<<"[DEBUG]"<<"Party::step():Cloning started !!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
                std::cout<<"[DEBUG]"<<"Party::step():bestOfferId:"<<bestOfferId<<std::endl;

                const int numberOfAgents=s.getAgents().size();
                 Coalition * coalition=s.getCoalitions()[bestOfferId];

                // clone agent
                Agent & agent =s.getAgents()[bestOfferId];
                Agent agentClone=Agent(numberOfAgents,mId,agent.getSelectionPolicy()->clone());

                std::cout<<"[DEBUG]"<<"Party::step():Cloning done !!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
                std::cout<<"[DEBUG]"<<"Party::step():Cloning update id&&party ID !!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;

                // join coalition
                mCoalition=coalition;
                std::cout<<"[DEBUG]"<<"Party::step():Cloning  set coaliotn !!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
                std::cout<<"[DEBUG]"<<"Party::step():Cloning  mCoalition->getTotalMandates():"<<mCoalition->getTotalMandates()<<" !!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
                mCoalition->setTotalMandates(mCoalition->getTotalMandates()+mMandates);
                std::cout<<"[DEBUG]"<<"Party::step():Cloning  add agent !!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;

                s.getAgents().push_back(std::move(agentClone));
                std::cout<<"[DEBUG]"<<"Party::step() set state (Collecting-> Joined) !!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
                setState(State::Joined);
                std::cout<<"[DEBUG]"<<"Party::step()(id"<<mId<<",mCoalition:"<<mCoalition->getId()<<")"<<std::endl;
                s.getAgents().back().step(s);

            }
            mTimer+=1;
            break;
        case State::Joined:
            std::cout<<"[DEBUG]"<<"Party::step():Joined"<<std::endl;

            break;
    }
    std::cout<<"[DEBUG]"<<"Party::step():mtimer:"<<mTimer<<std::endl;

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


