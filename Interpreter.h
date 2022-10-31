#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H
#include <vector>
#include <map>
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"

using namespace std;

class Interpreter
{
private:

    DatalogProgram* program = new DatalogProgram();

public:
    Interpreter(DatalogProgram* program){
        this->program = program;
    }
    ~Interpreter(){}

    void interpretSchemes();
    void interpretFacts();
    void interpretQueries();
};

#endif //PROJECT_1_INTERPRETER_H
