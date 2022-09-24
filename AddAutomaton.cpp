#include "AddAutomaton.h"

using namespace std;

void AddAutomaton::S0(const std::string& input) {
    if (input[index] == '+') {
        inputRead++;
    }
    else {
        Serr();
    }
}