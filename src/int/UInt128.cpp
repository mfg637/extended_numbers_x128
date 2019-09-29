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
	long long unsigned big, little;
    char overflow = 2;
    asm volatile(
		"addq %%rbx, %%rax\n\t"
		"movb $0, %%dl\n\t"
		"jnc 1f\n\t"
		"movb $1, %%dl\n\t"
		"1:"
		: "=a" (little), "=d" (overflow)
		: "b" (this->little), "a" (b.little) 
	);
	big = this->big + b.big;
	big += overflow;
    return *(new UInt128(big, little));
}

UInt128& UInt128::operator-(UInt128& b){
    return *this;
}

UInt128& UInt128::operator*(UInt128& b){
    return *this;
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
