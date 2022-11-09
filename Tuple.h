#ifndef PROJECT_1_TUPLE_H
#define PROJECT_1_TUPLE_H
#include <vector>
#include <map>
#include "DatalogProgram.h"
#include "Predicate.h"

using namespace std;

class Tuple
{
private:
    vector<string> rowVals;

public:
    Tuple(){}
    ~Tuple(){}

    void setRowVals(vector<string> input){
        rowVals = input;
    }

    string getRowVal(int i){
        return rowVals.at(i);
    }

    int getSize(){
        return rowVals.size();
    }

    bool operator< (const Tuple &rhs) const {
        return rowVals < rhs.rowVals;
    }
};

#endif //PROJECT_1_TUPLE_H
