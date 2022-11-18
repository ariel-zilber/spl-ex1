#pragma once

#include <vector>
 
using std::vector;


class Coalition {
public:
    Coalition(int id);
    void addParty(const int partyId);
    const std::vector<int>& getPartiesIds();
    void setTotalMandates(int value);
    int  getTotalMandates();
    int  getId() const ;
    void  setId(int value);

private:
    int mTotalMandates;
    int mId;
    std::vector<int> partiesIds;
};