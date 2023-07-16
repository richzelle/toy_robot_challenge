#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <iostream>
#include <string>
#include <algorithm>

const std::string WHITESPACE = " \n\r\t\f\v";

class string_util
{
public:
    static std::string ltrim(const std::string &input)
    {
        std::string out = "";
        size_t start = input.find_first_not_of(WHITESPACE);

        if (start != std::string::npos)
        {
            out = input.substr(start);
        }

        return out;
    }

    static std::string rtrim(const std::string &input)
    {
        std::string out = "";
        size_t end = input.find_last_not_of(WHITESPACE);

        if (end != std::string::npos)
        {
            out = input.substr(0, end + 1);
        }

        return out;
    }

    static std::string trim(const std::string &input)
    {
        std::string out = ltrim(input);
        out = rtrim(out);

        return out;
    }
};

#endif /* STRING_UTIL_H */