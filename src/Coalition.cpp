#include "Coalition.h"
Coalition::Coalition(int id):mTotalMandates(0),mId(id),partiesIds() {

}

void Coalition::addParty(const int partyId){
    this->partiesIds.push_back(partyId);
}

const std::vector<int>& Coalition::getPartiesIds(){
    return partiesIds;
}


void Coalition::setTotalMandates(int value){
    this->mTotalMandates=value;
};
int  Coalition::getTotalMandates(){
    return this->mTotalMandates;
};


int  Coalition::getId(){return this->mId;};
void  Coalition::setId(int value){this->mId=value;};