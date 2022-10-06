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

public:
    Parameter(){}
    ~Parameter(){}

    string toString(){
        return p;
    }
};

#endif //PROJECT_1_PARAMETER_H
