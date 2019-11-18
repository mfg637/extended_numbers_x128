#include <iostream>
#include "src/int/UInt128.h"
#include "src/int/Int128.h"

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
	Int128 d(0xffffffffffffffff, 0xffffffffffffffff);
	std::cout << "d = " << d << std::endl;
	Int128 e(0, 2);
	std::cout << "e = " << e << std::endl;
	Int128 result6 = d + e;
	std::cout<< "result6 = " << result6 <<std::endl;
	Int128 result7 = d - e;
	std::cout << "result7 = " << result7 << std::endl;
	Int128 result8 = result6 * e;
	std::cout << "result8 = " << result8 << std::endl;
	Int128 result9 = result8 / e;
	std::cout << "result9 = " << result9 << std::endl;
	Int128 result10 = d * e - e;
	std::cout << "result10 = "<< result10 << std::endl;
	UInt128 f(0, 0);
	std::cout << "f = ";
	std::cin >> f;
	if (!std::cin.bad()){
		std::cout << "f = " << f << std::endl;
	}else{
		std::cout << "incorrent 128bit unsigned number";
		return 1;
	}
	Int128 g(0, 0);
	std::cout << "g = ";
	std::cin >> g;
	if (!std::cin.bad()){
		std::cout << "g = " << g << std::endl;
	}else{
		std::cout << "incorrent 128bit signed integer number";
		return 1;
	}
    return 0;
}
