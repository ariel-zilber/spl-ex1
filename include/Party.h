#pragma once

#include <string>
#include <vector>
#include <set>
#include "Coalition.h"
#include "Agent.h"

using std::string;

class JoinPolicy;

class Simulation;

class Coalition;

class Agent;

enum State {
    Waiting,
    CollectingOffers,
    Joined
};

/**
* This class  represents a vertex in the graph.
*  Each party has an id, name, number of mandates, join policy
*  and party state
* */
class Party {
public:
    // Constructors:

    /**
     *  Creates a new Party
     *  @param id the id of the party
     *  @param name the name of the party
     *  @param mandates the number of mandates of the party
     *  @param JoinPolicy the  join policy of the party
     */
    Party(int id, string name, int mandates, JoinPolicy *);

    /***
     * Copy constructor of the party
     * @param party the party to copy
     */
    Party(const Party &party);

    /***
     * Move constructor of the party
     * @param party the party to move
     */
    Party(Party &&party);

    // Destructors:

    /**
     * Destructor
     */
    ~Party();

    // Methods:

    /***
     * Copy operator overload
     * @param party the party to copy
     */
    Party &operator=(const Party &party);

    /***
     * Move operator overload
     * @param party the party to move
     */
    Party &operator=(Party &&party);

    /***
     *   Const getter for the state of the party
     *   @return state of the party
     */
    State getState() const;

    /***
     *   Setter for a state of the  party
     *   @param state the updated state of the party
     */
    void setState(State state);

    /***
     *   Const getter for a number of mandates of the party
     *   @return number of mandates of the party
     */
    int getMandates() const;

    /***
     * Main action of the party.See step in aassigment  1 pdf file
     * @param s  associated simulation
     */
    void step(Simulation &s);


    /***
     *   Const getter for a name of the party
     *   @return name of the party
     */
    const string &getName() const;


    /***
     * Checks whenever the party can recieve an offer from a coalition
     * (checked by coaltion id)
     * @param coalitionID
     * @return whenever can recieve an offer from a coalition or not
     */
    bool canOffer(int coalitionID);

    /**
     * Adds an offer th a party
     * @param agent
     * @param coalitionID
     */
    void addOffer(Agent &agent, int coalitionID);

    /***
     *   Non const getter for a parties coalition
     *   @return the parties coalition
     */
    Coalition *getCoalition();


    /***
     *   Const getter for a parties coalition
     *   @return the parties coalition
     */
    const Coalition *getCoalition() const;

    /***
     *   Non const setter for a parties coalition
     *   @param coalition a pointer to a coalition
     */
    void setCoalition(Coalition *coalition);

private:
    // Data members:

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
