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
    if ((input[index] == '\n')) {
        this->newLines++;
        inputRead++;
        index++;
        S1(input);
    }

    //INCLUDING THIS ELSE-IF MAKE 90-2 WORK, BUT BREAKS EVERYTHING ELSE
    /*else if ((input[index] == '\'') & (!isspace(input[index + 1]))) {
        inputRead++;
        index++;
        S2(input);
    }*/

    else if ((input[index] == '\'')) {
        inputRead++;
    } else {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if ((input[index] == '\'') || (input[index + 1] == '\'')) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
