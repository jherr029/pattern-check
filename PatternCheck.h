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
        // string & - pass by reference
        // The motive for this method is to save
        // space by avoiding making a copy of the
        // argument
    
        // Default Constructor for PatternCheck object
        // const string &: the current line string
        // int : the pair number to find
        //      -- example 2 for xaax
        //      --         3 for abccba
        PatternCheck( const string &, int );
        // ~PatternCheck();     // not needed since dynamic memory
                                // was not used within the class

        // prints out the result of the current object
        void printValidity( );

        // prints out the line assigned to the current object
        void printLine( );

        // checks if the int value is passed is even or odd
        // the number comes from the current substring of the
        // file line
        bool isStrEven( int );

        // returns if the object's line is valid
        bool isValid( );

        // Returns a string that contains information
        // as to why the object's line is wrong
        // Also calls the printCorrectPatterns
        string printIncorrectPatterns( );

        // Returns a string that contains information
        // pertaining to the object's line that has 
        // a pair
        string printCorrectPatterns( bool );

        // Returns the number of correct patterns;
        int getCorrectAmountPatterns( );

        // Parses line into substrings based on the 
        // delimeters '[' and ']' and places them in one of two vectors
        // One vector contains substrings within the brackets, while the
        // other contains the ones that are not in between brackets
        void assignVectors( );

        // Initiates the call to compute the object's validity
        // Calls private method checkVector
        bool computeValidity( );

    private:
        bool valid_;                    // Valid status of the object
        static int sCorrect_;           // Static int - number of correct objects
        static int sLineNumber_;        // Static int - the file line of the object
        int patternNum_;                // The patternNum to be used

        vector<string> bracketSubstrings_;  // Vector holding substrings between []
        vector<string> noBracketSubstrings_;// Vector holding substrings not in []

        // Index of the first and last char of the pattern
        int patternFirstIndex_, patternLastIndex_;

        // The pattern, file line, and the substring the pattern is found in
        string pattern_, fileLine_,  patternSubstring_;
                                                        
        // Sets pattern_
        void setPattern( string::iterator ); 

        // Sets patternSubstring_ that pattern_ is found in
        void setPatternSubstring( const string & );

        // Iterates through the two vectors, bracketSubstrings_ and noBracketSubstrings_
        // which are passed onto the scanSubstring function
        bool checkVector( const vector<string> & );

        // Scans the substring to see if it contains a pattern
        bool scanSubstring( string & );

        // Recursively checks if the two string iterators match
        // the first int is the number of recurseive steps required to be
        // done in order to reach the recursion's base case
        // The last int is a bit vector that checks which alphabetical characters
        // have matched so far. This is explained more in the function
        bool matchRecursively( string::iterator, string::iterator, int, int );

        // If a pattern is found inside [] then 
        // pattern_, patternSubstring_, patternFirstIndex_ and patternLastIndex_
        // are set
        void setCorrectValues(string &, string::iterator );

        // Determines the range from the first char in the pair
        // to the last char in the pair
        int computeRange( );

        // Determines the int value of a char from a - z
        // a is 0, b is 1, ... , and z is 25
        int computeAlphaIndexValue( char );
};

#endif