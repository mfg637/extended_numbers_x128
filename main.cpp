#include <iostream>
#include "src/int/UInt128.h"

int main(int argc, char **argv)
{
    std::cout << "Hello world!" << std::endl;
	//overflow test
	UInt128 a(0, 0xffffffffffffffff);
	std::cout << "a = " << a << std::endl;
	UInt128 b(0, 2);
	std::cout << "b = " << b << std::endl;
	UInt128 result1 = a+b;
	std::cout << "result1 = " << result1 << std::endl;
	UInt128 result2 = result1 - b;
	std::cout << "result2 = " << result2 << std::endl;
	UInt128 result3 = a * b;
	std::cout << "result3 = " << result3 << std::endl;
	UInt128 c(0, 10);
	std::cout << "c = " << c << std::endl;
	UInt128 result4 = a * c;
	std::cout << "result4 = " << result4 << std::endl;
	UInt128 result5 = result4 / c;
	std::cout << "result5 = " << result5 << std::endl;
    return 0;
}
