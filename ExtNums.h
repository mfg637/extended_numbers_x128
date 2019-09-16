#ifndef EXTNUMS_H
#define EXTNUMS_H
#include <iostream>

class ExtNums
{
    private:
    protected:
    public:
        ExtNums() {}
        //virtual ~ExtNums() {}
        virtual ExtNums operator+(ExtNums&)=0;
        virtual ExtNums operators-(ExtNums&)=0;
        virtual ExtNums oparator*(ExtNums&)=0;
        virtual ExtNums operator/(ExtNums&)=0;
        virtual std::ostream& operator<<(std::ostream&);

};

#endif // EXTNUMS_H
