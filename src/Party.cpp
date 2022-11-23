#include "Party.h"
#include "JoinPolicy.h"
#include "SelectionPolicy.h"
#include "Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates),
                                                                  mJoinPolicy(jp), mState(Waiting), mTimer(0),
                                                                  mCoalition(nullptr), mAgentsOffersIds(),
                                                                  mCoalitionOptions() {
}

Party::Party(const Party &party) : mId(party.mId), mName(party.mName), mMandates(party.mMandates),
                                   mJoinPolicy(party.mJoinPolicy->clone()), mState(party.mState),
                                   mTimer(party.mTimer), mCoalition(nullptr), mAgentsOffersIds(),
                                   mCoalitionOptions() {}

Party::Party(Party &&party) : mId(party.mId), mName(party.mName), mMandates(party.mMandates),
                              mJoinPolicy(party.mJoinPolicy), mState(party.mState),
                              mTimer(party.mTimer), mCoalition(party.mCoalition), mAgentsOffersIds(),
                              mCoalitionOptions() {
    party.mJoinPolicy = nullptr;
}

Party &Party::operator=(const Party &party) {

    if (&party != this) {
        delete mJoinPolicy;
        mId = party.mId;
        mName = party.mName;
        mMandates = party.mMandates;
        mJoinPolicy = party.mJoinPolicy->clone();
        mState = party.mState;
        mTimer = party.mTimer;
        mCoalition = party.mCoalition;
        mAgentsOffersIds = party.mAgentsOffersIds;
        mCoalitionOptions = party.mCoalitionOptions;
    }
    return *this;
}

Party &Party::operator=(Party &&party) {

    if (&party != this) {
        delete mJoinPolicy;
        mId = party.mId;
        mName = party.mName;
        mMandates = party.mMandates;
        mState = party.mState;
        mTimer = party.mTimer;
        mCoalition = party.mCoalition;
        mAgentsOffersIds = party.mAgentsOffersIds;
        mCoalitionOptions = party.mCoalitionOptions;

        // swap
        mJoinPolicy = party.mJoinPolicy;
        party.mJoinPolicy = nullptr;

    }
    return *this;
}


Party::~Party() {

    if (mJoinPolicy != nullptr) {
        delete mJoinPolicy;
        mJoinPolicy = nullptr;
    }

}

State Party::getState() const {
    return mState;
}

void Party::setState(State state) {
    mState = state;
}

int Party::getMandates() const {
    return mMandates;
}

const string &Party::getName() const {
    return mName;
}

void Party::step(Simulation &s) {

    switch (mState) {
        case State::Waiting:
            // do nothing
            break;

        case State::CollectingOffers:

            // change state to joined
            if (mTimer == 3) {

                // choose the best offer
                const int bestOfferId = mJoinPolicy->join(s, mAgentsOffersIds);

                // clone agent
                Agent &agent = s.getAgents()[bestOfferId];
                Agent agentClone = Agent(s.getAgents().size(), mId, agent.getSelectionPolicy()->clone());

                // join coalition
                Coalition *coalition = s.getCoalitions()[bestOfferId];
                mCoalition = coalition;
                mCoalition->addMandates(mMandates);

                // add the cloned agent
                s.getAgents().push_back(std::move(agentClone));

                // make the created agent to perform a step
                s.getAgents().back().step(s);

                // update the step
                setState(State::Joined);
            }

            // increase timer time
            mTimer += 1;
            break;

        case State::Joined:
            // do nothing
            break;
    }
}

void Party::setCoalition(Coalition *coalition) {
    mCoalition = coalition;
}

bool Party::canOffer(int coalitionID) {
    auto it = mCoalitionOptions.find(coalitionID);
    return (it == mCoalitionOptions.end());
}

Coalition *Party::getCoalition() {
    return mCoalition;
}

const Coalition *Party::getCoalition() const {
    return mCoalition;
}

void Party::addOffer(Agent &agent, int coalitionID) {

    // add the coalition
    mCoalitionOptions.insert(coalitionID);
    mAgentsOffersIds.push_back(coalitionID);

    // change id case first one
    if (getState() == State::Waiting) {
        setState(State::CollectingOffers);
    }
}