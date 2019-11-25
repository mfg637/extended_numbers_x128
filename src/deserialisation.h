#pragma once

#include <iostream>
#include <cstring>
#include <typeinfo>
#include "ExtNums.h"
#include "int/UInt128.h"
#include "int/Int128.h"

class Fixed128: ExtNumsBase<long long int>{};

void write_bin_int64(char* bytes, std::ostream& out){
	for (unsigned i = 0; i < 8; i++){
		out<<bytes[i];
	}
}

void read_bin_int64(char* bytes, std::istream& in){
	for (unsigned i = 0; i < 8; i++){
		bytes[i] = in.get();
	}
}

template <typename BIG_PART_TYPE>
void serialize(ExtNumsBase<BIG_PART_TYPE>** array, long unsigned int array_size, std::ostream& out){
	out<<"BIN";
	char* array_size_char_ptr = (char*)(&array_size);
	for (unsigned i = 0; i < 4; i++){
		out<<array_size_char_ptr[i];
	}
	for (unsigned i=0; i<array_size; i++){
		ExtNumsBase<BIG_PART_TYPE>* current_elem = array[i];
		current_elem->serialize(out);
	}
}

template <typename BIG_PART_TYPE>
struct ExtNumsArray{
	ExtNumsBase<BIG_PART_TYPE>** array;
	long unsigned int array_size;
	ExtNumsArray(ExtNumsBase<BIG_PART_TYPE>** _array, long unsigned int _array_size){
		array = _array;
		array_size = _array_size;
	}
};

template <typename BIG_PART_TYPE>
ExtNumsArray<BIG_PART_TYPE> deserialize(std::istream& in);
ExtNumsArray<long long unsigned> deserialize(std::istream& in){
	char header[4];
	in.read(header, 3);
	header[3] = 0;
	if(std::strcmp(header, "BIN")!=0)
		return ExtNumsArray<long long unsigned>(nullptr, 0);
	long unsigned int array_size=0;
	in.read((char*)(&array_size), 4);
	ExtNumsBase<long long unsigned>** array = new ExtNumsBase<long long unsigned>*[array_size];
	for (unsigned i=0; i<array_size; i++){
		long long unsigned big_part;
		long long unsigned little_part;
		char number_type = in.get();
		char* number_part_ptr = (char*)(&big_part);
		read_bin_int64(number_part_ptr, in);
		number_part_ptr = (char*)(&little_part);
		read_bin_int64(number_part_ptr, in);
		if (number_type == 1){
			UInt128* t = new UInt128(big_part, little_part);
			array[i] = t;
		}else{
			std::cout << " wrong type identifier ";
		}
	}
	return ExtNumsArray<long long unsigned>(array, array_size);
}
/*ExtNumsArray<long long signed int> deserialize(std::istream& in){
	char header[4];
	in.read(header, 3);
	header[3] = 0;
	if(std::strcmp(header, "BIN")!=0)
		return ExtNumsArray<long long int>(nullptr, 0);
	long unsigned int array_size=0;
	//char* array_size_char_ptr = (char*)(&array_size);
	//for (unsigned i = 0; i < 4; i++){
		//out<<array_size_char_ptr[i];
		//char c = in.get();
		//*array_size_char_ptr = c;
		//array_size_char_ptr++;
		
	//}
	//in.read(array_size_char_ptr, 8);
	in.read((char*)(&array_size), 4);
	ExtNums<long long int>** array = new ExtNums<long long int>*[array_size];
	for (unsigned i=0; i<array_size; i++){
		long long int big_part;
		long long unsigned little_part;
		char number_type = in.get();
		char* number_part_ptr = (char*)(&big_part);
		read_bin_int64(number_part_ptr, in);
		number_part_ptr = (char*)(&little_part);
		read_bin_int64(number_part_ptr, in);
		if (number_type == 2){
			array[i] = new Int128(big_part, little_part);
		}
	}
	return ExtNumsArray<long long int>(array, array_size);
}*/
