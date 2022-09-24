#include "Left_ParenAutomaton.h"

using namespace std;

void Left_ParenAutomaton::S0(const std::string& input) {
    if (input[index] == '(') {
        inputRead++;
    }
    else {
        Serr();
    }
}