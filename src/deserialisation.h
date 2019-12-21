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

void serialize(IExtNums** array, long unsigned int array_size, std::ostream& out){
	out<<"BIN";
	out.write((char*)(&array_size), 4);
	for (unsigned i=0; i<array_size; i++){
		IExtNums* current_elem = array[i];
		//current_elem->text_out(std::cout);
		//std::cout << std::endl;
		current_elem->serialize(out);
	}
}

struct ExtNumsArray{
	IExtNums** array;
	long unsigned int array_size;
	ExtNumsArray(IExtNums** _array, long unsigned int _array_size){
		array = _array;
		array_size = _array_size;
	}
};

ExtNumsArray deserialize(std::istream& in){
	char header[4];
	in.read(header, 3);
	header[3] = 0;
	if(std::strcmp(header, "BIN")!=0)
		return ExtNumsArray(nullptr, 0);
	long unsigned int array_size=0;
	in.read((char*)(&array_size), 4);
	IExtNums** array = new IExtNums*[array_size];
	for (unsigned i=0; i<array_size; i++){
		char number_type = in.get();
		if (number_type == 1){
			long long unsigned big_part;
			long long unsigned little_part;
			in.read((char*)(&big_part), 8);
			in.read((char*)(&little_part), 8);
			array[i] = new UInt128(big_part, little_part);
		}else if (number_type == 2){
			long long int big_part;
			long long unsigned little_part;
			in.read((char*)(&big_part), sizeof(big_part));
			in.read((char*)(&little_part), sizeof(little_part));
			array[i] = new Int128(big_part, little_part);
		}else{
			std::cout << " wrong type identifier ";
		}
	}
	return ExtNumsArray(array, array_size);
}
