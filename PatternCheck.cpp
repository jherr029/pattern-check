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

    // patternFirstIndex_++;
    // patternLastIndex_++;

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
    int strLength = tempStr.length( );

    if ( strLength < 4 )
        return false;

    int stringMidpoint = strLength / 2;

    bool evenLength = isStrEven( strLength );

    string::iterator itr = tempStr.begin( );
    string::iterator backItr = tempStr.end( ) - 1;

    string::iterator leftCenter;
    string::iterator rightCenter;

    bool smallStr = false;
    bool patternFound;
    

    if ( strLength < 10 )
    {
        leftCenter = backItr;
        rightCenter = backItr;

        smallStr = true;
    }

    else
    {
        if( evenLength )
        {
            rightCenter = itr + stringMidpoint;
            leftCenter = rightCenter - 1;

            patternFound = checkCenter( (rightCenter - 3), rightCenter, 4, tempStr );

            if ( patternFound )
            {
                assignPatternSubstring( tempStr );
                return true;
            }
        }

        else
        {
            leftCenter  = itr + stringMidpoint;
            rightCenter = leftCenter;

            patternFound = checkCenter( leftCenter - 2, leftCenter + 1, 2, tempStr );

            if ( patternFound )
            {
                assignPatternSubstring( tempStr );
                return true;
            }
        }
    }

    patternFound = iteratorLoop( itr, leftCenter, rightCenter, backItr, smallStr, tempStr ); 

    if ( patternFound )
    {
        assignPatternSubstring( tempStr );
        return true;
    }

    return false;

}

bool PatternCheck::checkCenter( string::iterator first, string::iterator fourth,
                                 int maxItr, string & substr )
{
    bool firstMatchesLast, middleMatches, firstTwoLegal, lastTwoLegal;

    for ( int i = 0; i < maxItr; i++, first++, fourth++ )
    {

        firstMatchesLast = ifMatch(*first, *fourth);
        middleMatches = ifMatch( *( first + 1 ), *( fourth - 1 ) );

        if (  firstMatchesLast && middleMatches )
        {
            firstTwoLegal = ifLegalMatch(*first, *(first + 1));
            lastTwoLegal = ifLegalMatch( *( fourth - 1 ), *fourth );

            if ( firstTwoLegal && lastTwoLegal )
            {
                patternFirstIndex_ = first - substr.begin( );
                patternLastIndex_ = patternFirstIndex_ + 3;

                setPattern( first, true );

                return true;
            }
        }
    }

    return false;
}

bool PatternCheck::iteratorLoop( string::iterator & front, string::iterator & leftCenter, 
                                string::iterator & rightCenter, string::iterator & back, 
                                bool smallStr, string & substr )
{
    bool patternFoundLeft, patternFoundRight;

    for ( ; front <= leftCenter - 3 && front + 3 <= leftCenter; front++, back--,
            leftCenter--, rightCenter++ )
    {
        if ( smallStr )
            patternFoundLeft = iteratorCheck( front, back, substr );

        else 
        {
            patternFoundLeft = iteratorCheck( front, leftCenter, substr );
            patternFoundRight = iteratorCheck( rightCenter, back, substr );
        }

        if ( patternFoundLeft || patternFoundRight )
            return true;
    }

    return false;
}

bool PatternCheck::iteratorCheck( string::iterator & front, string::iterator & back, string & substr )
{
    bool firstMatchesLast, middleMatches, firstTwoLegal, lastTwoLegal;

    firstMatchesLast = ifMatch( *front, *( front +  3 ) );
    middleMatches = ifMatch( *(front + 1), *( front + 2 ) );

    if ( firstMatchesLast && middleMatches ) 
    {
        firstTwoLegal = ifLegalMatch( *front, *( front + 1 ) );
        lastTwoLegal = ifLegalMatch( *( front + 2 ), *( front + 3 ) );

        if ( firstTwoLegal && lastTwoLegal )
        {
            setPattern( front, true );

            patternFirstIndex_ = front - substr.begin( );
            patternLastIndex_ = patternFirstIndex_ + 3;

            return true;
        }
    }


    else 
    {
        firstMatchesLast = ifMatch( *( back - 3 ), *back );
        middleMatches = ifMatch( *( back - 2 ), *( back - 1 ) );

        if ( firstMatchesLast && middleMatches )
        {
            firstTwoLegal = ifLegalMatch( *( back - 3 ), *( back - 2 ) );
            lastTwoLegal = ifLegalMatch( *( back - 1 ), *back );

            if ( firstTwoLegal && lastTwoLegal ) 
            {
                setPattern( back, false );

                patternFirstIndex_ = back - substr.begin( ) - 3;
                patternLastIndex_ = patternFirstIndex_ + 3;

                return true;
            }
        }
    }

    return false;
}

bool PatternCheck::ifMatch( char a, char b)
{
    if ( a == b )
        return true;
    
    return false;
}

bool PatternCheck::ifLegalMatch( char a, char b)
{
    if ( a != b )
        return true;
    
    return false;
}

// scalable through vector??