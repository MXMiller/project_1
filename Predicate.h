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
        output.append(getID() + '(');
        for(unsigned int i = 0; i < parameters.size(); i++){
            output.append(parameters.at(i)->getParam());
            if(i < parameters.size() - 1){
                output.append(",");
            }
        }
        output.append(")");
        return output;
    }

    void setID(string input){
        ID = input;
    }

    string getID(){
        return ID;
    }

    void addParam(string input){
        Parameter* p = new Parameter(input);
        parameters.push_back(p);
    }

    int getSize(){ return parameters.size(); }

    string getParam(int i){
        return parameters.at(i)->getParam();
    }
};

#endif //PROJECT_1_PREDICATE_H
