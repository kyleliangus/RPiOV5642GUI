#include "parameter.h"

using namespace std;

Parameter::Parameter( string r , int v )
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
string Parameter::toString()
{
    stringstream a;
    //a << this->getRegistry() << ", 0x" << std::setfill ('0')
      //       << std::setw(sizeof(int)*2) << std::hex << this->getValue();
    a << this->getRegistry() << ", 0x" << std::setfill ('0') << std::setw(2) << std::hex << this->getValue();
    return a.str();
}

