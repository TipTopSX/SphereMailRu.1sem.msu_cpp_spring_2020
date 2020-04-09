#ifndef MSU_CPP_SPRING_2020_FORMAT_HPP
#define MSU_CPP_SPRING_2020_FORMAT_HPP

#include <string>
#include <sstream>
#include <vector>

template<class T>
std::string to_string(T &&x)
{
    std::stringstream stream;
    stream << x;
    return stream.str();
}

template<class... argsT>
std::string format(const std::string &fstr, argsT &&... args)
{
    std::stringstream result;
    std::vector<std::string> param = {to_string(std::forward<argsT>(args))...};
    for (std::string::const_iterator it = fstr.begin(); it < fstr.end(); ++it) {
        switch (*it) {
        case '}':
            throw std::runtime_error("unexpected closing brace");
        case '{': {
            if (++it == fstr.end() || *it == '}')
                throw std::runtime_error("empty braces or end of string");
            size_t param_num = 0;
            for (; *it != '}'; ++it) {
                if (it == fstr.end() || !isdigit(*it))
                    throw std::runtime_error("not a number");
                param_num = 10 * param_num + *it - '0';
            }
            if (param_num >= param.size())
                throw std::runtime_error("index out of range");
            result << param[param_num];
        }
            break;
        default:
            if (it < fstr.end())
                result << *it;
        }
    }
    return result.str();
}

#endif //MSU_CPP_SPRING_2020_FORMAT_HPP
