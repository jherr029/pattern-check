#include "patternCheck.h"


patternCheck::patternCheck(const string & str)
{
    fileStr = str;
    pattern = "NO PATTERN FOUND";
    patternSubstring = "NO PATTERN FOUND";

    startPosition = -999;
    endPosition = -999;
}

string patternCheck::getString()
{
    cout << "hi" << endl;
    return "hi";
}

void patternCheck::assignPatternSubstring(const string & str)
{
    patternSubstring = str;
}


void patternCheck::assignVectors()
{

    string str = this->fileStr;

    size_t position = 0;
    string token;

    bool bracketSwitch = false;
    bool substrInBrackets = false;
    string bracket = "[";

    while( (position = str.find( bracket )) != string::npos ) 
    {
        if (!bracketSwitch)
            bracket = "]";
        else 
            bracket = "[";
        

        bracketSwitch = !bracketSwitch; 

        token = str.substr(0, position);
        str.erase(0, position + 1);

        if (position != 0 ) 
        {

            if (substrInBrackets)
                subStrBrackets.push_back(token);
            
            else
                subStrNoBrackets.push_back(token);
            
            substrInBrackets = !substrInBrackets;
        }

        else
            substrInBrackets = true;

    }

    if ( str.length() > 0 )
    {
        // cout << " --- " <<  str << endl;
        subStrNoBrackets.push_back(str);
    }

    // cout << endl;
    // cout << "With brackets " << endl;
    // for ( auto ele : subStrBrackets )
    //     cout << ele << endl;;

    // cout << "\nWithout brackets" << endl;
    // for ( auto ele : subStrNoBrackets )
    //     cout << ele << endl;
    
    //cout << "test" << endl;
}

void patternCheck::printString()
{
    cout << this->fileStr << endl;
}

void patternCheck::printValidity()
{
    if (valid)
    {
        cout << "True" << " - pattern " << pattern << " ";
    }
    else
    {

        if (pattern.length() != 0)
            cout << "    False  -- pattern " << pattern << " found inside []" << endl;
        else
            cout << "  False - no patterns found" << endl;
    }
}

void patternCheck::printCorrectPatterns(bool brackets)
{
    patternSubstring.insert(startPosition, "(");
    patternSubstring.insert(endPosition + 2, ")");

    cout << "Pattern " << pattern << " in substring ";
    if (!brackets)
        cout << patternSubstring << endl;

    else
    {
        cout << "[" << patternSubstring << "]" << endl;
    }

    startPosition++;
    endPosition++;

    // cout << patternSubstring[startPosition] << patternSubstring[startPosition + 1];
    // cout << patternSubstring[endPosition - 1] << patternSubstring[endPosition] << endl;

    cout << endl;

}

void patternCheck::printIncorrectPatterns()
{
    if (pattern == "NO PATTERN FOUND")
        return;
    
    else
        printCorrectPatterns(true);



}

bool patternCheck::checkBrackets()
{
    bool patternFound;
    // cout << "checkBrackets" << endl;
    // do two sets of iterators
    // one from the beginning and the other from the end
    for ( auto str : subStrBrackets )
    {
        // cout << str << endl;
        patternFound = checker(str);

        if (patternFound)
        {
            // cout << "crap" << endl;
            return true;
        }
    }

    return false;
}

bool patternCheck::checkOutsideBrackets()
{
    bool patternFound;
    // cout << "checkOutsideBrackets" << endl;

    for ( auto str : subStrNoBrackets )
    {
        patternFound = checker(str);

        if (patternFound)
            return true;
    }

    return false;
}

bool patternCheck::isStrEven(int strLength){
    return ((strLength % 2) == 0);
}

bool patternCheck::checker(string & tempStr)
{
    int strLength = tempStr.length();

    if (strLength < 4)
        return false;
    // cout << "checker --- " << tempStr << " - " << tempStr.length() << endl;

    int stringMidpoint = strLength / 2;

    bool evenLength = isStrEven(strLength);

    string::iterator itr = tempStr.begin();
    string::iterator backItr = tempStr.end() - 1;

    string::iterator leftCenter;
    string::iterator rightCenter; 

    bool smallStr = false;

    if (strLength < 10)
    {
        leftCenter = backItr;
        rightCenter = backItr;

        smallStr = true;
    }

    else
    {
        if(evenLength)
        {
            rightCenter = itr + stringMidpoint;
            leftCenter = rightCenter - 1;

            if (checkCenter(rightCenter - 3, rightCenter, 4, tempStr))
            {
                assignPatternSubstring(tempStr);
                return true;
            }
        }

        else
        {
            leftCenter  = itr + stringMidpoint;
            rightCenter = leftCenter;

            if (checkCenter(leftCenter - 2, leftCenter + 1, 2, tempStr))
            {
                assignPatternSubstring(tempStr);
                return true;
            }
        }
    }

    if (iteratorLoop(itr, leftCenter, rightCenter, backItr, smallStr, tempStr))
    {
        assignPatternSubstring(tempStr);
        return true;
    }

    false;

}

bool patternCheck::checkCenter(string::iterator first, string::iterator fourth,
                                 int maxItr, string & substr)
{

    // int startPos, endPos;

    // if (maxItr == 4)
    // {
    //     startPos = midPoint - 3;
    //     endPos = midPoint;
    // }

    // else if (maxItr == 2)
    // {
    //     startPos = midPoint - 2;
    //     endPos = midPoint + 1;
    // }

    for ( int i = 0; i < maxItr; i++, first++, fourth++)
    {
        if (*first == *(first + 1) || *fourth == *(fourth - 1) )
            return false;

        if (  (*first == *fourth) && ( *( first + 1 ) == *( fourth - 1 ) ) )
        {
            // cout << *first << *(first + 1) << *(first + 2) << *(first + 3) << endl;

            startPosition = first - substr.begin();
            endPosition = startPosition + 3;
            setPattern(first, true);
            return true;
        }

    }

    return false;
}

bool patternCheck::iteratorLoop(string::iterator front, string::iterator leftCenter, 
                                string::iterator rightCenter, string::iterator back, 
                                bool smallStr, string & substr)
{

    bool patternFoundLeft, patternFoundRight;

    for( ; front <= leftCenter - 3 && front + 3 <= leftCenter; front++, back--,
            leftCenter--, rightCenter++)
    {

        // cout << "inisde for loop" << endl;
        if (smallStr)
            patternFoundLeft = iteratorCheck(front, back, substr);

        else 
        {
            patternFoundLeft = iteratorCheck(front, leftCenter, substr);
            patternFoundRight = iteratorCheck(rightCenter, back, substr);
        }

        if ( patternFoundLeft || patternFoundRight)
            return true;

    }

    return false;
}

bool patternCheck::iteratorCheck(string::iterator front, string::iterator back, string & substr)
{
    if ( *front == *( front + 1 ) || *back == *(back - 1 ) )
        return false;

    if ( ( *front == *( front + 3 ) ) && ( * ( front + 1 ) == *( front + 2 ) ) ) 
    {
        setPattern( front, true );
        startPosition = front - substr.begin();
        endPosition = startPosition + 3;
        // startAddress = front;
        // endAddress = front + 3;
        return true;
    }

    else if ( ( *( back - 3 ) == *back ) && ( *( back - 2 ) == *( back - 1 ) ) )
    {
        setPattern( back, false );
        startPosition = back - substr.begin() - 3;
        endPosition = startPosition + 3;
        return true;
    }

    return false;
}

void patternCheck::setPattern(string::iterator itr, bool forward)
{

    pattern.clear();

    for ( int i = 0; i < 4; i++ )
    {
        if (forward)
            pattern.push_back(*(itr + i));
        else
            pattern.push_back(*(itr - i));
    }
}

    // for( ; itr <= leftCenter - 3 && itr + 3 <= leftCenter; itr++, backItr--,
    //         leftCenter--, rightCenter++)
    // {

    //     // cout << "inisde for loop" << endl;
    //     if (smallStr)
    //         patternFoundLeft = iteratorCheck(itr, backItr);

    //     else 
    //     {
    //         patternFoundLeft = iteratorCheck(itr, leftCenter);
    //         patternFoundRight = iteratorCheck(rightCenter, backItr);
    //     }

    //     if (patternFoundLeft || patternFoundRight)
    //         return true;
        
    //     // cout << i << endl;
    // }

    // return false;