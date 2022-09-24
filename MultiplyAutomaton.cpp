#include "MultiplyAutomaton.h"

using namespace std;

void MultiplyAutomaton::S0(const std::string& input) {
    if (input[index] == '*') {
        inputRead++;
    }
    else {
        Serr();
    }
}