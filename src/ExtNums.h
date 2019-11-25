#ifndef EXTNUMS_H
#define EXTNUMS_H
#include <iostream>
#include <cmath>
#include <typeinfo>

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

class IExtNums{
	public:
	IExtNums() {}
	virtual ~IExtNums() = default;
    virtual IExtNums& operator+(IExtNums&)=0;
    virtual IExtNums& operator-(IExtNums&)=0;
    virtual IExtNums& operator*(IExtNums&)=0;
    virtual IExtNums& operator/(IExtNums&)=0;
};

template <typename BIG_PART_TYPE>
class ExtNumsBase
{
    private:
	protected:
		BIG_PART_TYPE big;
        long long unsigned int little;
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
		calc_results<BIG_PART_TYPE> mul(BIG_PART_TYPE big, long long unsigned little, bool offset = false){
			calc_results<BIG_PART_TYPE> results;
			BIG_PART_TYPE normal_big=0, overflow_big=0;
			long long unsigned normal_little=0, overflow_little=0;
			#ifdef __x86_64__
			char overflow = 2;
			long long unsigned n_iterations_big;
			if (typeid(big)!=typeid(long long unsigned))
				n_iterations_big = (long long unsigned)((long long int)(std::abs((long long int)(big))));
			else
				n_iterations_big = big;
			for (long long unsigned i = 1; i <= n_iterations_big; i++){
				for (long long unsigned j = 0; j<=0xffffffffffffffff; j++){
					asm volatile(
						"addq %%rbx, %%rax\n\t"
						"movb $0, %%dl\n\t"
						"jnc 1f\n\t"
						"movb $1, %%dl\n\t"
						"1:"
						: "=a" (normal_little), "=d" (overflow)
						: "b" (this->little), "a" (normal_little) 
					);
					normal_big += overflow;
					asm volatile(
						"addq %%rbx, %%rax\n\t"
						"movb $0, %%dl\n\t"
						"jnc 1f\n\t"
						"movb $1, %%dl\n\t"
						"1:"
						: "=a" (normal_big), "=d" (overflow)
						: "b" (normal_big), "a" (this->big) 
					);
					asm volatile(
						"addq %%rbx, %%rax\n\t"
						"movb $0, %%dl\n\t"
						"jnc 1f\n\t"
						"movb $1, %%dl\n\t"
						"1:"
						: "=a" (overflow_little), "=d" (overflow)
						: "b" (overflow_little), "a" ((long long unsigned)(overflow)) 
					);
					overflow_big += overflow;
				}
			}
			for (long long unsigned i = 1; i <= little; i++){
					asm volatile(
						"addq %%rbx, %%rax\n\t"
						"movb $0, %%dl\n\t"
						"jnc 1f\n\t"
						"movb $1, %%dl\n\t"
						"1:"
						: "=a" (normal_little), "=d" (overflow)
						: "b" (this->little), "a" (normal_little) 
					);
					normal_big += overflow;
					asm volatile(
						"addq %%rbx, %%rax\n\t"
						"movb $0, %%dl\n\t"
						"jnc 1f\n\t"
						"movb $1, %%dl\n\t"
						"1:"
						: "=a" (normal_big), "=d" (overflow)
						: "b" (normal_big), "a" (this->big) 
					);
					asm volatile(
						"addq %%rbx, %%rax\n\t"
						"movb $0, %%dl\n\t"
						"jnc 1f\n\t"
						"movb $1, %%dl\n\t"
						"1:"
						: "=a" (overflow_little), "=d" (overflow)
						: "b" (overflow_little), "a" ((long long unsigned)(overflow)) 
					);
					overflow_big += overflow;
			}
			#endif
			if (offset){
				results.set(overflow_little, normal_big);
			}else{
				results.set(normal_big, normal_little);
			}
			return results;
		}
    public:
    	virtual void serialize(std::ostream&)=0;
        BIG_PART_TYPE getBig(){return big;}
        long long unsigned getLittle(){return little;}
        //virtual std::ostream& operator<<(std::ostream&)=0;

};

#endif // EXTNUMS_H
