#ifndef PROJECT_1_HEADER_H
#define PROJECT_1_HEADER_H
#include <vector>
#include <map>
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

using namespace std;

class Header
{
private:
    vector<Parameter*> colNames;

public:
    Header(){}
    ~Header(){}

    void setColName(vector<Parameter*> input){
        colNames = input;
    }

    Parameter* getColName(int i){
        return colNames.at(i);
    }

    int getSize(){
        return colNames.size();
    }
};

#endif //PROJECT_1_HEADER_H
