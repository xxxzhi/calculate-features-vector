/*
 * ReadData_test.cpp
 *
 *  Created on: 2013��11��18��
 *      Author: houzhi
 */

#include "DataSetOperate.h"
#include <sstream>

using std::istringstream;

int main(){
	cout<<"hello"<<endl;


	DataSetOperate dataSet_opeate("I:\\Dropbox\\ˤ��\\���ݼ�\\Localization Data for Person Activity\\ConfLongDemo_JSI.txt",20);

	//һ��һ���ض�ȡ���� ����20��
	for(int i=0;i!=20;++i)
		dataSet_opeate.readNext().printRecord();

	//features vector  array
	vector<vector<double>> features_vecotr_arr ;
	//��Ӧ�����
	vector<string> activity_arr;
	do{
		DataRecord record = dataSet_opeate.readNext();

		if(record.is_empty){
			// ����ĩβ
			break;
		}
		features_vecotr_arr.push_back(record.features_vector);
		activity_arr.push_back(record.activity);
	}while(true);
}
