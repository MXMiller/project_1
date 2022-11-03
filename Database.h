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

    void addRel(Relation* newRelation){
        relations.insert(pair<string, Relation>(newRelation->getName(), *newRelation));
    }

    Relation* getRel(string name){
        return &relations[name];
    }

    Relation getRelCopy(string name){
        return relations[name];
    }
};

#endif //PROJECT_1_DATABASE_H
