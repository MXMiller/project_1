#ifndef PROJECT_1_PARAMETER_H
#define PROJECT_1_PARAMETER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "DatalogProgram.h"

using namespace std;

class Parameter
{
private:

    string p;
    bool isConstant = false;

public:
    Parameter(string input){
        p = input;
    }
    ~Parameter(){}

    string getParam(){
        return p;
    }

    void setParam(string input){
        p = input;
    }

    void setConstant(){
        isConstant = true;
    }

    bool isCon(){
        return isConstant;
    }
};

#endif //PROJECT_1_PARAMETER_H
