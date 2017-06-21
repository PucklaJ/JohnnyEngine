#include "operators.h"
#include <sstream>

const std::string operator+(const std::string& str,int i)
{
    std::string str1 = "";
    std::stringstream stream;

    stream << i;
    stream >> str1;

    str1 = str + str1;

    return str1;
}

const std::string operator+(int i,const std::string& str)
{
    std::string str1 = "";
    std::stringstream stream;

    stream << i;
    stream >> str1;

    str1 = str1 + str;

    return str1;
}

const std::string operator+(const std::string& str,const double& i)
{
    std::string str1 = "";
    std::stringstream stream;

    stream << i;
    stream >> str1;

    str1 = str + str1;

    return str1;
}
const std::string operator+(const double& i,const std::string& str)
{
    std::string str1 = "";
    std::stringstream stream;

    stream << i;
    stream >> str1;

    str1 = str1 + str;

    return str1;
}
const std::string operator+(const std::string& str,const float& i)
{
    std::string str1 = "";
    std::stringstream stream;

    stream << i;
    stream >> str1;

    str1 = str + str1;

    return str1;
}
const std::string operator+(const float& i,const std::string& str)
{
    std::string str1 = "";
    std::stringstream stream;

    stream << i;
    stream >> str1;

    str1 = str1 + str;

    return str1;
}
