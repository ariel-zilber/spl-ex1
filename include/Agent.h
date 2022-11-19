#pragma once

#include <vector>
#include "Graph.h"

class SelectionPolicy;

class Simulation;


/**
 *
* This class has agentId, partyId (each agent associated with a single party), and
* selection policy.
* In each step, an agent is trying to select a neighboring party (in the graph)
* using SelectionPolicy::select(...) and offers the party to join its coalition.
* */
class Agent {
public:
    // Constructors:

    /**
     *  Creates a new Agent
     *  @param agentId id of the agent
     *  @param partyId id of the agents party
     *  @param selectionPolicy the selection policy of the agent
     */
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    /***
     *  Copy constructor of the Agent
     * @param agent the agent to copy
     */
    Agent(const Agent &agent);

    /***
     * Move constructor of the Agent
     * @param agent the agent to copy
     */
    Agent(Agent &&agent);

    /***
     * Copy operator overload
     * @param agent the agent to copy
     */
    Agent &operator=(const Agent &other);

    /***
     * Move operator overload
     * @param agent the agent to move
     */
    Agent &operator=(Agent &&other);

    // Destructors:
    /**
     * Destructor
     */
    ~Agent();


    // Methods:
    /***
     *   Const getter for id of the agents party
     *   @return id of the agents party
     */
    int getPartyId() const;

    /***
     *   Const getter for id of the agent
     *   @return id of the agent
     */
    int getId() const;

    /***
     *   main action of the agent
     */
    void step(Simulation &);

    /***
     *   Getter for id of the agent
     *   @return selection policy of the party
     */
    SelectionPolicy *getSelectionPolicy();

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
