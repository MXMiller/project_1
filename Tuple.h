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
    vector<Parameter*> rowVals;

public:
    Tuple(){}
    ~Tuple(){}

    void setRowVals(vector<Parameter*> input){
        rowVals = input;
    }
};

#endif //PROJECT_1_TUPLE_H
