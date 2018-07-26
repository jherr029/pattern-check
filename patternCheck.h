#ifndef PATTERNCHECK_H
#define PATTERNCHECK_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class patternCheck
{
    private:
        vector<string> subStrBrackets;
        vector<string> subStrNoBrackets;

        string::iterator startAddress;
        string::iterator endAddress;

        bool valid;

        string fileStr;
        string pattern;
        string patternSubstring;


        bool checkBrackets();
        bool checkOutsideBrackets();
        bool checker(string &);

        bool iteratorCheck(string::iterator, string::iterator);
        bool checkCenter(string::iterator, string::iterator, int);
        bool iteratorLoop(string::iterator, string::iterator, string::iterator, string::iterator, bool);
        void setPattern(string::iterator, bool);

        void assignPatternSubstring(const string &);
    
    public:
        patternCheck(const string &);

        void assignVectors();
        bool checkValidty()
        {
            if (checkBrackets())
            {
                valid = false;
                return false;
            }
            
            else if (checkOutsideBrackets())
            {
                valid = true;
                return true;
            }

            valid = false;
            return false;

        }

        void printString();
        string getString();

        void printValidity();
        void printCorrectPatterns();
        bool getValidty() {return valid;}
        bool isStrEven(int);
};

#endif