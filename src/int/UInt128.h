#ifndef UINT128_H
#define UINT128_H

#include "../ExtNums.h"

class UInt128 : public ExtNums<long long unsigned>
{
    private:

    protected:

    public:
        UInt128(long long unsigned big_part, long long unsigned little_part);
        UInt128(const char*);
		UInt128(ExtNums<long long unsigned int>&);
        ~UInt128();
        UInt128& operator+(UInt128&);
        UInt128& operator-(UInt128&);
        UInt128& operator*(UInt128&);
        UInt128& operator/(UInt128&);
		ExtNums<long long unsigned>& operator+(ExtNums&);
        ExtNums<long long unsigned>& operator-(ExtNums&);
        ExtNums<long long unsigned>& operator*(ExtNums&);
        ExtNums<long long unsigned>& operator/(ExtNums&);
        friend std::ostream& operator<<(std::ostream&, UInt128&);
        friend std::istream& operator>>(std::istream&, UInt128&);
};

#endif // UINT128_H
