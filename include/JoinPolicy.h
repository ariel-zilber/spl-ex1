#pragma once

class JoinPolicy {
    virtual int join(Simulation &sim,std::vector<int> agentIdVector) =0;

};

class MandatesJoinPolicy : public JoinPolicy {
     int join(Simulation &sim,std::vector<int> agentIdVector) override;

};

class LastOfferJoinPolicy : public JoinPolicy {
    int join(Simulation &sim,std::vector<int> agentIdVector) override;


};