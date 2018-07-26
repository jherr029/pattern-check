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

        bool valid;

        string fileStr;
        string pattern = "";

        bool checkBrackets();
        bool checkOutsideBrackets();
        bool checker(string &);

        bool iteratorCheck(string::iterator, string::iterator);
        bool checkCenter(string::iterator, string::iterator, int);
        void setPattern(string::iterator, bool);
    
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
};

#endif