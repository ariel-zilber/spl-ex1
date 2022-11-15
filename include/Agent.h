#pragma once

#include <vector>
#include "Graph.h"
class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent * clone();
    int getPartyId() const;
    int getId() const;
    void setId(int value);
    void step(Simulation &);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
