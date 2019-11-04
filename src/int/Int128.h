#ifndef INT128_H
#define INT128_H

#include "../ExtNums.h"

class Int128 : public ExtNums<long long int>
{
	public:
		Int128(long long int big_part, long long unsigned little_part);
        ~Int128();
        Int128& operator+(Int128&);
        Int128& operator-(Int128&);
        Int128& operator*(Int128&);
        Int128& operator/(Int128&);
		ExtNums<long long int>& operator+(ExtNums&);
        ExtNums<long long int>& operator-(ExtNums&);
        ExtNums<long long int>& operator*(ExtNums&);
        ExtNums<long long int>& operator/(ExtNums&);
        friend std::ostream& operator<<(std::ostream&, Int128&);
	protected:
};

#endif
