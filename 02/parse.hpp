#pragma once
#ifndef MSU_CPP_SPRING_2020_PARSE_HPP
#define MSU_CPP_SPRING_2020_PARSE_HPP

namespace parse {
    using t_onBegin = void (*)(const char *str);
    using t_onEnd = void (*)();
    using t_onWord = void (*)(const std::string &);
    using t_onNumber = void (*)(int);

    void setOnBegin(t_onBegin callback);

    void setOnEnd(t_onEnd callback);

    void setOnWord(t_onWord callback);

    void setOnNumber(t_onNumber callback);

    void parse(const char *input);
}


#endif //MSU_CPP_SPRING_2020_PARSE_HPP
