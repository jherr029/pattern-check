#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
// #include <regex>
// #include <boost/tokenizer.hpp>

#include "PatternCheck.h"

using namespace std;
using namespace chrono;
// using namespace boost;

ifstream fileOpen( char*  fileName )
{
    ifstream readFile;

    readFile.open(fileName);

    if (!readFile)
    {
        cout << "File did not open" << endl;
    }
    else
        cout << "file opened" << endl;

    cout << endl;

    return readFile;
}

int main( int argc, char **argv )
{
    string fileLine, fileLine2;
    int userInput = 0;

    vector<PatternCheck *> objectVector;

    ifstream  inputFile = fileOpen(argv[1]);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    ofstream outputFile;
    ofstream correctFile;
    outputFile.open("output.txt");

    correctFile.open("cCorrect.txt");

    int line = 1;
    while( getline(inputFile, fileLine ) )
    {

        PatternCheck * tempObject = new PatternCheck(fileLine);

        tempObject->assignVectors();
        tempObject->computeValidity();
        // tempObject->printValidity();

        if (tempObject->isValid())
        {
            outputFile << line << "\n";
            correctFile << line << "\n";
            outputFile << tempObject->printCorrectPatterns(false);
            outputFile << endl;
        }

        objectVector.push_back(tempObject);
        line++;

    }

    cout << "Number Correct: " << objectVector[1]->getCorrectAmountPatterns() << endl;

    outputFile.close();

    // cout << "Number Correct: " << i << endl;

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << duration << endl;

    int vectorSize = objectVector.size();

    cout << endl;
    cout << "Enter 'quit' at any time to exit " << endl;
    cout << "Enter line number to get specific information about that line " << endl;
    cout << "Total lines: " << vectorSize << endl;
    
    while ( userInput != -1 )
    {
        cin >> userInput;
        while ( cin.fail( ) )
        {
            cout << "please enter a number: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> userInput;
            
        }


        if ( userInput >= 1 && userInput <= vectorSize )
        {
            objectVector[userInput - 1]->printValidity( );
        }
        
        else if ( userInput -1 )
        {
            cout << "Program end" << endl;
        }

        else
        {
            cout << "That line does not exist " << endl;
            cout << "Enter a number from 1 to " << vectorSize;
            cout << " or -1 to quit" << endl;
        }
    }

    return 0;
}

/*
void boostToken(string str)
{

    vector<string> without;
    vector<string> with;


    bool bracketFlag = false;
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> seperator("[]");

    tokenizer tokens(str);

    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
    {

        // cout << *tok_iter << endl;

        if (*tok_iter == "[" || *tok_iter == "]")
        {
            bracketFlag = !bracketFlag;
            tok_iter++;
        }

        if (bracketFlag)
            with.push_back(*tok_iter);
        
        else if (!bracketFlag)
            without.push_back(*tok_iter);
        
    }

    // cout << "With" << endl;
    // for ( auto ele : with )
    //     cout << ele << endl;

    // cout << "\nWithout" << endl;
    // for ( auto ele : without )
    //     cout << ele << endl;
    
    // cout << endl;

}
*/