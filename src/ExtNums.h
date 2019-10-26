#ifndef EXTNUMS_H
#define EXTNUMS_H
#include <iostream>

class ExtNums
{
    private:
	protected:
		long long unsigned int big;
        long long unsigned int little;
		template <typename BIG_PART_TYPE>
		struct calc_results{
			BIG_PART_TYPE big;
			long long unsigned little;
			void set(BIG_PART_TYPE _big, long long unsigned _little){
				big = _big;
				if (big != _big)
					std::cout << "INCORECT_PROGRAM!";
				little = _little;
				if (little != little)
					std::cout << "INCORECT_PROGRAM!";
			}
		};
		template <typename BIG_PART_TYPE>
		calc_results<BIG_PART_TYPE> add(BIG_PART_TYPE big, long long unsigned little){
			calc_results<BIG_PART_TYPE> results;
			#ifdef __x86_64__
			//char overflow = 2;
			/*asm volatile(
				"addq %%rbx, %%rax\n\t"
				"movb $0, %%dl\n\t"
				"jnc 1f\n\t"
				"movb $1, %%dl\n\t"
				"1:"
				: "=a" (little), "=d" (overflow)
				: "b" (this->little), "a" (b.little) 
			);*/
			BIG_PART_TYPE bigr;
			long long unsigned littler;
			asm(
				"addq %%rbx, %%rax\n\t"
				"adcq %%rcx, %%rdx\n\t"
				: "=a" (littler), "=d" (bigr)
				: "b" (this->little), "a" (little), "c" (this->big), "d" (big)
			);
			/*big = this->big + b.big;
			big += overflow;*/
			results.set(bigr, littler);
			#endif
			return results;
			
		}
		template <typename BIG_PART_TYPE>
		calc_results<BIG_PART_TYPE> sub(BIG_PART_TYPE big, long long unsigned little){
			calc_results<BIG_PART_TYPE> results;
			#ifdef __x86_64__
			BIG_PART_TYPE bigr;
			long long unsigned littler;
			asm(
				"subq %%rbx, %%rax\n\t"
				"sbbq %%rcx, %%rdx\n\t"
				: "=a" (littler), "=d" (bigr)
				: "b" (little), "a" (this->little), "c" (big), "d" (this->big)
			);
			results.set(bigr, littler);
			#endif
			return results;
		}
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
