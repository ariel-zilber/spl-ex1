#include "Coalition.h"

Coalition::Coalition(int id) : mTotalMandates(0), mId(id) {

}


void Coalition::setTotalMandates(int value) {
    this->mTotalMandates = value;
};

int Coalition::getTotalMandates() {
    return this->mTotalMandates;
};


int Coalition::getId() const {
    return this->mId;
};

