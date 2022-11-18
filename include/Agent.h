#pragma once

#include <vector>
#include "Graph.h"
class SelectionPolicy;
class Simulation;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(const Agent& agent);
    Agent( Agent&& agent);
    Agent& operator=(const Agent& other);
    Agent& operator=(Agent&& other)  ;
    ~Agent();
    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    SelectionPolicy * getSelectionPolicy();

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
