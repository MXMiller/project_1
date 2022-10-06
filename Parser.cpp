#include "Parser.h"

using namespace std;

Parser::Parser() {

}

Parser::~Parser() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Parser::Run(std::vector<Token*> tokens){}

string Parser::toString() {
    string output = "";

    //its showing symbols because

    for(unsigned int i = 0; i < tokens.size(); i++){
        output.push_back('(');
        output.append((tokens.at(i)->getType()) + ',' + '"');
        output.append(tokens.at(i)->getVal() + '"' + ',');
        output += to_string(tokens.at(i)->getLine());
        output.append(")\n");
    }

    output.append("Total Tokens = ");
    output += to_string(tokens.size());

    return output;
}

