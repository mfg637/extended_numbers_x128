#include "UInt128.h"

UInt128::UInt128(long long unsigned big_part, long long unsigned little_part)
{
    this->big = big_part;
	this->little = little_part;
}

UInt128::~UInt128()
{
    //dtor
}

UInt128& UInt128::operator+(UInt128& b){
	calc_results<long long unsigned> results = add(b.big, b.little);
    return *(new UInt128(results.big, results.little));
}

UInt128& UInt128::operator-(UInt128& b){
	calc_results<long long unsigned> results = sub(b.big, b.little);
    return *(new UInt128(results.big, results.little));
}

UInt128& UInt128::operator*(UInt128& b){
	calc_results<long long unsigned> results = mul(b.big, b.little);
    return *(new UInt128(results.big, results.little));
}
UInt128& UInt128::operator/(UInt128& b){
    return *this;
}
std::ostream& UInt128::operator<<(std::ostream& out){
    return out;
}

ExtNums& UInt128::operator+(ExtNums& b){
	return (ExtNums&)(this->operator+((UInt128&)(b)));
}

ExtNums& UInt128::operator-(ExtNums& b){
	return (ExtNums&)(this->operator-((UInt128&)(b)));
}

ExtNums& UInt128::operator*(ExtNums& b){
	return (ExtNums&)(this->operator*((UInt128&)(b)));
}

ExtNums& UInt128::operator/(ExtNums& b){
	return (ExtNums&)(this->operator/((UInt128&)(b)));
}
