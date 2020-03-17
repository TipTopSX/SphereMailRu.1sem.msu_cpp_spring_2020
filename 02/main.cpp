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

void myParseWord(const std::string &word)
{
    tester.append("|");
    tester.append(word);
    tester.append("|");
}

void myParseNumber(int num)
{
    tester.append("^");
    tester.append(std::to_string(num));
    tester.append("^");
}

int main()
{
    char str[] = "Lorem ipsum   45\ndolor   sit 1914\tamet";
    tester = "";
    parse_callbacks::setOnBegin(myParseBegin);
    parse_callbacks::setOnEnd(myParseEnd);
    parse_callbacks::setOnWord(myParseWord);
    parse_callbacks::setOnNumber(myParseNumber);
    parse(str);
    assert(tester == "<<<Lorem ipsum   45\ndolor   sit 1914\tamet>>>|Lorem||ipsum|^45^|dolor||sit|^1914^|amet|___");
    std::cout << "OK" << std::endl;
}