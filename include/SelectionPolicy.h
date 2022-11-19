#pragma once

#include "Simulation.h"


/**
* Abstract class that represents a strategy algorithm
 * for selecting the next party to offer.
* */
class SelectionPolicy {
public:

    /**
     * Destructor
     */
    virtual ~SelectionPolicy() {};

    /**
     * Selects a party based on a selection strategy
     */
    virtual int select(const Simulation &sim, const Agent &agent, const int partyId1, const int partyId2) = 0;

    /***
     * Clone the selection policy
     * @return  a clone of the selection policy
     */
    virtual SelectionPolicy *clone() = 0;
};

/***
 * Extends the SelectionPolicy class.
 * Selects the neighboring party with the most mandates.
 */
class MandatesSelectionPolicy : public SelectionPolicy {
public:
    int select(const Simulation &sim, const Agent &agent, const int partyId1, const int partyId2) override;

    SelectionPolicy *clone() override;

};


/***
 * Extends the SelectionPolicy class.
 * Selects the neighboring party with the highest edge weight.
 */
class EdgeWeightSelectionPolicy : public SelectionPolicy {
public:
    int select(const Simulation &sim, const Agent &agent, const int partyId1, const int partyId2) override;

    SelectionPolicy *clone() override;


};