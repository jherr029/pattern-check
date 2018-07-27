import string
from random import *

pairInBrackets = False

def getRandomString():
    minChar = 3
    maxChar = 21
    possibleChar = string.ascii_lowercase

    return ("".join(choice(possibleChar) for x in range(randint(minChar, maxChar))))

def getRandomPair():
    firstChar = choice(string.ascii_lowercase)
    secondChar = choice(string.ascii_lowercase)

    while firstChar == secondChar:
        firstChar = choice(string.ascii_lowercase)
        secondChar = choice(string.ascii_lowercase)

    pair = firstChar + secondChar + secondChar + firstChar

    return pair

def createUniqueString(str):

    tempStr = "".join(set(str))

    while len(tempStr) < 3:
        tempStr = getRandomString()
        tempStr = "".join(set(tempStr))

    return tempStr


def checkIfPatternExists(firstStr, secondStr):

    firstStr += "?"
    secondStr += "@"


    for i in range(3):

        if firstStr[i] == secondStr[i]:
            # print(firstStr, secondStr)

            if firstStr[i + 1] == "?":
                if secondStr[i - 2] == secondStr[i - 1]:
                    if firstStr[i] != secondStr[i - 2] and secondStr[i-1] != secondStr[i]:
                        print ("first", firstStr[i], secondChar[i - 2], secondStr[i-1], secondStr[i])
                        # print("true")
                        return True

            elif firstStr[i + 1] == firstStr[i + 2]:
                if firstStr[i] != firstStr[i + 1] and firstStr[i + 2] != secondStr[i]:
                    print ( "second", firstStr[i], firstStr[i + 1], firstStr[i + 2], secondStr[i])
                    return True


            elif firstStr[i + 1] == secondStr[i - 1]:
                if firstStr[i] != firstStr[i + 1] and secondStr[i] != secondStr[i + 1]:
                    # print ( "third", firstStr[i], firstStr[i + 1], secondStr[i-1], secondStr[i])
                    # print("true")
                    return True


    return False


def writeToFile(testFile):

    correctFile = open("correct.txt", "w")
    senFile = open("cool.txt", "w")
    line = 1


    myList = []
    validList = []
    # patternObj = pattern()

    for i in range(10000):

        patternCode = 0
        valid = False
        pairInBrackets = False
        pair = newString = randomString = randomString2 = ""

        for i in range(randint(3, 6)):

            randNum = randint(1, 100)
            if randNum <= 33:
                valid = True
                validList.append(True)
                patternCode = 1
                pair = getRandomPair()

            randomString = createUniqueString( getRandomString() )
            senFile.write(randomString + " ");
            senFile.write(pair + " ")

            if ( len(newString) > 0 and len(randomString) ):
                valid = checkIfPatternExists(newString[-3:], randomString[:3])
            else:
                valid = False

            if valid:
                # print("FIXED IT !!!")
                validList.append(True)
            newString = newString + randomString + pair

            valid = checkIfPatternExists(newString[-3:], randomString[:3])
            if valid:
                validList.append(True)

            bracketToggle = randint(0,2)
            if bracketToggle > 0:
                randomString = getRandomString()
                randomString = createUniqueString(randomString)
                senFile.write(" [" + randomString + " ")

                randomString2 = getRandomString()
                randomString2 = createUniqueString(randomString2)

                pairInBrackets = checkIfPatternExists(randomString[-3:], randomString2[:3])
                if pairInBrackets:
                    myList.append(True)

                randNum = randint(1, 100)
                if randNum <= 33:
                    pair = getRandomPair()
                    myList.append(True)
                    # print(pair)
                    senFile.write(pair + " ")
                    pairInBrackets = True
                    valid = False
                    # print("\t\t", pair, pairInBrackets)

                else:
                    pair = ""

                senFile.write(randomString2 + "] ")

                newString = newString + "[" + randomString + pair + randomString2 + "]"

            randomString = createUniqueString( getRandomString())
            senFile.write(randomString + " ")
            valid = checkIfPatternExists(newString[-3:], randomString[:3])
            if valid:
                validList.append(True)

            newString = newString + randomString
            senFile.write(" || ")


        testFile.write(newString + "\n")

        # print("Length ",len(myList))

        if  len(myList) != 0:
            temp = myList.pop()
        else:
            temp = False

        if len(validList) != 0:
            valid = validList.pop()

        if temp:
            toWrite = False

        elif valid:
            toWrite = True
        else:
            toWrite = False

        senFile.write(" -- " + str(temp) + " -- " + str(valid) + " " + str(toWrite) + "\n")

        # print()
        # print("%temp: ", temp )
        # print("%valid: ", valid)

        if temp != True:
            if valid == True:
                # print("\t\t\t", line)
                correctFile.write(str(line) + "\n")

        myList = []
        validList = []

        line += 1
        # print("-" * 40)

    senFile.close()
    testFile.close()
    correctFile.close()



def main():

    testFile = open("testFile.txt", "w")

    writeToFile(testFile)


    print("hi")
    # my code here


if __name__ == "__main__":
    main()
