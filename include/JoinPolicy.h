#pragma once

class JoinPolicy {
    public:
    virtual int join(Simulation &sim,std::vector<int> agentIdVector) =0;

};

class MandatesJoinPolicy : public JoinPolicy {
    public:

     int join(Simulation &sim,std::vector<int> agentIdVector) override;

};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
    int join(Simulation &sim,std::vector<int> agentIdVector) override;


};