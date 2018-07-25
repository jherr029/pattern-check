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
    string::iterator peekAheadItr = itr + 3;
    
    string::iterator backItr = tempStr.end() - 1;
    string::iterator peekBackItr = backItr - 3;

    string::iterator leftCenter;
    string::iterator peekLeftCenter;

    string::iterator rightCenter; 
    string::iterator peekRightCenter;

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

        peekLeftCenter = peekAheadItr;
        peekRightCenter = peekAheadItr;
        smallStr = true;
    }

    if (evenLength)
    {
        // cout << "even ";
        
        if (tempStr.length() >= 6)
        {

            rightCenter = itr + stringMidpoint;
            leftCenter = rightCenter - 1;

            peekLeftCenter = leftCenter - 3;
            peekRightCenter = rightCenter + 3;

            if (checkCenter(rightCenter - 3, rightCenter, 4))
                return true;

            // cout << *rightCenter << endl;

            // cout << *rightCenter << *(rightCenter+1) << *(rightCenter+2) <<  *(rightCenter+3) << endl;
        }

        // cout << "rightCenter: " << *rightCenter << " peek:" << *peekRightCenter << endl; 

        // cout << *leftCenter << endl;

        // check the middle for both odd and even

        // for (; (itr <= peekBackItr) && (peekAheadItr <= backItr); itr++, peekAheadItr++, backItr--, peekBackItr-- )
        for( ; (itr <= peekLeftCenter) && (peekAheadItr <= leftCenter); 
                itr++, peekAheadItr++, backItr--, peekBackItr--, leftCenter--,
                    peekLeftCenter--, rightCenter++, peekRightCenter++)
        {

            // cout << "inisde for loop" << endl;
            patternFoundLeft = iteratorCheck(itr, peekAheadItr, peekLeftCenter, leftCenter);

            if (!smallStr)
                patternFoundRight = iteratorCheck(rightCenter, peekRightCenter, peekBackItr, backItr);

            if (patternFoundLeft)
                return true;
            
            else if (patternFoundRight)
                return true;
            
            // cout << i << endl;
            i++;
        }

    }

    else
    {

        if (tempStr.length() >= 6) 
        {
            leftCenter  = itr + stringMidpoint;
            rightCenter = leftCenter;

            peekLeftCenter = leftCenter - 3;
            peekRightCenter = rightCenter + 3;

            if (checkCenter(leftCenter - 2, leftCenter + 1, 2))
                return true;
        }

        
        // cout << "odd "; 
        // cout << *rightCenter << " " << *peekRightCenter << endl; 
        // orignal
        for( ; itr <= peekLeftCenter && peekAheadItr <= leftCenter; 
                itr++, peekAheadItr++, backItr--, peekBackItr--, leftCenter--,
                    peekLeftCenter--, rightCenter++, peekRightCenter++)
        {
            // cout << *rightCenter << *peekRightCenter << " - ";
            // cout << *peekBackItr << *backItr << endl;

            // patternFound = iteratorCheck(itr, peekAheadItr, peekBackItr, backItr);
            patternFoundLeft = iteratorCheck(itr, peekAheadItr, peekLeftCenter, leftCenter);

            if (!smallStr)
                patternFoundRight = iteratorCheck(rightCenter, peekRightCenter, peekBackItr, backItr);

            if (patternFoundLeft)
                return true;
            
            else if (patternFoundRight)
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

bool patternCheck::iteratorCheck(string::iterator front, string::iterator frontPeek, string::iterator backPeek, string::iterator back)
{
    // cout << "1)" << *front << " 2)" << *frontPeek << " 3)" << *backPeek << " 4)" << *back << endl;

    // if ((*front == '\000' && *frontPeek == '\000' ) || (*backPeek =='\000' && *back == '\000'))
    // {
    //     cout << "WE HAVE NULL" << endl;
    //     return false;
    // }

    if (*front == *frontPeek)
    {
        // cout << "front" << endl;

        if (*(front + 1 ) == *(frontPeek - 1) )
        {
            pattern.push_back(*front);
            pattern.push_back(*(front + 1));
            pattern.push_back(*(frontPeek - 1));
            pattern.push_back(*frontPeek);
            // cout << "front is true" << endl;
            return true;
        }
    }

    else if (*backPeek == *back)
    {
        // cout << "back" << endl;

        if (*(backPeek + 1) == *(back - 1))
        {
            pattern.push_back(*backPeek);
            pattern.push_back(*(backPeek + 1));
            pattern.push_back(*(back - 1));
            pattern.push_back(*back);
            // cout << "back is true" << endl;
            return true;
        }
    }

    // else if (*front == *backPeek)
    // {
    //     cout << "both" << endl;

    //     if (*frontPeek == *back)
    //     {
    //         pattern.push_back(*front);
    //         pattern.push_back(*frontPeek);
    //         pattern.push_back(*backPeek);
    //         pattern.push_back(*back);
    //         // cout << pattern << endl;
        
    //         return true;
    //     }
    // }
    
    // cout << "RETURNING FALSE" << endl;

    return false;
}