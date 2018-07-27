#ifndef PATTERNCHECK_H
#define PATTERNCHECK_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class PatternCheck
{
    public:
        PatternCheck( const string & );
        // ~PatternCheck();

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

        vector<string> bracketSubStrings_;
        vector<string> noBracketSubstrings_;

        int patternFirstIndex_, patternLastIndex_;
        string pattern_, fileLine_,  patternSubstring_;

        void setPattern( string::iterator, bool );
        void assignPatternSubstring( const string & );

        bool checkBrackets( const vector<string> & );
        bool checker( string & );

        bool checkCenter( string::iterator, string::iterator, int, string & );

        bool iteratorLoop( string::iterator &, string::iterator &, string::iterator &,
                             string::iterator &, bool, string & );

        bool iteratorCheck( string::iterator &, string::iterator &, string & );

        bool ifMatch( char, char );
        bool ifLegalMatch( char, char );

};

#endif