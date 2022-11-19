#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;

/**
* This class is responsible for managing the simulation resources and
 * making simulation steps as described in the Assignment 1  pdf
 * instruction file
* */
class Simulation {
public:
    // Constructors:
    /**
     *  Creates a new Simulation object as defined in the exercise description
     * @param dimention
     * @param steps The total numbre of steps in the fractal creation
     */
    Simulation(Graph g, vector<Agent> agents);

    /**
     * Destructor
     */
    ~Simulation();

    // Methods:
    /***
     * main action of the program
     */
    void step();

    /***
     *   Check whenever the program should finish
     */
    bool shouldTerminate() const;

    /***
     *   Non const getter for simulations' graph
     */
    Graph &getGraph();

    /***
     *   Const getter for simulations' graph
     */
    const Graph &getGraph() const;

    /***
     *   Non const getter for agents vector
     */
    vector<Agent> &getAgents();

    /***
     *   Const getter for agents vector
     */
    const vector<Agent> &getAgents() const;


    /***
     *   Non const getter for party by id
     *   @param partyId id of party
     */
    Party &getParty(int partyId);


    /***
     *   Const getter for party by id
     *   @param partyId id of party
     */
    const Party &getParty(int partyId) const;


    /***
     *   This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
     *    At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
     *   @return vector of vector of parties seperated by coalitions
     */
    const vector<vector<int>> getPartiesByCoalitions() const;

    /***
     *  Getter for coalition vector
     * @return
     */
    vector<Coalition *> getCoalitions();

private:

    // Data members:

    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition *> mCoalitions;
};
