#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>
#include <math.h>
#include <iomanip>
#include <sstream>

class Parameter
{
public:
    Parameter(std::string r, int v);
    ~Parameter();
    operator==(const Parameter &b);
    //operator=(const Parameter &b);

    // getters and setters
    std::string getRegistry() const
    {
        return registry;
    }
    int getValue() const
    {
        return value;
    }
    void setValue( int x )
    {
        value = x;
    }
    /*
    bool isDefaultValue()
    {
        return defaultValue;
    } */

    // print as hex
    std::string toString();
    std::string toRawFormat();

private:
    std::string registry;
    int value;
    //bool defaultValue;
};

#endif // PARAMETER_H
