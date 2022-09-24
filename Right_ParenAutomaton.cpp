#include "Right_ParenAutomaton.h"

using namespace std;

void Right_ParenAutomaton::S0(const std::string& input) {
    if (input[index] == ')') {
        inputRead++;
    }
    else {
        Serr();
    }
}