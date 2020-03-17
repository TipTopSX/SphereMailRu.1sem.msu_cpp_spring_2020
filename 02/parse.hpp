#pragma once
#ifndef MSU_CPP_SPRING_2020_PARSE_HPP
#define MSU_CPP_SPRING_2020_PARSE_HPP

namespace parse_callbacks {

    void setOnBegin(void (*callback)(const char *));

    void setOnEnd(void (*callback)());

    void setOnWord(void (*callback)(const std::string &));

    void setOnNumber(void (*callback)(int));

}

void parse(const char *input);

#endif //MSU_CPP_SPRING_2020_PARSE_HPP
