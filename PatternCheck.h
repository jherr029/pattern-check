#ifndef PATTERNCHECK_H
#define PATTERNCHECK_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// PatterCheck object responsible for checking if a pattern exist
// within a line of a file
class PatternCheck
{
    public:

        PatternCheck( const string &, int );
        PatternCheck();

        void printValidity( );
        void printLine( );

        bool isStrEven( int );
        bool isValid( );

        string printIncorrectPatterns( );
        string printCorrectPatterns( bool );

        int getCorrectAmountPatterns( );

        void assignVectors( );
        bool computeValidity( );



        // make a nice print for a specific line
        // set line number

    private:
        bool valid_;
        static int sCorrect_;
        static int sLineNumber_;
        int patternNum_;

        vector<string> bracketSubStrings_;
        vector<string> noBracketSubstrings_;

        int patternFirstIndex_, patternLastIndex_;
        string pattern_, fileLine_,  patternSubstring_;

        void setPattern( string::iterator );
        void assignPatternSubstring( const string & );

        bool checkBrackets( const vector<string> & );
        bool scanSubstring( string & );

        int computeAlphaIndexValue( char );
        int computeRange( );
        bool matchRecursively( string::iterator, string::iterator, int, int );
        void setCorrectValues(string &, string::iterator );
};

#endif