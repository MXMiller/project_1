#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "DatalogProgram.h"
#include "Parameter.h"

using namespace std;

class Predicate
{
private:

    string ID;
    vector<Parameter*> parameters;

public:
    Predicate(){}
    ~Predicate(){}

    string toString(){
        string output = "";
        return output;
    }

    void setID(string input){
        ID = input;
    }

    string getID(){
        return ID;
    }

    void addParam(string input){
        parameters.push_back(new Parameter(input));
    }
};

#endif //PROJECT_1_PREDICATE_H
