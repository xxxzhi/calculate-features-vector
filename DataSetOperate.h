/*
 * DataSetOperate.h
 *
 *  Created on: 2013年11月18日
 *      Author: houzhi
 */

#ifndef READDATA_H_
#define READDATA_H_

#include "DataRecord.h"
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>



using std::queue;
using std::ifstream;
using std::cout;
using std::ios;
using std::endl;
using std::istringstream;

class DataSetOperate {
private:
	unsigned int slideWindowSize = 10;
		//文件读取 滑动窗口
	queue<DataRecord> slideWindow;

	//文件
	ifstream infile;

	double calculateSMV(DataRecord& record);
	double calculateSMA();

	DataRecord readRecordFromFile();
public:
	DataRecord readNext();

	/*
	 * N 表示 滑动窗口的大小
	 */
	DataSetOperate(char* datafilename,int N);
	DataSetOperate();
	virtual ~DataSetOperate();
};


inline double DataSetOperate::calculateSMV(DataRecord& record){
	double sum = 0;
	for(unsigned int i=0;i!=record.data.size();++i){
		sum+= record.data[i]*record.data[i];
	}
	double smv =  sqrt(sum);
	record.smv = smv;
	return smv;
}

inline double DataSetOperate::calculateSMA(){
	double sma = 0;
	int n = slideWindow.size();
	DataRecord record;
	//遍历一遍
	for(int i=0;i != n;++i){
		record = slideWindow.front();
		for(unsigned int j = 0; j != record.data.size(); ++ j){
			sma +=fabs(record.data[j]);
		}
		slideWindow.pop();
		slideWindow.push(record);
	}

	sma /=n;

	return sma;
}

#endif /* READDATA_H_ */
