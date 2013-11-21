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
	const string sign_split = "_";
	const string select_tag = "010-000-024-033";
	const string root_root = "I:\\Dropbox\\摔倒\\数据集\\Localization Data for Person Activity\\";
	string temp = "trains\\";
	string root = root_root+temp;
	DataSetOperate dataSet_opeate("I:\\Dropbox\\摔倒\\数据集\\Localization Data for Person Activity\\ConfLongDemo_JSI.txt",20);

	dataSet_opeate.SetSelectContainSequence(select_sequence);
	dataSet_opeate.SetSelectTagIdentificator(select_tag);

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
	int counts = 0;

	do{
		DataRecord record = dataSet_opeate.ReadNext();
		counts ++ ;
		if(record.is_empty){
			// 到了末尾
			break;
		}

		if(counts == 502 ){
			features_ofstream.close();
			activity_ofstream.close();
			features_all_ofstream.close();
			temp = "test\\";
			root = root_root + temp;
			file_name_features_vector = "features_vector";
			 features_ofstream.open(
					(root+file_name_features_vector+sign_split
							+select_sequence +sign_split +select_tag+suffix).c_str(),ios::out);

			file_name_features_vector = "activity";
			 activity_ofstream.open(
					(root+file_name_features_vector+sign_split
							+select_sequence+sign_split
							+select_tag+suffix).c_str(),ios::out);

			file_name_features_vector = "features_all";
			 features_all_ofstream.open(
					(root+file_name_features_vector+sign_split
							+select_sequence+sign_split
							+select_tag+suffix).c_str(),ios::out);
		}
		for(size_t i = 0 ; i != record.data.size() ; ++ i){
			features_ofstream << record.data[i] << "\t" ; ;
		}
		features_ofstream << endl;

		//全部特征 包含sma 之类的
		for(size_t i = 0 ; i != record.features_vector.size() ; ++ i){
			features_all_ofstream << record.features_vector[i] << "\t" ; ;
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
	cout << counts << endl;
}
