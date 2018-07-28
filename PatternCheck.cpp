#include "PatternCheck.h"


int PatternCheck::sCorrect_ = 0;
int PatternCheck::sLineNumber_ = 0;

PatternCheck::PatternCheck( const string & str, int num )
{
    valid_ = false;

    fileLine_ = str;
    pattern_ = "NO PATTERN FOUND";
    patternSubstring_ = "NO PATTERN FOUND";

    patternNum_ = num;
    patternFirstIndex_ = -999;
    patternLastIndex_ = -999;
    sLineNumber_++;
}

void PatternCheck::printValidity( )
{

    cout << endl;
    string tempString;

    if ( pattern_ != "NO PATTERN FOUND" )
    {
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

void PatternCheck::printLine( )
{
    cout << fileLine_ << endl;
}

bool PatternCheck::isStrEven( int stringLength )
{
    return ( ( stringLength % 2 ) == 0 );
}

bool PatternCheck::isValid( )
{
    return valid_;
}

string PatternCheck::printCorrectPatterns( bool brackets )
{
    string tempStr;
    string tempSubstr = patternSubstring_;
    int stepAhead = computeRange( );
    int tempPosition = patternLastIndex_;

    // cout << tempSubstr << endl;
    tempSubstr.insert( patternFirstIndex_, "(" );
    // cout << tempSubstr << endl;
    tempSubstr.insert( patternLastIndex_ + 2, ")" );

    if ( !brackets )
        tempStr = "pattern " + pattern_ + "\n" + tempSubstr + "\n" + fileLine_ + "\n";

    else
        tempStr = "pattern " + pattern_ + "\n[" + tempSubstr + "]\n" + fileLine_ + "\n";

    return tempStr;
}

string PatternCheck::printIncorrectPatterns( )
{
    if ( pattern_ == "NO PATTERN FOUND" )
        return ( "No pattern found\n" + fileLine_ + "\n");

    else
        return printCorrectPatterns( true );

    return "";
}

int PatternCheck::getCorrectAmountPatterns( )
{
    return sCorrect_;
}

void PatternCheck::assignVectors( )
{

    string str = fileLine_;

    size_t position = 0;
    string token;

    bool bracketSwitch = false;
    bool substrInBrackets = false;
    string bracket = "[";

    while( ( position = str.find( bracket ) ) != string::npos ) 
    {
        if ( !bracketSwitch )
            bracket = "]";
        else 
            bracket = "[";
        

        bracketSwitch = !bracketSwitch; 

        token = str.substr( 0, position );
        str.erase( 0, position + 1 );

        if ( position != 0 ) 
        {

            if ( substrInBrackets )
                bracketSubStrings_.push_back( token );
            
            else
                noBracketSubstrings_.push_back( token );
            
            substrInBrackets = !substrInBrackets;
        }

        else
            substrInBrackets = true;

    }

    if ( str.length() > 0 )
        noBracketSubstrings_.push_back( str );
}



void PatternCheck::setPattern( string::iterator itr )
{
    pattern_.clear( );

    // TODO: pattern
    for ( int i = 0; i < patternNum_ * 2; i++ )
    {
        pattern_.push_back( *( itr + i ) );
    }
}

void PatternCheck::assignPatternSubstring( const string & str )
{
    patternSubstring_ = str;
}

bool PatternCheck::computeValidity( )
{
    if ( checkBrackets( bracketSubStrings_ ) )
    {
        valid_ = false;
        return false;
    }
    
    else if ( checkBrackets( noBracketSubstrings_ ) )
    {
        valid_ = true;
        sCorrect_++;
        return true;
    }

    valid_ = false;
    return false;
}

bool PatternCheck::checkBrackets( const vector<string> & vec)
{
    bool patternFound;

    for ( auto str : vec )
    {
        patternFound = scanSubstring( str );

        if (patternFound)
            return true;
    }

    return false;
}

int PatternCheck::computeRange(  )
{
    if ( patternNum_ == 1 )
        return 1;

    else
        return ( ( patternNum_ * 2 ) - 1 );

}

bool PatternCheck::scanSubstring( string & tempString )
{
    bool frontResult, backResult;

    int stepAhead = computeRange( );
    int stringLength = tempString.length( ); 
    int stringMidpoint = stringLength / 2;

    if ( stringLength < ( patternNum_ * 2 ) - 1 )
        return false;

    int alphaBitVector;

    string::iterator front = tempString.begin( );
    string::iterator back = tempString.end( ) - 1;  // 5

    for ( ; front + 3 != tempString.end( ); front++, back--)
    {
        alphaBitVector = 0;
        frontResult = matchRecursively( front, front + stepAhead, 
                                    patternNum_, alphaBitVector ); // 2

        if ( frontResult )
        {
            setCorrectValues( tempString, front );
            return true;
        }
    }

    return false;
}

bool PatternCheck::matchRecursively( string::iterator front, string::iterator back,
                                 int steps, int bitVector )
{
    bool unique;

    if ( *front == *back )
    {
        // cout << *front << " = " << *back << endl;
        int alphaIndex = computeAlphaIndexValue( *front );

        unique = ( ( bitVector & ( 1 << alphaIndex ) ) != 1 );

        if (alphaIndex != -1 && unique )
        {
            bitVector |= ( 1 << alphaIndex );

            if ( steps == 1 ) // 0 for 2, 1 for 3, pattern - 2
                return true;

            steps--;

            return( matchRecursively( front + 1, back - 1, steps, bitVector ) );
        
        }
    }

    return false;
}

int PatternCheck::computeAlphaIndexValue( char ch )
{
    int aValue = 'a';
    int zValue = 'z';
    int charValue = ch;

    if ( charValue >= aValue && charValue <= zValue )
    {
       return charValue - aValue; 
    }

    return -1;
}

void PatternCheck::setCorrectValues(string & substring, string::iterator front )
{
    int stepAhead = computeRange( );

    patternSubstring_ = substring;
    patternFirstIndex_ = front - substring.begin();
    patternLastIndex_ = patternFirstIndex_ + stepAhead; // 5

    setPattern(front);
}
