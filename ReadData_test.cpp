/*
 * ReadData_test.cpp
 *
 *  Created on: 2013年11月18日
 *      Author: houzhi
 */

#include "DataSetOperate.h"
#include <sstream>
#include <fstream>

using namespace std;

int main(){
	cout<<"hello"<<endl;

	const string select_sequence = "A01";
	const string sign_split = "-";
	const string select_tag = "010-000-024-033";
	const string root = "I:\\Dropbox\\摔倒\\数据集\\Localization Data for Person Activity\\";
	DataSetOperate dataSet_opeate("I:\\Dropbox\\摔倒\\数据集\\Localization Data for Person Activity\\ConfLongDemo_JSI.txt",20);

	dataSet_opeate.SetSelectContainSequence("A01");
	dataSet_opeate.SetSelectTagIdentificator("010-000-024-033");

	//features vector  array
	vector< vector<double> > features_vecotr_arr ;
	//对应的类别
	vector<string> activity_arr;

	string file_name_features_vector = "features_vector";
	string suffix = ".txt";
	ofstream features_ofstream(
			(root+file_name_features_vector+sign_split
					+select_sequence +sign_split +select_tag+suffix).c_str(),ios::out);

	file_name_features_vector = "activity";
	ofstream activity_ofstream(
			(root+file_name_features_vector+sign_split
					+select_sequence+sign_split
					+select_tag+suffix).c_str(),ios::out);

	file_name_features_vector = "features_all";
	ofstream features_all_ofstream(
			(root+file_name_features_vector+sign_split
					+select_sequence+sign_split
					+select_tag+suffix).c_str(),ios::out);

	do{
		DataRecord record = dataSet_opeate.ReadNext();

		if(record.is_empty){
			// 到了末尾
			break;
		}
		for(size_t i = 0 ; i != record.data.size() ; ++ i){
			features_ofstream << record.data[i] ;
		}
		features_ofstream << endl;

		//全部特征 包含sma 之类的
		for(size_t i = 0 ; i != record.features_vector.size() ; ++ i){
			features_all_ofstream << record.features_vector[i] ;
		}
		features_all_ofstream << endl;
		if(record.activity == "walking"){
			activity_ofstream <<1<< endl;
		}else if (record.activity == "falling"){
			activity_ofstream <<2<< endl;
		}else if (record.activity == "lying down"){
			activity_ofstream <<3<< endl;
		}else if (record.activity == "lying"){
			activity_ofstream <<4<< endl;
		}else if (record.activity == "sitting down"){
			activity_ofstream <<5<< endl;
		}else if (record.activity == "sitting"){
			activity_ofstream <<6<< endl;
		}else if (record.activity == "standing up from lying"){
			activity_ofstream <<7<< endl;
		}else if (record.activity == "on all fours"){
			activity_ofstream <<8<< endl;
		}else if (record.activity == "sitting on the ground"){
			activity_ofstream <<9<< endl;
		}else if (record.activity == "standing up from sitting"){
			activity_ofstream <<10<< endl;
		}else{
			activity_ofstream <<11<< endl;
		}


	}while(true);
}
