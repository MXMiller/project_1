#ifndef PROJECT_1_DATABASE_H
#define PROJECT_1_DATABASE_H
#include <vector>
#include <map>
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Relation.h"

using namespace std;

class Database
{
private:

    map<string, Relation> relations;

public:
    Database(){}
    ~Database(){}

    void AddRel(Relation newRelation);
    Relation* getRel(string name);
    Relation getRelCopy(string name);
};

#endif //PROJECT_1_DATABASE_H
