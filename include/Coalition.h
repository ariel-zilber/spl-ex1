#pragma once

#include <vector>
 
using std::vector;

/**
* This class represents a coalition( group of parties).
* */
class Coalition {
public:
    // Constructors:
    /**
    *  Creates a new Coalition
    *  @param id the id of the coalition
    */
    Coalition(int id);

    // Methods:
    /***
     *   Const getter for the total mandates of the coalition
     *   @return the total mandates of the coalition
     */
    int  getTotalMandates();



    /***
     *  Adds mandates to the coalition
     */
    void addMandates(int numOfMandatesToAdd);



    /***
     *   Const getter for the id the coalition
     *   @return the id of the  coalition
     */
    int  getId() const ;

private:
    // Data members:

    int mTotalMandates;
    int mId;
};