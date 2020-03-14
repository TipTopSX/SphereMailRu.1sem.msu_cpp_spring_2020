#include <iostream>
#include "parse.hpp"

std::string tester;

void myParseBegin(const char *str)
{
    tester.append("<<<");
    tester.append(str);
    tester.append(">>>");
}

void myParseEnd()
{
    tester.append("___");
}

void myParseWord(char *word)
{
    tester.append("|");
    tester.append(word);
    tester.append("|");
}

void myParseNumber(char *num)
{
    tester.append("^");
    tester.append(num);
    tester.append("^");
}

int main()
{
    char str[] = "Lorem ipsum   45\ndolor   sit 1914\tamet";
    tester = "";
    setParseBegin(myParseBegin);
    setParseEnd(myParseEnd);
    setParseWord(myParseWord);
    setParseNumber(myParseNumber);
    parse(str);
    assert(tester == "<<<Lorem ipsum   45\ndolor   sit 1914\tamet>>>|Lorem||ipsum|^45^|dolor||sit|^1914^|amet|___");
    std::cout << "OK" << std::endl;
}