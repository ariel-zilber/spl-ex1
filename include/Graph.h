#pragma once

#include <vector>
#include "Party.h"

class Party;

using std::vector;

/**
* This class is represented by an adjacency matrix (edges) and parties vector
* (vertices).
*  The graph is undirected, it can be  assumed that the matrix is symmetric.
*  An edge exists if and only if the weight is greater than 0.
* */
class Graph {
public:
    // Constructors:

    Graph(vector<Party> vertices, vector<vector<int>> edges);

    // Methods:

    /***
     *   Const getter for number of mandates of specific party(by party id)
     *   @param partyId
     *   @return number of mandates
     */
    int getMandates(int partyId) const;

    /***
     *   Const getter to get edge weight of two parties(nodes)
     *   @param v1
     *   @param v2
     *   @return edge weigh
     */
    int getEdgeWeight(int v1, int v2) const;

    /***
     *   Const getter for number of vertices in the graph
     *   @return number of vertices
     */
    int getNumVertices() const;

    /***
     *   Non const getter for a party in the graph(by party id)
     *   @param partyId
     *   @return party
     */
    Party &getParty(int partyId);

    /***
     *   Const getter for a party in the graph(by party id)
     *   @param partyId
     *   @return party
     */
    const Party &getParty(int partyId) const;

private:


    // Data members:

    vector<Party> mVertices;
    vector<vector<int>> mEdges;
};
