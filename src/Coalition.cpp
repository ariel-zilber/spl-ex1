#include "Coalition.h"

Coalition::Coalition(int id) : mTotalMandates(0), mId(id) {
}

int Coalition::getTotalMandates() {
    return this->mTotalMandates;
};


int Coalition::getId() const {
    return this->mId;
};


void Coalition::addMandates(int numOfMandatesToAdd) {
    this->mTotalMandates += numOfMandatesToAdd;
};

