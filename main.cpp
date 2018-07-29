#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <chrono> // used for time
// #include <boost/tokenizer.hpp> // decided not to use

#include "PatternCheck.h"

using namespace std;
// using namespace chrono;

// Opens file named in fileName
// If it does not exist, it prompts
// the user to enter the file name again
// This occur until user inputs an actual file name
ifstream fileOpen( char* fileName )
{
    ifstream readFile;

    readFile.open( fileName );

    if ( !readFile )
    {
        string newFileName;

        cout << "File did not open" << endl;
        cout << "Enter file name: ";

        while ( !readFile )
        {
            getline( cin, newFileName );
            readFile.open( newFileName.c_str( ) );
        }
    }
    else
    {
        cout << "file opened" << endl;
    }

    cout << endl;

    return readFile;
}

// Checks if the user entered a valid number
// If the user did not enter a valid number
// they are prompted to enter a valid number until
// it is correct
int checkIfValidNumber( char* userInput )
{
    int result = atoi( userInput );

    while ( result == 0 )
    {
        cin >> result;
        while ( cin.fail( ) )
        {
            cout << "Enter a valid pattern number: ";
            cin.clear(); 
            cin.ignore(256, '\n');
            cin >> result;

            if ( result == 0 )
                cout << "0 is not a valid number" << endl;
        }

    }

    return result;
}

//  PatternCheck object is created here
// This method is responsible for creating and initiating the call
// to compute the objects validity
// the vector patternObjectVector is passed by reference to let
// main to use it's contents
void computePattern( vector<PatternCheck *> & patternObjectVector, char* fileName, int patterNumber )
{
    int line = 1;
    string fileLine;
    ifstream  inputFile = fileOpen( fileName );

    // creates the output file streams
    ofstream outputFile, correctFile, incorrectFile;

    // Results list of correct lines and its patterns
    outputFile.open( "output.txt" ); 

    // Does the same as above but for incorrect lines
    incorrectFile.open("incorrectPatterns.txt ");

    // A file for comparing a test case file created from pyython file
    // testing was used with shell's diff command
    correctFile.open( "correctPatterns.txt" );

    // If one file did not open exit
    if ( !outputFile || !correctFile || !incorrectFile )
    {
        cout << "A file did not open" << endl;
        exit(0);
    }

    cout << "Computing..." << endl;

    // While there are lines in inputFile continue with the loop
    // the lines of inputFile are placed in fileLine
    while( getline( inputFile, fileLine ) )
    {
        // Dynamically create PatternCheck objects
        // The file name and patternNumber are passed in to the default constructor
        PatternCheck * tempObject = new PatternCheck( fileLine, patterNumber );

        // Assigns the substrings of the string to the propre vectors
        // bracketSubstring_ or noBracketSubstring
        tempObject->assignVectors();

        // Thee call to determine fileLine contains a pattern
        tempObject->computeValidity();

        // Based on valid status, print to the proper files
        if (tempObject->isValid())
        {
            correctFile << line << "\n";

            outputFile << line << "\n";
            outputFile << tempObject->printCorrectPatterns(false);
            outputFile << endl;
        }
        
        else
        {
            incorrectFile << line << "\n";
            incorrectFile << tempObject->printIncorrectPatterns();
            incorrectFile << "\n";
        }

        // Push the PatternCheck object into the vector
        patternObjectVector.push_back(tempObject);
        line++;
    }

    // Prints the total number of correct lines
    // The index value does not matter as long as it exist in the vector
    // reason for this is that the class function returns a static variable
    cout << "Number Correct: " << patternObjectVector[1]->getCorrectAmountPatterns() << endl;

    outputFile.close();
    correctFile.close();
    incorrectFile.close();

}

// A prompt that ask the user if they would like
// information to a specific line
// If the input is invalid, then it prompts the
// user to enter a valid number
void userPrompt(vector<PatternCheck*> & patternObjectVector)
{
    int userInput = 0;
    int vectorSize = patternObjectVector.size();

    cout << endl;
    cout << "Enter '-1' at any time to exit " << endl;
    cout << "Total lines: " << vectorSize << endl;
    cout << "Enter line number to get specific information about that line: ";
    
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
            // Prints information pertaining to the specific
            // PatternCheck object
            patternObjectVector[userInput - 1]->printValidity( );
        }
        
        else if ( userInput == -1 )
        {
            cout << "Program end" << endl;
        }

        else
        {
            cout << endl;
            cout << "That line does not exist " << endl;
            cout << "Enter a number from 1 to " << vectorSize;
            cout << " or -1 to quit" << endl;
        }
    }
}


int main( int argc, char **argv )
{
    // Second command line arugment
    char* fileName = argv[1];

    // Third command line argument
    int patternNumber = checkIfValidNumber( argv[2] );

    vector<PatternCheck *> patternObjectVector;

    // high_resolution_clock::time_point t1 = high_resolution_clock::now();

    // Creates and works with PatternCheck objects
    computePattern( patternObjectVector, fileName, patternNumber );

    // high_resolution_clock::time_point t2 = high_resolution_clock::now();

    // auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    // cout << duration << endl;

    userPrompt(patternObjectVector);

    // Deletes the dynnamically created objects to avoid memory leaks
    for ( auto obj : patternObjectVector )
    {
        delete obj;
    }

    return 0;
}