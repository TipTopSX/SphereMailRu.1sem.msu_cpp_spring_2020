#include <cstring>
#include <cctype>
#include "parse.hpp"

void (*parseBegin)(const char *);

void (*parseEnd)();

void (*parseWord)(char *);

void (*parseNumber)(char *);

void setParseBegin(void (*callback)(const char *))
{
    parseBegin = callback;
}

void setParseEnd(void (*callback)())
{
    parseEnd = callback;
}

void setParseWord(void (*callback)(char *))
{
    parseWord = callback;
}

void setParseNumber(void (*callback)(char *))
{
    parseNumber = callback;
}

void parse(char *input)
{
    parseBegin(input);
    char *pch = strtok(input, " \n\t");
    while (pch != nullptr) {
        if (isdigit(pch[0])) {
            parseNumber(pch);
        } else {
            parseWord(pch);
        }
        pch = strtok(nullptr, " \n\t");
    }
    parseEnd();
}