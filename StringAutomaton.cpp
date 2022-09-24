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

    else if ((input[index] == '\'') & (!isspace(input[index + 1]))) {
        inputRead++;
        index++;
        S1(input);
    }

    else if ((input[index] == '\'')) {
        inputRead++;

        /*
        if ((input[index + 1] == '\'') & (!isspace(input[index + 1])) {
            index++;
            S1(input);
        }
        */
    } else {
        inputRead++;
        index++;
        S1(input);
    }
}
