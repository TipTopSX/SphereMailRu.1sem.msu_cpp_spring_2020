#ifndef MSU_CPP_SPRING_2020_SERIALIZER_HPP
#define MSU_CPP_SPRING_2020_SERIALIZER_HPP
#pragma once

#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream &out_;
public:
    explicit Serializer(std::ostream &out) : out_(out)
    {}

    template<class T>
    Error save(T &object)
    {
        return object.serialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

private:
    // process использует variadic templates
    template<class T>
    Error process(T &&val)
    {
        if (print(val) != Error::NoError)
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    template<class T, class... Args>
    Error process(T &&val, Args &&... args)
    {
        if (print(val) != Error::NoError)
            return Error::CorruptedArchive;
        return process(std::forward<Args>(args)...);
    }

    template<class T>
    Error print(T &val)
    {
        out_ << std::boolalpha << val << Separator;
        out_ << std::noboolalpha;
        return Error::NoError;
    }
};

class Deserializer
{
    static constexpr char Separator = ' ';
    std::istream &in_;
public:
    explicit Deserializer(std::istream &in) : in_(in)
    {}

    template<class T>
    Error load(T &object)
    {
        return object.deserialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

private:
    template<class T>
    Error process(T &&val)
    {
        if (load(val) != Error::NoError)
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    template<class T, class... Args>
    Error process(T &&val, Args &&... args)
    {
        if (load(val) != Error::NoError)
            return Error::CorruptedArchive;
        return process(std::forward<Args>(args)...);
    }

    Error load(uint64_t &val)
    {
        std::string buf;
        in_ >> buf;
        if (!std::all_of(buf.begin(), buf.end(), ::isdigit))
            return Error::CorruptedArchive;
        val = std::stoi(buf);
        return Error::NoError;
    }

    Error load(bool &val)
    {
        std::string buf;
        in_ >> buf;
        if (buf != "true" && buf != "false")
            return Error::CorruptedArchive;
        val = (buf == "true");
        return Error::NoError;
    }
};

#endif //MSU_CPP_SPRING_2020_SERIALIZER_HPP
