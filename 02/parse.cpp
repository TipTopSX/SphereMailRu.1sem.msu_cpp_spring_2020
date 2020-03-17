#include <cstring>
#include <cctype>
#include <cstdlib>
#include <string>
#include "parse.hpp"

namespace parse_callbacks {

    void (*onBegin)(const char *);

    void (*onEnd)();

    void (*onWord)(const std::string &);

    void (*onNumber)(int);

    void setOnBegin(void (*callback)(const char *))
    {
        parse_callbacks::onBegin = callback;
    }

    void setOnEnd(void (*callback)())
    {
        parse_callbacks::onEnd = callback;
    }

    void setOnWord(void (*callback)(const std::string &))
    {
        parse_callbacks::onWord = callback;
    }

    void setOnNumber(void (*callback)(int))
    {
        parse_callbacks::onNumber = callback;
    }

}

void parse(const char *input)
{
    parse_callbacks::onBegin(input);
    char *pch = strtok(strdup(input), " \n\t");
    while (pch != nullptr) {
        std::string s = std::string(pch);
        if (isdigit(pch[0])) {
            parse_callbacks::onNumber(stoi(s));
        } else {
            parse_callbacks::onWord(s);
        }
        pch = strtok(nullptr, " \n\t");
    }
    parse_callbacks::onEnd();
}