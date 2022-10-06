#include <fstream>
#include <iostream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    // check command line arguments
    if (argc != 2) {
        cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // open file
    string fileName = argv[1];
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
        return 1;
    }

    string input;

    while(file.peek() != EOF){
        input.push_back(file.get());
    }

    //MAKING SURE IT GOT THE STUFF FROM THE FILE
    //cout << input << endl;

    lexer->Run(input);

    Parser* parser = new Parser(lexer->getTokens());
    parser->parse();

    //cout << lexer->toString();

    delete lexer;

    return 0;
}