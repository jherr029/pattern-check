#include "PatternCheck.h"


// Static int initializations
// -- sCorrect - the number of correct objects
// -- sLineNumber_ - the line number assigned to the object
int PatternCheck::sCorrect_ = 0;
int PatternCheck::sLineNumber_ = 0;

// Default PatternCheck constructor
// Default values are assigned
// -- str : read file line 
// -- num : the length of the pattern to be searched for
PatternCheck::PatternCheck( const string & str, int num )
{
    valid_ = false;                         // Object is set to false

    fileLine_ = str;                        // Sets the object's file line
    pattern_ = "NO PATTERN FOUND";          // Default no pattern
    patternSubstring_ = "NO PATTERN FOUND"; // Default no substring

    patternNum_ = num;                      // Set pattern length
    patternFirstIndex_ = -999;              // Default
    patternLastIndex_ = -999;               // Default
    sLineNumber_++;                         // Increments line number
}


// Prints the current's objects information about the pattern
// Prints if a pattern exist and if it is valid or not
// also prints information if no pattern is found
// -- : No parameters
// ++ : Nothing retruns
void PatternCheck::printValidity( )
{
    cout << endl;
    string tempString;

    if ( pattern_ != "NO PATTERN FOUND" )
    {
        // Adds parentheses between the pair to help
        // visualize the pattern within the substring
        tempString = patternSubstring_;
        tempString.insert( patternFirstIndex_, "(" );
        tempString.insert( patternLastIndex_ + 2, ")" );
    }

    if ( valid_ )
    {
        cout << "True\n" << "pattern: " << pattern_ << "\n" << tempString << endl;
        cout << fileLine_ << endl;
    }

    else
    {
        if ( pattern_ != "NO PATTERN FOUND" )
        {
            cout << "False\npattern: " << pattern_ << " found inside [" << tempString;
            cout << "]\n" << fileLine_ << endl;
        }

        else
            cout << "False - no patterns found in string\n" << fileLine_ << endl;
    }

    cout << endl;
}

// <public>
// Prints the object's file line
// -- : No parameters
// ++ : Nothing returns
void PatternCheck::printLine( )
{
    cout << fileLine_ << endl;
}

// <public> TODO:maybe should be private
// Determines if the number is even or odd
// -- stringLength : int representing substring's length
// ++ : bool representing if the number is even or odd
bool PatternCheck::isStrEven( int stringLength )
{
    return ( ( stringLength % 2 ) == 0 );
}

// <public>
// Print's the objects validity
// -- : No parameters
// ++ : Returns valid_
bool PatternCheck::isValid( )
{
    return valid_;
}

// <public>
// Returns a string that conatains the pattern_, patternSubstring_ and fileLine_
// -- brackets : bool that indicates that the pattern is valid or invalid
// ++ tempStr : returns the description
string PatternCheck::printCorrectPatterns( bool brackets )
{
    string tempStr;
    string tempSubstr = patternSubstring_;

    // Adds parentheses between the pattern to help
    // visualize the pattern inside the substring
    tempSubstr.insert( patternFirstIndex_, "(" );
    tempSubstr.insert( patternLastIndex_ + 2, ")" );

    if ( !brackets )
        tempStr = "pattern " + pattern_ + "\n" + tempSubstr + "\n" + fileLine_ + "\n";

    else
        tempStr = "pattern " + pattern_ + "\n[" + tempSubstr + "]\n" + fileLine_ + "\n";

    return tempStr;
}

// <public>
// Returns a string that contains information from
// printCorrectPatterns but only specifically thoes
// inside []. If the object has no pattern, it will
// return a string saying no pattern is found and the 
// file line 
// -- : No parameters
// ++ : Description 
string PatternCheck::printIncorrectPatterns( )
{
    if ( pattern_ == "NO PATTERN FOUND" )
        return ( "No pattern found\n" + fileLine_ + "\n");

    else
        return printCorrectPatterns( true );

    return "";
}

// <public>
// Returns the amount of valid patterns
// -- : No parameters
// ++ : Description
int PatternCheck::getCorrectAmountPatterns( )
{
    return sCorrect_;
}

// <public>
// Parses the string based on '[' and ']'
// Substrings between [] are placed in bracketSubstrings_
// Substrings that are not between [] are placed in nobracketSubstrings_
// -- : No parameters
// ++ : Nothing returns
void PatternCheck::assignVectors( )
{
    string str = fileLine_;     // The object's file line is placed in str

    size_t position = 0;        // Placeholder for the first occurence
    string token;               // of '[' or ']'

    bool bracketSwitch = false;     // A flag to toggle between '[' and ']'
    bool substrInBrackets = false;  // Used on the edge case if fileLine_ starts with '['
    string bracket = "[";           // The delimiter


    // While there is brackets, the while loop will loop
    // Finds the first position of bracket which toggles from '[' and ']'
    while( ( position = str.find( bracket ) ) != string::npos ) 
    {
        // Toggles bracket value
        if ( !bracketSwitch )
            bracket = "]";
        else 
            bracket = "[";
        
        // Toggles the bool value 
        bracketSwitch = !bracketSwitch; 

        // Gets the substring from 0 and the first occurnce of bracket
        token = str.substr( 0, position );

        //  Erases that portion of the substring from str
        //  and the bracket itself
        str.erase( 0, position + 1 );

        // Edge case
        // If for the first char from the fileLine_ is not '['
        // continue 
        if ( position != 0 ) 
        {
            // Substring is between [ ]
            if ( substrInBrackets )
                bracketSubstrings_.push_back( token );
            
            else
                noBracketSubstrings_.push_back( token ); // Not between []
            
            // Toggle 
            substrInBrackets = !substrInBrackets;
        }
        // the first char of fileLine_ is '['
        else
            substrInBrackets = true;
            // Toggle
    }

    // Gets the remaining string
    if ( str.length( ) > 0 )
        noBracketSubstrings_.push_back( str );
}

// <private>
// Sets the pattern that is found
// This pattern is either a valid one or one that makes the
// line invalid
// -- itr : A string iterator that contains the address 
//          of the first character of the pattern
// ++ : Nothing is returned
void PatternCheck::setPattern( string::iterator itr )
{
    // Clears pattern from the default value
    pattern_.clear( );

    // Iterates through itr in its address to
    // get the remaning values;
    // patterNum + 2 is for scaling purposes
    for ( int i = 0; i < patternNum_ * 2; i++ )
    {
        pattern_.push_back( *( itr + i ) );
    }
}

// <private>
// Sets the substring that the patterin is found in
// -- str : The substring that the pattern is found in
// ++ : Nothing is returned
void PatternCheck::setPatternSubstring( const string & str )
{
    patternSubstring_ = str;
}

// <public>
// Initiates the calls to a private method to determine the objects
// validity.
// If a pattern is found in between [] then the line is false
// If no pattern was found in between [] then check those that are not
// If neirther of the two are true then no pattern is found
// between []
// Its important to first check if the string is invalid first to save time
// -- : No Parameters
// ++ : Nothing is returned
bool PatternCheck::computeValidity( )
{
    // Checks the elements in bracketSubstrings_
    if ( checkVector( bracketSubstrings_ ) )
    {
        valid_ = false;
        return false;
    }
    
    // Checks the elements in noBracketSubstrings_
    else if ( checkVector( noBracketSubstrings_ ) )
    {
        valid_ = true;
        sCorrect_++;    // increments the correct counter
        return true;
    }

    // No Pattern is found
    valid_ = false;
    return false;
}

// <private>
// Iterates through the elements of the passed vector to see
// if a pattern exist
// -- vec : a vector of strings ( bracketSubstrings_, noBracketSubsrtings_)
//          This is passed by reference to save memory space
// ++ bool : Returns a value indicating if a pettern is found
bool PatternCheck::checkVector( const vector<string> & vec)
{
    bool patternFound;

    // Iteratees through the elements in the array
    // C++11 required for this
    // auto gets the data type automatically
    // iterates through vec and sets the data in str
    for ( auto str : vec )
    {
        patternFound = scanSubstring( str );

        if (patternFound)
            return true;
    }

    return false;
}

// <private>
// Computes and returns the range from the beginning of the pattern
// to the end of the pattern.
// Required for scaling
// -- : Nothing
// ++ : Returns the range
int PatternCheck::computeRange(  )
{
    if ( patternNum_ == 1 )
        return 1;

    else
        return ( ( patternNum_ * 2 ) - 1 );

}

// <private>
// Iterates through the substring to find a pattern
// Inside the for loop, a recursive function; matchRecursively
// is called to see if there is pattern
// This function is mostly responsible for the block that the 
// recursive function will be examing
// Example - let patternNum_ be 2
//      let substring be abcdefghi
//      the first block is {abcd}efghi
//      the second block if no pattern was found is a{bcde}fghi
//      all the way to the end if no pattern was found abcde{fghi}
//
//      If patterNum is 4 then the block is {abcdefgh}ijklm
//      The block size is patternNum_ * 2
//
// -- substring : a string representing the current substring
// ++ bool : returns if pattern is found
bool PatternCheck::scanSubstring( string & substring )
{
    bool result;
    int stepAhead = computeRange( );    // computes the range to get the block
    int stringLength = substring.length( ); // substring length 
    // int stringMidpoint = stringLength / 2;

    // If the length of the substring is smaller than patternNum * 2
    // then it is impossible for a pattern to be in the substring
    if ( stringLength < ( patternNum_ * 2 ) )
        return false;

    // A bit vector
    int alphaBitVector;

    // Sets front to the beginning of the string
    string::iterator front = substring.begin( );


    // Iterates through the string
    for ( ; front + stepAhead != substring.end( ); front++ )
    {
        // Sets the bit vector to 0 ( reseting the bit vector )
        alphaBitVector = 0;

        // Calls the recursive function to see if the block is
        // a pattern
        // Arguments:
        //          1. Sets the beginning of the block
        //          2. Sets the end of the block
        //          3. Bit vector to determine if the block does not contain
        //              more than 2 of the same character
        result = matchRecursively( front, front + stepAhead, alphaBitVector );

        // If a pattern exist set patternSubstring_ and pattern_
        // returns true
        if ( result )
        {
            setCorrectValues( substring, front );
            return true;
        }
    }

    // Pattern does not exist
    return false;
}

// <private>
// Recursively calls it to see if the block contains a pattern
// The function checks if the ends of the block match each other
// When true, it sets a bit at a specific to indicate that the matched
// character exist in the pattern. This is to avoid having a pattern such as
// aaaa, or aabb, and others like caccac
// When the function calls itself the block shrinks, and the same behavior
// is repeated again ( if the ends of the block match )
//                      ( else it returns false )
// Assumption: since I was not asked to find a pattern not bigger than 2
//              I assumed as long as all the characters within the block
//              does not occur more than twice
//
// -- front : the beginning of the block
// -- back  : the end of the block 
// -- bitVector : a bit vector that indicates which specific alphabetical characters
//                  are active in the block. Used to make sure there is nomre than 2
//                  of the same character
// 

bool PatternCheck::matchRecursively( string::iterator front, string::iterator back,
                                        int bitVector )
{
    // bool to use for bit vector
    bool unique;

    // Checks if the ends of the block match
    if ( *front == *back )
    {
        // Gets numerical values for the alphabetical characters
        // a is 0, b is 1, ..., and z is 25
        int alphaIndex = computeAlphaIndexValue( *front );

        // Checks if at bit position alphaIndex is not equal to 1
        // If it is not 1, then that character pair is uniqe in  the block
        unique = ( ( bitVector & ( 1 << alphaIndex ) ) != 1 );

        // If index is -1 then an error occured that indicates that the file has illegal
        //  characters such like upper case letters or non alphabetical
        // If unique continue for another recursive call
        if (alphaIndex != -1 && unique )
        {
            // Sets the bit position at alphaIndex to 1
            bitVector |= ( 1 << alphaIndex );

            // Base case
            // If front + 1 is equal to one
            // then the block is in the middle of the pattern
            // Therefore the pattern is true and there is no more
            // need to recursively call
            if ( ( front + 1) ==  back )
                return true;

            // Calls itself, shrinks the block by 1 spot on both ends
            // And passes the bit vector
            return( matchRecursively( front + 1, back - 1, bitVector ) );
        }
    }

    // The ends of the block do not match
    return false;
}

// <private>
// Gets a numeral value that represents a lower case alphabetical character
// -- ch : the matching character
// ++ int : returns a number representing the character
// *        returns -1 if ch is an illegal character
int PatternCheck::computeAlphaIndexValue( char ch )
{
    // Converts the char values to int (ASCII)
    // a and z are the bounds
    int aValue = 'a'; 
    int zValue = 'z';
    int charValue = ch;

    // If the value is between the bounds, then it is legal
    if ( charValue >= aValue && charValue <= zValue )
    {
        // Uses 'a' int value as the base
        //  Example : a - a = 97 - 97 = 0
        //             b - a = 98 - 97 = 1
        return charValue - aValue; 
    }

    // An illegal character is used
    return -1;
}


// <private>
// Sets patternSubstring_, patternFirstIndex_, patternLastIndex_, and pattern_
// -- substring : the substring the pattern is found in
// -- front : a string iterator of the first position (address) of the pattern 
void PatternCheck::setCorrectValues(string & substring, string::iterator front )
{
    int stepAhead = computeRange( );

    patternSubstring_ = substring;

    // front - substring.begin() gets an int value of where front is located
    //          in the substring
    patternFirstIndex_ = front - substring.begin();

    // Gets the last position of the pattern from the substring
    patternLastIndex_ = patternFirstIndex_ + stepAhead;

    // Sets the pattern_
    setPattern(front);
}
