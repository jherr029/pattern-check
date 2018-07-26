#include "patternCheck.h"


patternCheck::patternCheck(const string & str)
{
    fileStr = str;
}

string patternCheck::getString()
{
    cout << "hi" << endl;
    return "hi";
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
        cout << "\t\t\tTrue" << " - pattern " << pattern << endl;
        int x = 0;
    }
    else
    {
        int y = 0;

        cout << "\t\t\t\tFalse";

        if (pattern.length() != 0)
            cout << " - pattern " << pattern << " found inside []" << endl;
        else
            cout << " - no patterns found" << endl;
    }
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

bool patternCheck::checker(string & tempStr)
{

    // cout << "checker --- " << tempStr << " - " << tempStr.length() << endl;

    bool evenLength;
    int stringMidpoint = tempStr.length() / 2;

    if (tempStr.length() < 4)
        return false;

    if ( (tempStr.length() % 2) == 0 )
    {
        evenLength = true;
    }

    else
    {

        evenLength = false;
    }


    string::iterator itr = tempStr.begin();
    string::iterator backItr = tempStr.end() - 1;


    string::iterator leftCenter;
    string::iterator rightCenter; 

    // cout << "length: " << tempStr.length() << endl;

    int i = 0;
    bool patternFoundLeft;
    bool patternFoundRight = false;
    bool smallStr = false;

    // cout << "Str: " << tempStr << " ";

    if (tempStr.length() < 6)
    {
        leftCenter = backItr;
        rightCenter = backItr;

        smallStr = true;
    }

    if (evenLength)
    {
        // cout << "even " << endl;
        
        if (tempStr.length() >= 6)
        {

            rightCenter = itr + stringMidpoint;
            leftCenter = rightCenter - 1;

            if (checkCenter(rightCenter - 3, rightCenter, 4))
                return true;

            // cout << *rightCenter << endl;

            // cout << *rightCenter << *(rightCenter+1) << *(rightCenter+2) <<  *(rightCenter+3) << endl;
        }

        // cout << "rightCenter: " << *rightCenter << " peek:" << *peekRightCenter << endl; 

        // cout << *leftCenter << endl;

        // check the middle for both odd and even

        // for (; (itr <= peekBackItr) && (peekAheadItr <= backItr); itr++, peekAheadItr++, backItr--, peekBackItr-- )
        for( ; itr <= leftCenter - 3 && itr + 3 <= leftCenter; itr++, backItr--,
                leftCenter--, rightCenter++)
        {

            // cout << "inisde for loop" << endl;
            if (smallStr)
                patternFoundLeft = iteratorCheck(itr, backItr);

            else 
            {
                patternFoundLeft = iteratorCheck(itr, leftCenter);
                patternFoundRight = iteratorCheck(rightCenter, backItr);
            }

            if (patternFoundLeft || patternFoundRight)
                return true;
            
            // cout << i << endl;
            i++;
        }

    }

    else
    {

        // cout << "odd " << endl;
        if (tempStr.length() >= 6) 
        {
            leftCenter  = itr + stringMidpoint;
            rightCenter = leftCenter;

            if (checkCenter(leftCenter - 2, leftCenter + 1, 2))
                return true;
        }

        
        // cout << *rightCenter << " " << *peekRightCenter << endl; 
        // orignal
        for( ; itr <= leftCenter - 3 && itr + 3 <= leftCenter; itr++, backItr--,
                leftCenter--,  rightCenter++)
        {
            // cout << *rightCenter << *peekRightCenter << " - ";
            // cout << *peekBackItr << *backItr << endl;

            // patternFound = iteratorCheck(itr, peekAheadItr, peekBackItr, backItr);
            if (smallStr)
                patternFoundLeft =iteratorCheck(itr, backItr);
            
            else
            {
                patternFoundLeft = iteratorCheck(itr, leftCenter);
                patternFoundRight = iteratorCheck(rightCenter, backItr);
            }


            if (patternFoundLeft || patternFoundRight)
                return true;

            // cout << i << " ---> " << peekBackItr - peekAheadItr << endl;
            // cout << i << endl;
            i++;
        }
    }


    return false;
}

bool patternCheck::checkCenter(string::iterator first, string::iterator fourth, int maxItr)
{
    for ( int i = 0; i < maxItr; i++, first++, fourth++)
    {
        if ( (*first == *fourth) && (*(first + 1) == *(fourth - 1)) )
        {
            return true;
        }

    }

    return false;
}

bool patternCheck::iteratorCheck(string::iterator front, string::iterator back)
{

    if ( ( *front == *( front + 3 ) ) && ( * ( front + 1 ) == *( front + 2 ) ) ) 
    {
        setPattern( front, true );
        return true;
    }

    else if ( ( *( back - 3 ) == *back ) && ( *( back - 2 ) == *( back - 1 ) ) )
    {
        setPattern( back, false );
        return true;
    }

    return false;
}

void patternCheck::setPattern(string::iterator itr, bool forward)
{
    for ( int i = 0; i < 4; i++ )
    {
        if (forward)
            pattern.push_back(*(itr + i));
        else
            pattern.push_back(*(itr - i));
    }
}