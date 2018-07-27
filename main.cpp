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

void computePattern(vector<PatternCheck *> & patternObjectVector, char* fileName )
{
    int line = 1;
    string fileLine;
    ifstream  inputFile = fileOpen(fileName);
    ofstream outputFile, correctFile, incorrectFile;

    outputFile.open("output.txt");
    correctFile.open("correctPatterns.txt");
    incorrectFile.open("incorrectPatterns.txt");

    while( getline(inputFile, fileLine ) )
    {

        PatternCheck * tempObject = new PatternCheck(fileLine);

        tempObject->assignVectors();
        tempObject->computeValidity();

        if (tempObject->isValid())
        {
            outputFile << line << "\n";
            correctFile << line << "\n";
            outputFile << tempObject->printCorrectPatterns(false);
            outputFile << endl;
        }
        
        else
        {
            incorrectFile << line << "\n";
            incorrectFile << tempObject->printIncorrectPatterns();
            incorrectFile << "\n";
        }

        patternObjectVector.push_back(tempObject);
        line++;
    }

    cout << "Number Correct: " << patternObjectVector[1]->getCorrectAmountPatterns() << endl;

    outputFile.close();
    correctFile.close();
    incorrectFile.close();

}

void userPrompt(vector<PatternCheck*> & patternObjectVector)
{
    int userInput = 0;
    int vectorSize = patternObjectVector.size();

    cout << endl;
    cout << "Enter '-1' at any time to exit " << endl;
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
            patternObjectVector[userInput - 1]->printValidity( );
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

}


int main( int argc, char **argv )
{
    char* fileName = argv[1];

    vector<PatternCheck *> patternObjectVector;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    computePattern(patternObjectVector, fileName);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << duration << endl;

    userPrompt(patternObjectVector);

    return 0;
}