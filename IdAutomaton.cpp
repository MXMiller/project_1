#include "IdAutomaton.h"

using namespace std;

void IdAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IdAutomaton::S1(const std::string& input) {
    if (isalpha(input[index]) || isalnum(input[index])) {
        inputRead++;
        index++;
        S1(input);
    } else {
    }
}
