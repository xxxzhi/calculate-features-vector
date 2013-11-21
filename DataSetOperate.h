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

	//sequence name 的限制  是包含限制
	string select_contain_sequence;

	//tag identifitor 的限制
	string select_tag_identificator;



	unsigned int slideWindowSize = 10;
		//文件读取 滑动窗口
	queue<DataRecord> slideWindow;

	//文件
	ifstream infile;

	double calculateSMV(DataRecord& record);
	double CalculateSMA();

	DataRecord ReadRecordFromFile();

	bool RestrainSequenceName(const DataRecord& record);

	bool RestrainTagIdentificator(const DataRecord& record);


	bool RestrainOk(const DataRecord & record);
public:
	DataRecord ReadNext();

	/*
	 * N 表示 滑动窗口的大小
	 */
	DataSetOperate(char* datafilename,int N);
	DataSetOperate();
	virtual ~DataSetOperate();

	const string& GetSelectContainSequence() const {
		return select_contain_sequence;
	}

	void SetSelectContainSequence(const string& selectContainSequence) {
		select_contain_sequence = selectContainSequence;
	}

	const string& GetSelectTagIdentificator() const {
		return select_tag_identificator;
	}

	void SetSelectTagIdentificator(const string& selectTagIdentificator) {
		select_tag_identificator = selectTagIdentificator;
	}
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

inline bool DataSetOperate::RestrainTagIdentificator(const DataRecord& record){
	if(select_tag_identificator.length() <= 0){
		return true;
	}else{
		return record.tag_identificator.find(select_tag_identificator) >=0;
	}
}


inline bool DataSetOperate::RestrainSequenceName(const DataRecord& record){
	if(select_contain_sequence.length() <= 0){
		return true;
	}else{
		return record.sequence_name.find(select_contain_sequence) >=0;
	}
}


inline bool DataSetOperate::RestrainOk(const DataRecord& record){
	return RestrainSequenceName(record)&&RestrainTagIdentificator(record);
}

#endif /* READDATA_H_ */
