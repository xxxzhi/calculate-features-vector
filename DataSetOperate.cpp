/*
 * DataSetOperate.cpp
 *
 *  Created on: 2013��11��18��
 *      Author: houzhi
 */

#include "DataSetOperate.h"

#include "stdlib.h"
DataSetOperate::DataSetOperate() {

}


double DataSetOperate::CalculateSMA(){
	double sma = 0;
	int n = slideWindow.size();
	DataRecord record;
	//����һ��
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

DataSetOperate::DataSetOperate(char*datafilename,int N){
	slideWindowSize = N;
	infile.open(datafilename,ios::in);

	if(!infile.is_open()){
		cout<<"error: file"<< datafilename <<" open fail!"<<std::endl;
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
DataRecord DataSetOperate::ReadRecordFromFile(){
	DataRecord record;
	if(!infile.is_open()){
		record.is_empty = true;
		return record;
	}


	do{
		//��ȡ��¼ �����ļ�������ʽ����
		if( infile.eof()){
			record.is_empty = true;
			infile.close();
			return record;
		}
		string str_record;
		getline(infile,str_record);

		//�滻����
		for(int i=0;i != str_record.size() ; ++i){

			//ʱ������
			if(str_record[i] ==' '){
				str_record[i] = '-';
			}

			if(str_record[i] == ','){
				str_record[i] =' ';
			}

		}

		istringstream istring_record(str_record);

		istring_record >>record.sequence_name >> record.tag_identificator
				>> record.timestamp >> record.date;

		for(int i=0; i !=record.dimens ; ++i ){
			double atemp=0;
			istring_record >>atemp;
			record.data.push_back(atemp);
		}

		istring_record >> record.activity;
	}while(!RestrainOk(record));
	return record;
}

/*
 * ��ȡ��һ��
 */
DataRecord DataSetOperate::ReadNext(){
	DataRecord record_return;

	record_return = ReadRecordFromFile();

	//�Ƿ�Ϊ�� ��ʾ�Ѿ������ļ�β��
	if(record_return.is_empty ){
		return record_return;
	}

	//�����޶����ڴ�С ���Ƴ�����ǰ������ݣ�
	if(slideWindow.size() == slideWindowSize){
		slideWindow.pop();
	}
	slideWindow.push(record_return);

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

	//����sma smv
	record_return.smv = calculateSMV(record_return);
	record_return.sma = CalculateSMA();

	record_return.genearateFeaturesVector();
	return record_return;
}



DataSetOperate::~DataSetOperate() {

}

