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
std::ostream& operator<<(std::ostream& out, UInt128& number){
	const unsigned digits_count = 39;
	char digits[digits_count];
	bool bits[128];
	for (unsigned i = 0; i < 39; i++)
		digits[i] = 0;
	long long unsigned mask = 1;
	for (unsigned i = 0; i < 64; i++){
		bits[i] = bool(number.little & mask);
		mask <<= 1;
	}
	mask = 1;
	for (unsigned i = 64; i < 128; i++){
		bits[i] = bool(number.big & mask);
		mask <<= 1;
	}
	unsigned bits_read = 128;
	for (;bits_read>1; bits_read--)
		if ((bits[bits_read-1]!=0) || (bits_read==1))
			break;
	for (int j = bits_read-1; j>=0; j--){
		int overflow = bits[j];
		for (unsigned i = 0; i < digits_count; i++){
			digits[i] = digits[i] * 2 + overflow;
			overflow = 0;
			if (digits[i]>9){
				//overflow = dig
				char remainder=127, quotient=127; 
				asm volatile(
					"movb $10, %%bl\n\t"
					"movb $0, %%ah\n\t"
					"divb %%bl\n\t"
					"mov %%ah, %%dl\n\t"
					: "=d" (remainder), "=al" (quotient)
					: "a" (digits[i])
					: "bl", "cc"
				);
				overflow = quotient;
				digits[i] = remainder;
			}
		}
	}
	unsigned digits_read = digits_count;
	for (;digits_read>1; digits_read--)
		if ((digits[digits_read-1]!=0) || (digits_read==1))
			break;
	for (int i = digits_read - 1; i>=0; i--)
		out << (char)(digits[i]+(char)(48));
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
