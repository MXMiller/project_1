#include <vector>
#include <map>
#include "DatalogProgram.h"
#include "Header.h"
#include "Tuple.h"
#include "Relation.h"


Relation Relation::select1(int columnI, string val){

    Relation* selectR = new Relation(name, colNames);

    for(set<Tuple>::iterator i = tuples.begin(); i != tuples.end(); ++i){

        Tuple curr = *i;

        if(curr.getRowVal(columnI) == val){
            selectR->addTuple(curr);
        }
    }

    return *selectR;
}

Relation Relation::select2(int columnI1, int columnI2){

    Relation* selectR = new Relation(name, colNames);

    for(set<Tuple>::iterator i = tuples.begin(); i != tuples.end(); ++i){

        Tuple curr = *i;

        if(curr.getRowVal(columnI1) == curr.getRowVal(columnI2)){
            selectR->addTuple(curr);
        }
    }

    return *selectR;
}

Relation Relation::project(vector<int> columns){

    Header newHeader;
    vector<Parameter*> newC;

    //get the right column headers

    for(int i = 0; i < colNames.getSize(); i++){
        for(unsigned int j = 0; j < columns.size(); j++){
            if(i == columns.at(j)){
                //found one of the columns
                newC.push_back(colNames.getColName(i));
            }
        }
    }

    newHeader.setColName(newC);
    Relation projectR = *(new Relation(name, newHeader));

    //get the right column values

    for(set<Tuple>::iterator t = tuples.begin(); t != tuples.end(); t++){

        Tuple curr = *t;
        Tuple newT;

        vector<string> newVals;

        //newT.setRowVals(newVals);

        for(int i = 0; i < curr.getSize(); i++){

            for(unsigned int j = 0; j < columns.size(); j++){
                //what is the first thing supposed to be?
                if(i == columns.at(j)){
                    //found one of the columns
                    string tupleVal = curr.getRowVal(i);
                    newVals.push_back(tupleVal);
                }
            }
        }

        newT.setRowVals(newVals);

        projectR.addTuple(newT);
    }

    return projectR;
}

Relation Relation::rename(vector<string> newColNames){

    //the tuples that are sent into this function aren't the right tuples
    Header blank;

    Relation renameR = *(new Relation(name, blank));
    renameR.setTuples(this->getTuples());
    renameR.setName(name);

    vector<Parameter*> newN;

    for(unsigned int i = 0; i < newColNames.size(); i++){
        Parameter* newP = new Parameter(newColNames.at(i));
        if(newP->isCon() == false){
            newN.push_back(newP);
        }
    }

    Header newHeader;
    newHeader.setColName(newN);
    renameR.setHeader(newHeader);

    return renameR;
}
