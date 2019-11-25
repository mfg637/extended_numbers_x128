#ifndef INT128_H
#define INT128_H

#include "../ExtNums.h"

class Int128 : public ExtNumsBase<long long int>, IExtNums
{
	public:
		Int128(long long int big_part, long long unsigned little_part);
		Int128(const char*);
		Int128(ExtNumsBase<long long int>&);
        ~Int128();
        Int128& operator+(Int128&);
        Int128& operator-(Int128&);
        Int128& operator*(Int128&);
        Int128& operator/(Int128&);
		IExtNums& operator+(IExtNums&);
        IExtNums& operator-(IExtNums&);
        IExtNums& operator*(IExtNums&);
        IExtNums& operator/(IExtNums&);
        void serialize(std::ostream&);
        friend std::ostream& operator<<(std::ostream&, Int128&);
        friend std::istream& operator>>(std::istream&, Int128&);
	protected:
};

#endif
