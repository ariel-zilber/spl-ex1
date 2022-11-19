#pragma once

#include "Simulation.h"


/**
* An abstract class that represents a strategy algorithm
* for choosing which offer to accept and which coalition
* to join.
* */
class JoinPolicy {
public:
    // Destructors:
    virtual ~JoinPolicy() {};

    // methods:
    /***
     *
     * @param sim
     * @param coalitionIdVector
     * @return
     */
    virtual int join(Simulation &sim, std::vector<int> coalitionIdVector) = 0;

    /***
     * Clone the join policy
     * @return  a clone of the join policy
     */
    virtual JoinPolicy *clone() = 0;


};

/***
 * Extends the JoinPolicy class.
 * Selects the coalition with the largest number of mandates.
 *  Note that this refers to the number of mandates in the
 *  iteration when the offer is accepted.
 *  If the number of mandates is not unique, join the coalition that offered first.
 */
class MandatesJoinPolicy : public JoinPolicy {
public:

    int join(Simulation &sim, std::vector<int> coalitionIdVector) override;

    JoinPolicy *clone() override;

};

/***
 * Extends the JoinPolicy class.
 * Selects the coalition that made the last offer.
 */
class LastOfferJoinPolicy : public JoinPolicy {
public:
    int join(Simulation &sim, std::vector<int> coalitionIdVector) override;

    JoinPolicy *clone() override;


};