#include <cstring>
#include <cctype>
#include <cstdlib>
#include <string>
#include "parse.hpp"

namespace parse {
    t_onBegin onBegin;
    t_onEnd onEnd;
    t_onWord onWord;
    t_onNumber onNumber;


    void setOnBegin(t_onBegin callback)
    {
        parse::onBegin = callback;
    }

    void setOnEnd(t_onEnd callback)
    {
        parse::onEnd = callback;
    }

    void setOnWord(t_onWord callback)
    {
        parse::onWord = callback;
    }

    void setOnNumber(t_onNumber callback)
    {
        parse::onNumber = callback;
    }

    void call(const char *begin, const char *end)
    {
        std::string s(begin, 0, end - begin);
        if (isdigit(*begin))
            parse::onNumber(stoi(s));
        else
            parse::onWord(s);
    }

    void parse(const char *input)
    {
        parse::onBegin(input);
        const char *pch = input;
        bool inToken = false;
        const char *begin = input;
        while (*pch) {
            if (!isspace(*pch) && !inToken)
                begin = pch;
            if (isspace(*pch) && inToken)
                call(begin, pch);
            inToken = isspace(*pch) == 0;
            ++pch;
        }
        if (inToken)
            call(begin, pch);
        parse::onEnd();
    }
}