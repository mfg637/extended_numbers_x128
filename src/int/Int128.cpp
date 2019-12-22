#include "Int128.h"
#include <sstream>

Int128::Int128(long long int big_part, long long unsigned little_part)
{
    this->big = big_part;
	this->little = little_part;
}

Int128::Int128(const char* string){
	std::stringstream s;
	s << string;
	s >> *this;
}

Int128::Int128(ExtNumsBase<long long int>& n){
	if (typeid(n)==typeid(Int128)){
		this->big = n.getBig();
		this->little = n.getLittle();
	}
}

Int128::~Int128()
{
    //dtor
}

Int128& Int128::operator+(Int128& b){
	calc_results<long long int> results = add(b.big, b.little);
    return *(new Int128(results.big, results.little));
}

Int128& Int128::operator-(Int128& b){
	calc_results<long long int> results = sub(b.big, b.little);
    return *(new Int128(results.big, results.little));
}

Int128& Int128::operator*(Int128& b){
	calc_results<long long int> results = mul(b.big, b.little);
    return *(new Int128(results.big, results.little));
}

Int128& Int128::operator/(Int128& b){
	long long unsigned normal_little=this->little;
	long long int normal_big=this->big, result_count_big = 0;
	long long unsigned result_count_little=0;
	#ifdef __x86_64__
		if (b.big == 0){
			asm(
				"idivq %%rbx\n\t"
				: "=a" (result_count_little)
				: "a" (normal_little), "d" (normal_big), "b" (b.little)
			);
			if (result_count_little&0x8000000000000000LL)
				result_count_big = -1;
		}else{
			while (((normal_big == b.big) && (normal_little >= b.little)) || (normal_big > b.big)){
				asm(
					"subq %%rbx, %%rax\n\t"
					"sbbq %%rcx, %%rdx\n\t"
					: "=a" (normal_little), "=d" (normal_big)
					: "b" (b.little), "a" (normal_little), "c" (b.big), "d" (normal_big)
				);
				asm(
					"addq %%rbx, %%rax\n\t"
					"adcq %%rcx, %%rdx\n\t"
					: "=a" (result_count_little), "=d" (result_count_big)
					: "b" (1), "a" (result_count_little), "c" (0), "d" (result_count_big)
				);
			}
		}
	#endif
    return *(new Int128(result_count_big, result_count_little));
}

std::ostream& Int128::text_out(std::ostream& out){
	return (out << *this);
}

std::ostream& operator<<(std::ostream& out, Int128& number){
	const unsigned digits_count = 39;
	calc_results<long long int> results1 = number.sub(0, 1);
	long long int number_big = number.getBig();
	bool sign_bit = (bool)(number_big & (long long int)(1)<<63);
	long long unsigned number_little;
	if (sign_bit){
	Int128 max(0xffffffffffffffff, 0xffffffffffffffff);
	Int128 t(results1.big, results1.little);
	Int128 result2 = max - t;
	number_big = result2.getBig();
	number_little = result2.getLittle();
	}else{
		number_little = number.getLittle();
	}
	char digits[digits_count];
	bool bits[128];

	for (unsigned i = 0; i < 39; i++)
		digits[i] = 0;
	long long int mask = 1;
	for (unsigned i = 0; i < 64; i++){
		bits[i] = bool(number_little & mask);
		mask <<= 1;
	}
	mask = 1;
	for (unsigned i = 64; i < 128; i++){
		bits[i] = bool(number_big & mask);
		mask <<= 1;
	}
	unsigned bits_read = 127;
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
	if (sign_bit)
		out << '-';
	for (int i = digits_read - 1; i>=0; i--)
		out << (char)(digits[i]+(char)(48));
    return out;
}

IExtNums& Int128::operator+(IExtNums& b){
	Int128 c(b.getSignedBig(), b.getLittle());
	return ((*this) + c);
}

IExtNums& Int128::operator-(IExtNums& b){
	return (IExtNums&)(this->operator-((Int128&)(b)));
}

IExtNums& Int128::operator*(IExtNums& b){
	return (IExtNums&)(this->operator*((Int128&)(b)));
}

IExtNums& Int128::operator/(IExtNums& b){
	return (IExtNums&)(this->operator/((Int128&)(b)));
}
std::istream& operator>>(std::istream& in, Int128& number){
	const unsigned digits_count = 39;
	unsigned read_digits=0;
	Int128 result(0, 0);
	char c = in.get();
	bool negative=false;
	if (c == '-'){
		negative = true;
		c = in.get();
	}
	if ((c<'0') || (c>'9')){
		in.setstate(std::ios_base::badbit);
		return in;
	}
	Int128 _10(0, 10);
	while ((c>='0') && (c<='9') && (read_digits<digits_count)){
		Int128 digit(0, c-(char)(48));
		result = result*_10+digit;
		c = in.get();
		read_digits++;
	}
	if (read_digits==digits_count){
		c = in.get();
		if ((c>='0') && (c<='9')){
			in.setstate(std::ios_base::badbit);
			return in;
		}
	}
	number.big = result.getBig();
	number.little = result.getLittle();
	if (negative){
		number.big = ~number.big;
		number.little = ~number.little;
		asm(
			"addq %%rbx, %%rax\n\t"
			"adcq %%rcx, %%rdx\n\t"
			: "=a" (number.little), "=d" (number.big)
			: "b" (number.little), "a" (1), "c" (number.big), "d" (0)
		);
	}
	return in;
}

void Int128::serialize(std::ostream& out){
	out << (char)(2);
	out.write((char*)(&big), sizeof(big));
	out.write((char*)(&little), sizeof(little));
}
