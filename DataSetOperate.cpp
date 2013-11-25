/*
 * DataSetOperate.cpp
 *
 *  Created on: 2013��11��18��
 *      Author: houzhi
 */

#include "DataSetOperate.h"

#include "stdlib.h"

/**
 * ��־�Ż������ڳ��ֶ��ٸ�falling ʱ����ʾ��ˤ����
 */
const int DataSetOperate::FALLING_COUNTS_SIGN = 3;

DataSetOperate::DataSetOperate() {

}

double DataSetOperate::CalculateSMA() {
	double sma = 0;
	int n = slideWindow.size();
	DataRecord record;
	//����һ��
	for (int i = 0; i != n; ++i) {
		record = slideWindow.front();
		for (unsigned int j = 0; j != record.data.size(); ++j) {
			sma += fabs(record.data[j]);
		}
		slideWindow.pop();
		slideWindow.push(record);
	}

	sma /= n;

	return sma;
}

DataSetOperate::DataSetOperate(char*datafilename, int N) {
	slideWindowSize = N;
	infile.open(datafilename, ios::in);

	if (!infile.is_open()) {
		cout << "error: file" << datafilename << " open fail!" << std::endl;
	}
	//���ú�n �����㷨
//	DataRecord record;
//	//��ȡһ����¼
//	for(int i=0;i!=N;++i){
//		record = readRecordFromFile();
//		if(record.is_empty){
//			break;
//		}
//		slideWindow.push(record);
//	}

}
/**
 *
 *���ļ��ж�ȡһ������
 */
DataRecord DataSetOperate::ReadRecordFromFile() {
	DataRecord record;
	if (!infile.is_open()) {
		record.is_empty = true;
		return record;
	}

	do {
		//��ȡ��¼ �����ļ�������ʽ����
		if (infile.eof()) {
			record.is_empty = true;
			infile.close();
			return record;
		}
		string str_record;
		getline(infile, str_record);

		//�滻����
		for (int i = 0; i != str_record.size(); ++i) {

			//ʱ������
			if (str_record[i] == ' ') {
				str_record[i] = '-';
			}

			if (str_record[i] == ',') {
				str_record[i] = ' ';
			}

		}

		istringstream istring_record(str_record);

		istring_record >> record.sequence_name >> record.tag_identificator
				>> record.timestamp >> record.date;
		record.data.clear();
		for (int i = 0; i != record.dimens; ++i) {
			double atemp = 0;
			istring_record >> atemp;
			record.data.push_back(atemp);
		}

		istring_record >> record.activity;
	} while (!RestrainOk(record));
	return record;
}

/*
 * ��ȡ��һ��
 */
DataRecord DataSetOperate::ReadNext() {
	DataRecord record_return;
	do{
		record_return = ReadRecordFromFile();

		//�Ƿ�Ϊ�� ��ʾ�Ѿ������ļ�β��
		if (record_return.is_empty) {
			return record_return;
		}

		//����sma smv
		record_return.smv = calculateSMV(record_return);
		record_return.sma = CalculateSMA();

		record_return.genearateFeaturesVector();

		//�����޶����ڴ�С ���Ƴ�����ǰ������ݣ�
		if (slideWindow.size() == slideWindowSize) {
			slideWindow.pop();
		}
	slideWindow.push(record_return);
	}while(slideWindow.size() < slideWindowSize);
	//����n �����ݵ�����
//	//�Ѿ�û��������
//	if(slideWindow.size() == 0){
//		record_return.is_empty = true;
//		return record_return;
//	}
//	record_return = slideWindow.front();
//	slideWindow.pop();
//	//����
//	if( !(record2.is_empty)){
//		slideWindow.push(record2);
//	}

	return record_return;
}

FeatureRecord DataSetOperate::ReadNextFeatureRecord() {
	DataRecord record = ReadNext();
	FeatureRecord feature_record;

	if (record.is_empty) {
		feature_record.is_empty = true;
		return feature_record;
	}

	int size = slideWindow.size();
	double sma = 0;
	//����һ��
	for (int i = 0; i != size; ++i) {
		record = slideWindow.front();
		for (unsigned int j = 0; j != record.data.size(); ++j) {
			sma += fabs(record.data[j]);
		}
		slideWindow.pop();
		slideWindow.push(record);
	}

	sma /= size;


	size_t falling_counts = 0;

	feature_record.feature_vector.clear();
	for (size_t i = 0; i != size; ++i) {
		DataRecord record = slideWindow.front();
		slideWindow.pop();
		for (size_t j = 0; j != record.data.size(); ++j) {
			feature_record.feature_vector.push_back(record.data[j]);
		}
		record.sma = sma;
		feature_record.feature_vector.push_back(record.smv);
		feature_record.feature_vector.push_back(record.sma);

		//�Ƿ�Ϊ����
		if (record.IsFalling()) {
			falling_counts++;
		}

		slideWindow.push(record);
	}

	//��־�Ŵ�������������ˤ��
	if (falling_counts > FALLING_COUNTS_SIGN) {
		feature_record.activity = feature_record.FALLING;
	} else {
		feature_record.activity = feature_record.NO_FALLING;
	}

	return feature_record;
}


DataSetOperate::~DataSetOperate() {

}

