#include "patternCheck.h"

patternCheck::patternCheck( const string & str )
{
    fileStr = str;
    pattern = "NO PATTERN FOUND";
    patternSubstring = "NO PATTERN FOUND";

    startPosition = -999;
    endPosition = -999;
}

void patternCheck::assignVectors( )
{

    string str = this->fileStr;

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
                subStrBrackets.push_back( token );
            
            else
                subStrNoBrackets.push_back( token );
            
            substrInBrackets = !substrInBrackets;
        }

        else
            substrInBrackets = true;

    }

    if ( str.length() > 0 )
        subStrNoBrackets.push_back( str );
}

void patternCheck::printString( )
{
    cout << this->fileStr << endl;
}

void patternCheck::printValidity( )
{
    if ( valid )
        cout << "True" << " - pattern " << pattern << " " << patternSubstring << endl;

    else
    {
        if ( pattern.length() != 0 )
            cout << "    False  -- pattern " << pattern << " found inside []" << endl;
        else
            cout << "  False - no patterns found" << endl;
    }
}

void patternCheck::setPattern( string::iterator itr, bool forward )
{
    pattern.clear( );

    for ( int i = 0; i < 4; i++ )
    {
        if ( forward )
            pattern.push_back( *( itr + i ) );
        else
            pattern.push_back( *( itr - i ) );
    }
}

string patternCheck::printCorrectPatterns( bool brackets )
{
    string tempStr;

    patternSubstring.insert( startPosition, "(" );
    patternSubstring.insert( endPosition + 2, ")" );

    if ( !brackets )
        tempStr = "Pattern " + pattern + "\n" + patternSubstring + "\n" + fileStr + "\n";

    else
        tempStr = "Pattern " + pattern + "\n[" + patternSubstring + "]\n" + fileStr + "\n";

    startPosition++;
    endPosition++;

    return tempStr;
}

void patternCheck::printIncorrectPatterns( )
{
    if ( pattern == "NO PATTERN FOUND" )
        return;

    else
        printCorrectPatterns( true );
}

bool patternCheck::checkBrackets( )
{
    bool patternFound;

    for ( auto str : subStrBrackets )
    {
        patternFound = checker( str );

        if (patternFound)
            return true;
    }

    return false;
}

bool patternCheck::checkOutsideBrackets( )
{
    bool patternFound;

    for ( auto str : subStrNoBrackets )
    {
        patternFound = checker( str );

        if ( patternFound )
            return true;
    }

    return false;
}

bool patternCheck::isStrEven( int strLength )
{
    return ( ( strLength % 2 ) == 0 );
}

bool patternCheck::checker( string & tempStr )
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

            patternFound = checkCenter( rightCenter - 3, rightCenter, 4, tempStr );

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

bool patternCheck::checkCenter( string::iterator first, string::iterator fourth,
                                 int maxItr, string & substr )
{

    for ( int i = 0; i < maxItr; i++, first++, fourth++ )
    {
        if (  ( *first == *fourth ) && ( *( first + 1 ) == *( fourth - 1 ) ) )
        {
            if ( *first != *( first + 1 ) && *( fourth - 1 ) != *fourth )
            {
                startPosition = first - substr.begin( );
                endPosition = startPosition + 3;

                setPattern( first, true );

                return true;
            }
        }
    }

    return false;
}

bool patternCheck::iteratorLoop( string::iterator front, string::iterator leftCenter, 
                                string::iterator rightCenter, string::iterator back, 
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

bool patternCheck::iteratorCheck( string::iterator front, string::iterator back, string & substr )
{
    if ( ( *front == *( front + 3 ) ) && ( * ( front + 1 ) == *( front + 2 ) ) ) 
    {
        if ( *front != *( front + 1 ) && *( front + 2 ) != *( front + 3 ) )
        {
            setPattern( front, true );

            startPosition = front - substr.begin( );
            endPosition = startPosition + 3;

            return true;
        }
    }

    else if ( ( *( back - 3 ) == *back ) && ( *( back - 2 ) == *( back - 1 ) ) )
    {
        if ( *( back - 3 ) != *( back - 2 ) && *( back - 1 ) != *back ) 
        {
            setPattern( back, false );

            startPosition = back - substr.begin( ) - 3;
            endPosition = startPosition + 3;

            return true;
        }
    }

    return false;
}

