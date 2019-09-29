#ifndef UINT128_H
#define UINT128_H

#include "../ExtNums.h"


class UInt128 : public ExtNums
{
    private:
        long long unsigned int big;
        long long unsigned int little;

    protected:

    public:
        UInt128(long long unsigned big_part, long long unsigned little_part);
        ~UInt128();
        UInt128& operator+(UInt128&);
        UInt128& operator-(UInt128&);
        UInt128& operator*(UInt128&);
        UInt128& operator/(UInt128&);
		ExtNums& operator+(ExtNums&);
        ExtNums& operator-(ExtNums&);
        ExtNums& operator*(ExtNums&);
        ExtNums& operator/(ExtNums&);
        std::ostream& operator<<(std::ostream&);
};

#endif // UINT128_H
