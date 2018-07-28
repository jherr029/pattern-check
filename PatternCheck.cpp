#include "PatternCheck.h"

int PatternCheck::sCorrect_ = 0;
int PatternCheck::sLineNumber_ = 0;

PatternCheck::PatternCheck( const string & str )
{
    valid_ = false;

    fileLine_ = str;
    pattern_ = "NO PATTERN FOUND";
    patternSubstring_ = "NO PATTERN FOUND";

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

bool PatternCheck::isStrEven( int strLength )
{
    return ( ( strLength % 2 ) == 0 );
}

bool PatternCheck::isValid( )
{
    return valid_;
}

string PatternCheck::printCorrectPatterns( bool brackets )
{
    string tempStr;
    string tempSubstr = patternSubstring_;


    tempSubstr.insert( patternFirstIndex_, "(" );
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

    string str = this->fileLine_;

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

void PatternCheck::setPattern( string::iterator itr, bool forward )
{
    pattern_.clear( );

    // TODO: pattern
    for ( int i = 0; i < 4; i++ )
    {
        if ( forward )
            pattern_.push_back( *( itr + i ) );
        else
            pattern_.push_back( *( itr - i ) );
    }
}

void PatternCheck::assignPatternSubstring( const string & str )
{
    patternSubstring_ = str;
}


bool PatternCheck::checkBrackets( const vector<string> & vec)
{
    bool patternFound;

    for ( auto str : vec )
    {
        patternFound = checker( str );

        if (patternFound)
            return true;
    }

    return false;
}

bool PatternCheck::checker( string & tempStr )
{
    bool frontResult, backResult;
    int strLength = tempStr.length( ); 
    int stringMidpoint = strLength / 2;

    if ( strLength < 3 )
        return false;

    int alphaArray[26] = {0};

    string::iterator front = tempStr.begin( );
    string::iterator back = tempStr.end( ) - 1;  // 5

    for ( ; front != tempStr.end( ); front++, back--)
    {
        int alphaArray[26] = {0};
        frontResult = recursive( front, front + 3, 2, alphaArray); // 2

        if ( frontResult )
        {
            setCorrectValues( tempStr, front );
            return true;
        }

        // fill_n(alphaArray, 26, 0);
        // backResult = recursive( back - 3, back, 2, alphaArray); // 2

        // if (backResult)
        // {
        //     // cout << "BACK" << endl;
        //     setCorrectValues( tempStr, back - 3 );
        //     return true;

        // }

        // fill_n(alphaArray, 26, 0);

    }

    return false;

}

bool PatternCheck::recursive(string::iterator front, string::iterator back, int steps, int array[26])
{
    if ( *front == *back )
    {
        int alphaIndex = computeAlphaIndexValue(*front);

        if (alphaIndex != -1 && array[alphaIndex] != 1 )
        {
            array[alphaIndex] = 1;

            if ( steps == 1 ) // 0 for 2, 1 for 3, pattern - 2
                return true;

            steps--;

            return( recursive( front + 1, back - 1, steps, array ) );
        
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
    patternSubstring_ = substring;
    patternFirstIndex_ = front - substring.begin();
    patternLastIndex_ = patternFirstIndex_ + 3; // 5
    valid_ = true;

    setPattern(front, true);
}
// bool PatternCheck::checkNeighbors( string::iterator front, string::iterator back, string & substring )
// {
//     if ( front != substring.begin( ) )
//     {
//         if ( *front == *( front - 1 ) )
//             return false;
//     }

//     else
//         return false;

//     if ( back != substring.end() - 1 ) 
//     {
//         if ( *back == *( back + 1) )
//             return false;
//     }

//     return true;
// }
