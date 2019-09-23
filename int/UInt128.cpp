#include "UInt128.h"

UInt128::UInt128(long long unsigned big_part, long long unsigned little_part)
{
    //ctor
}

UInt128::~UInt128()
{
    //dtor
}

UInt128* UInt128::operator+(ExtNums*){
    bool overflow = false;
    //
    return this;
}

UInt128* UInt128::operator-(ExtNums*){
    return this;
}

UInt128* UInt128::operator*(ExtNums*){
    return this;
}
UInt128* UInt128::operator/(ExtNums*){
    return this;
}
std::ostream& UInt128::operator<<(std::ostream& out){
    return out;
}
