/*
 * RandomTools.h
 *
 *  Created on: 2013年11月25日
 *      Author: houzhi
 */

#ifndef RANDOMTOOLS_H_
#define RANDOMTOOLS_H_

#include<time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class SingleTraveralRandom {

public:
	SingleTraveralRandom(int select_nums);

	int SingleTraversal();

	void Init();

private:
	int Random(int max);


	size_t cur_index;
	
	//选择多少
	size_t select_nums;



	

};

SingleTraveralRandom::SingleTraveralRandom(int select_nums){
	this-> select_nums = select_nums;
	cur_index = 0;
}

inline int SingleTraveralRandom::Random(int max){
	srand((unsigned )time(NULL));

	int res = rand() % max;

	return res;
}

/**
 * 初始化
 */
inline void SingleTraveralRandom::Init(){
	cur_index = 0;
}


int SingleTraveralRandom::SingleTraversal(){
	cur_index ++;
	if(cur_index <= select_nums ){
		return cur_index-1;
	}else{
		int random = Random(cur_index);
		if(random <=select_nums){
			return random-1;
		}else{
			return -1;
		}
	}
}

#endif /* RANDOMTOOLS_H_ */
