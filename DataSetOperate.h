/*
 * DataSetOperate.h
 *
 *  Created on: 2013��11��18��
 *      Author: houzhi
 */

#ifndef READDATA_H_
#define READDATA_H_

#include "DataRecord.h"
#include "FeatureRecord.h"

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

public:

	static const int FALLING_COUNTS_SIGN;
	DataRecord ReadNext();

	FeatureRecord ReadNextFeatureRecord();
	/*
	 * N ��ʾ �������ڵĴ�С
	 */
	DataSetOperate(char* datafilename, int N);
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
private:

	double calculateSMV(DataRecord& record);
	double CalculateSMA();

	DataRecord ReadRecordFromFile();

	bool RestrainSequenceName(const DataRecord& record);

	bool RestrainTagIdentificator(const DataRecord& record);

	bool RestrainOk(const DataRecord & record);

	//sequence name ������  �ǰ�������
	string select_contain_sequence;

	//tag identifitor ������
	string select_tag_identificator;

	unsigned int slideWindowSize = 10;
	//�ļ���ȡ ��������
	queue<DataRecord> slideWindow;

	//�ļ�
	ifstream infile;

	string last_sequence_name;
};


inline double DataSetOperate::calculateSMV(DataRecord& record) {
	double sum = 0;
	for (unsigned int i = 0; i != record.data.size(); ++i) {
		sum += record.data[i] * record.data[i];
	}
	double smv = sqrt(sum);
	record.smv = smv;
	return smv;
}

inline bool DataSetOperate::RestrainTagIdentificator(const DataRecord& record) {
	if (select_tag_identificator.length() <= 0) {
		return true;
	} else {
		string::size_type pos = record.tag_identificator.find(
				select_tag_identificator);
		if (pos != string::npos)
			return true;
		else
			return false;
	}
}

inline bool DataSetOperate::RestrainSequenceName(const DataRecord& record) {
	if (select_contain_sequence.length() <= 0) {
		return true;
	} else {
		string::size_type pos = record.sequence_name.find(
				select_contain_sequence);
		if (pos != string::npos)
			return true;
		else
			return false;
	}
}

inline bool DataSetOperate::RestrainOk(const DataRecord& record) {
	return RestrainSequenceName(record) && RestrainTagIdentificator(record);
}

#endif /* READDATA_H_ */
