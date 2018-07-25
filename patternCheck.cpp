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
        cout << "True" << endl;
    else
        cout << "False" << endl;
}

bool patternCheck::checkBrackets()
{
    // do two sets of iterators
    // one from the beginning and the other from the end
    for ( auto str : subStrBrackets )
        if (checker(str))
            return true;

    return false;
}

bool patternCheck::checkOutsideBrackets()
{
    for ( auto str : subStrNoBrackets )
        if (checker(str))
            return true;

    return false;
}

bool patternCheck::checker(string & tempStr)
{

    bool evenLength;

    if ( (tempStr.length() % 2) == 0 )
        evenLength = true;
    else
        evenLength = false;

    string::iterator itr = tempStr.begin();
    string::iterator peekAheadItr = itr + 3;
    
    string::iterator backItr = tempStr.end();
    string::iterator peekBackItr = backItr - 3;

    cout << "length: " << tempStr.length() << endl;

    int i = 0;

    if (evenLength)
    {
        for (; itr == peekBackItr && peekAheadItr == backItr; itr++, peekAheadItr++, backItr--, peekBackItr-- )
        {
            if(iteratorCheck(*itr, *(itr + 1), *(peekAheadItr - 1), *peekAheadItr))
                return true;
        }

    }
    else
    {
        for (; peekAheadItr != tempStr.end(); itr++, peekAheadItr++, backItr--, peekBackItr--)
        {

            if(iteratorCheck(*itr, *(itr + 1), *(peekAheadItr - 1), *peekAheadItr))
                return true;

            cout << i << " ---> " << peekBackItr - peekAheadItr << endl;
            i++;
        }
    }


    return false;
}

bool patternCheck::iteratorCheck(char first, char second, char third, char fourth)
{
    if (first == fourth)
        if (second == third)
            return true;
    
    return false;
}
        //         pattern.push_back(*itr);
        //         pattern.push_back(*(itr + 1));
        //         pattern.push_back(*(peekAheadItr - 1));
        //         pattern.push_back(*peekAheadItr);
        //         cout << pattern << endl;