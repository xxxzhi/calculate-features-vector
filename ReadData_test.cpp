/*
 * ReadData_test.cpp
 *
 *  Created on: 2013年11月18日
 *      Author: houzhi
 */

#include "DataSetOperate.h"
#include <sstream>

using std::istringstream;

int main(){
	cout<<"hello"<<endl;


	DataSetOperate dataSet_opeate("I:\\Dropbox\\摔倒\\数据集\\Localization Data for Person Activity\\ConfLongDemo_JSI.txt",20);

	//一条一条地读取出来 测试20条
	for(int i=0;i!=20;++i)
		dataSet_opeate.readNext().printRecord();

	//features vector  array
	vector<vector<double>> features_vecotr_arr ;
	//对应的类别
	vector<string> activity_arr;
	do{
		DataRecord record = dataSet_opeate.readNext();

		if(record.is_empty){
			// 到了末尾
			break;
		}
		features_vecotr_arr.push_back(record.features_vector);
		activity_arr.push_back(record.activity);
	}while(true);
}
