#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <chrono>
#include <boost/tokenizer.hpp>
#include "patternCheck.h"

using namespace std;
using namespace boost;
using namespace chrono;

ifstream fileOpen(char* fileName)
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

int main(int argc, char **argv)
{

    string fileLine, fileLine2;

    vector<patternCheck *> objectVector;

    ifstream  inputFile = fileOpen(argv[1]);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    int i = 0;
    while( getline(inputFile, fileLine ) )
    {

        patternCheck * tempObject = new patternCheck(fileLine);

        tempObject->assignVectors();
        tempObject->checkValidty();
        tempObject->printValidity();

        objectVector.push_back(tempObject);

        // ownDelimiter(fileLine);
    }
    
    // objectVector[0]->assignVectors();
    // objectVector[0]->checkValidty();
    // objectVector[0]->printValidity();

    //objectVector[0]->checkValidty();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << duration << endl;

    // ifstream  inputFile2 = fileOpen(argv[1]);

    // high_resolution_clock::time_point t3 = high_resolution_clock::now();

    // while( getline(inputFile2, fileLine2) )
    //     boostToken(fileLine2);

    // high_resolution_clock::time_point t4 = high_resolution_clock::now();

    // auto duration2= duration_cast<microseconds>( t4 - t3 ).count();
    // cout << duration2 << endl;

    // cout << fileLine << endl;
    // getline(inputFile, fileLine, ']' );
    // cout << fileLine << endl;


    return 0;
}

    // string str = "ecoabbafl";

    // regex rx("b");
    
    // smatch mt;

    // while(regex_search(str, mt, rx))
    // {
    //     for (auto x : mt)
    //     {
    //         cout << x;
    //     }

    //     str = mt.suffix().str();
    // }

    // cout << endl;

    // if (regex_match(str, rx))
    // {
    //     cout << "true";
    // }
