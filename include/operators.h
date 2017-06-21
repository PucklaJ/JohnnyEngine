#ifndef OPERATORS_H_INCLUDED
#define OPERATORS_H_INCLUDED
#include <string>

extern const std::string operator+(const std::string&,int);
extern const std::string operator+(int,const std::string&);
extern const std::string operator+(const std::string&,const double&);
extern const std::string operator+(const double&,const std::string&);
extern const std::string operator+(const std::string&,const float&);
extern const std::string operator+(const float&,const std::string&);


#endif // OPERATORS_H_INCLUDED
