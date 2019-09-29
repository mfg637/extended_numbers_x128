#include <iostream>
#include "src/int/UInt128.h"

int main(int argc, char **argv)
{
    std::cout << "Hello world!" << std::endl;
	//overflow test
	UInt128 a(0, 0xffffffffffffffff);
	UInt128 b(0, 2);
	UInt128 result = a+b;
    return 0;
}
