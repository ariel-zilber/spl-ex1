#include "Party.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),mTimer(0)
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
