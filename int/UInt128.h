#ifndef UINT128_H
#define UINT128_H

#include <ExtNums.h>


class UInt128 : public ExtNums
{
    public:
        UInt128(lond long unsigned big_part, long long unsigned little_part);
        virtual ~UInt128();

        //long long unsigned int Getbig() { return big; }
        //void Setbig(long long unsigned int val) { big = val; }
        //long long unsigned int Getlittle() { return little; }
        //void Setlittle(long long unsigned int val) { little = val; }

    protected:

    private:
        long long unsigned int big;
        long long unsigned int little;
};

#endif // UINT128_H
