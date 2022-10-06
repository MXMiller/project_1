#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"

using namespace std;

class DatalogProgram
{
private:

    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;

public:
    DatalogProgram(){}
    ~DatalogProgram(){}

    string toString(){
        string output = "";
        return output;
    }

};

#endif //PROJECT_1_DATALOGPROGRAM_H
