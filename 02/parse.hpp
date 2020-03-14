#pragma once
#ifndef MSU_CPP_SPRING_2020_PARSE_HPP
#define MSU_CPP_SPRING_2020_PARSE_HPP


void setParseBegin(void (*callback)(const char *));

void setParseEnd(void (*callback)());

void setParseWord(void (*callback)(char *));

void setParseNumber(void (*callback)(char *));

void parse(char *input);

#endif //MSU_CPP_SPRING_2020_PARSE_HPP
