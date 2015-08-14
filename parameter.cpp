#include "parameter.h"


Parameter::Parameter( std::string r , int v )
{
    registry = r;
    value = v;

}

Parameter::~Parameter()
{

}

// operator /*  updated to only include registry  */
Parameter::operator== ( const Parameter &b )
{
    //if( this->getRegistry().compare( b.getRegistry() ) == 0
      //      && this->getValue() == b.getValue() )
    if( this->getRegistry().compare( b.getRegistry() ) == 0 )
    {
        return true;
    }
    return false;
}

/*
Parameter::operator= ( const Parameter &b )
{
    registry = b.getRegistry();
    value = b.getValue();
} */

// functions
std::string Parameter::toString()
{
    std::stringstream a;
    //a << this->getRegistry() << ", 0x" << std::setfill ('0')
      //       << std::setw(sizeof(int)*2) << std::hex << this->getValue();
    a << this->getRegistry() << ", 0x" << std::setfill ('0') << std::setw(2) << std::hex << this->getValue();
    return a.str();
}

std::string Parameter::toRawFormat()
{
    std::stringstream b;
    b << (this->getRegistry()).substr(2, 4) << std::setfill ('0') << std::setw(2) << std::hex << this->getValue();
    return b.str();
}

