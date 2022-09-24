#include "EOFAutomaton.h"

using namespace std;

void EOFAutomaton::S0(const std::string& input) {
    if (input[index] == EOF) {
        inputRead++;
    }
    else {
        Serr();
    }
}