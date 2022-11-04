#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H
#include <vector>
#include <map>
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Database.h"

using namespace std;

class Interpreter
{
private:

    DatalogProgram* program = new DatalogProgram();
    Database* database = new Database();

public:
    Interpreter(DatalogProgram* program){
        this->program = program;
    }
    ~Interpreter(){}

    Database* interpret(){

        interpretSchemes();
        interpretFacts();
        interpretQueries();

        toString();

        return database;
    }

    void interpretSchemes();
    void interpretFacts();
    //void interpretRules();
    void interpretQueries();

    Relation evaluatePredicate(Predicate* query);

    string toString();
};

#endif //PROJECT_1_INTERPRETER_H
