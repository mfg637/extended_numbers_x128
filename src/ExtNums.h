#ifndef EXTNUMS_H
#define EXTNUMS_H
#include <iostream>

class ExtNums
{
    private:
    protected:
    public:
        ExtNums() {}
        virtual ~ExtNums() = default;
        virtual ExtNums& operator+(ExtNums&)=0;
        virtual ExtNums& operator-(ExtNums&)=0;
        virtual ExtNums& operator*(ExtNums&)=0;
        virtual ExtNums& operator/(ExtNums&)=0;
        virtual std::ostream& operator<<(std::ostream&)=0;

};

#endif // EXTNUMS_H
