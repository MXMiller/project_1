#include "StringAutomaton.h"

using namespace std;

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if(index >= (input.size())){
        this->type = TokenType::UNDEFINED;
    } else if ((input[index] == '\n')) {
        this->newLines++;
        inputRead++;
        index++;
        S1(input);
    } else if ((input[index] == '\'')) {
        inputRead++;
        index++;
        S2(input);
    } else {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if ((input[index] == '\'')) {
        inputRead++;
        index++;
        S1(input);
    } else {
        //this->type = TokenType::UNDEFINED;
    }
}
