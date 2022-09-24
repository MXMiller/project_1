#include "ColonAutomaton.h"

using namespace std;

void ColonAutomaton::S0(const std::string& input) {
    if (input[index] == ':') {
        //cout << "i read a COLON" << endl;
        inputRead++;
    }
    else {
        Serr();
    }
}