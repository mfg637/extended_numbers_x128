#ifndef EXTNUMS_H
#define EXTNUMS_H
#include <iostream>

class ExtNums
{
    private:
    protected:
    public:
        ExtNums() {}
        virtual ~ExtNums();
        virtual ExtNums* operator+(ExtNums*)=0;
        virtual ExtNums* operator-(ExtNums*)=0;
        virtual ExtNums* operator*(ExtNums*)=0;
        virtual ExtNums* operator/(ExtNums*)=0;
        virtual std::ostream& operator<<(std::ostream&)=0;

};

ExtNums::~ExtNums(){}

#endif // EXTNUMS_H
