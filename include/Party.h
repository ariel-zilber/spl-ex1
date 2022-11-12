#pragma once
#include <string>
#include <vector>
#include <set>
#include "Coalition.h"
#include "Agent.h"

using std::string;
class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
//    void hasJoined();
//    receiveRequest(const Agent & agent);
    const string &getName() const;
    void setCoalition(Coalition * coalition);
    bool canOffer(int coalitionID);
    void addOffer(Agent &agent,int coalitionID);
    Coalition * getCoalition() const ;
private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mTimer;
    Coalition *mCoalition;
    std::vector<int> mAgentsOffersIds;
    std::set<int> mCoalitionOptions;

};
