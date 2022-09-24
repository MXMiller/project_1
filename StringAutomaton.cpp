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
    if (input[index] == '\n') {
        this->newLines++;
        inputRead++;
        index++;
        S1(input);
    } else if ((input[index] == '\'')) {
        if ((input[index + 1] != '\n')) {
            inputRead++;
            index++;
            S1(input);
        } else {
            inputRead++;
        }
    } else {
        inputRead++;
        index++;
        S1(input);
    }
}
