/*
 * ReadData_test.cpp
 *
 *  Created on: 2013年11月18日
 *      Author: houzhi
 */

#include "DataSetOperate.h"
#include "SingleTraveralRandom.h"
#include "ReadFeatureVector.h"
#include <sstream>
#include <fstream>

using namespace std;

const string select_sequence = "";
const string sign_split = "_";
const string select_tag = "010-000-024-033";
const string root_root =
		"I:\\Dropbox\\摔倒\\数据集\\Localization Data for Person Activity\\";
const string suffix = ".txt";
const string file_name_dataset = "dataset";
const int N = 20;

const int FALLING_SELECT_NUMS = 750;
const int FALLING_SELECT_TRAIN = FALLING_SELECT_NUMS * (0.8);
const int falling_select_test = FALLING_SELECT_NUMS - FALLING_SELECT_TRAIN;

const int NO_FALLING_SELECT_NUMS = 25000;
const int NO_FALLING_SELECT_TRAIN = NO_FALLING_SELECT_NUMS * (0.8);
const int no_falling_select_test = NO_FALLING_SELECT_NUMS
		- NO_FALLING_SELECT_TRAIN;

vector<FeatureRecord> vector_feature_select;
vector<FeatureRecord> vector_feature_falling;
vector<FeatureRecord> vector_feature_no_falling;
bool should_select[20000];
int sum_record = 0;

void TestRecrod() {
	cout << "hello" << endl;

	string temp = "trains\\";
	string root = root_root + temp;
	DataSetOperate dataSet_opeate(
			"I:\\Dropbox\\摔倒\\数据集\\Localization Data for Person Activity\\ConfLongDemo_JSI.txt",
			N);

	dataSet_opeate.SetSelectContainSequence(select_sequence);
	dataSet_opeate.SetSelectTagIdentificator(select_tag);

	//features vector  array
	vector<vector<double> > features_vecotr_arr;
	//对应的类别
	vector<string> activity_arr;

	string file_name_features_vector = "ffeatures_vector";
	ofstream features_ofstream(
			(root + file_name_features_vector + sign_split + select_sequence
					+ sign_split + select_tag + suffix).c_str(), ios::out);

	file_name_features_vector = "factivity";
	ofstream activity_ofstream(
			(root + file_name_features_vector + sign_split + select_sequence
					+ sign_split + select_tag + suffix).c_str(), ios::out);

	file_name_features_vector = "ffeatures_all";
	ofstream features_all_ofstream(
			(root + file_name_features_vector + sign_split + select_sequence
					+ sign_split + select_tag + suffix).c_str(), ios::out);
	int counts = 0;

	do {
		DataRecord record = dataSet_opeate.ReadNext();
		counts++;
		if (record.is_empty) {
			// 到了末尾
			break;
		}

		if (counts == 502) {
			features_ofstream.close();
			activity_ofstream.close();
			features_all_ofstream.close();
			temp = "test\\";
			root = root_root + temp;
			file_name_features_vector = "features_vector";
			features_ofstream.open(
					(root + file_name_features_vector + sign_split
							+ select_sequence + sign_split + select_tag + suffix).c_str(),
					ios::out);

			file_name_features_vector = "activity";
			activity_ofstream.open(
					(root + file_name_features_vector + sign_split
							+ select_sequence + sign_split + select_tag + suffix).c_str(),
					ios::out);

			file_name_features_vector = "features_all";
			features_all_ofstream.open(
					(root + file_name_features_vector + sign_split
							+ select_sequence + sign_split + select_tag + suffix).c_str(),
					ios::out);
		}
		for (size_t i = 0; i != record.data.size(); ++i) {
			features_ofstream << record.data[i] << "\t";
			;
		}
		features_ofstream << endl;

		//全部特征 包含sma 之类的
		for (size_t i = 0; i != record.features_vector.size(); ++i) {
			features_all_ofstream << record.features_vector[i] << "\t";

		}
		features_all_ofstream << endl;

		if (record.activity == "walking") {
			activity_ofstream << 1 << endl;
		} else if (record.activity == "falling") {
			activity_ofstream << 2 << endl;
		} else if (record.activity == "lying down") {
			activity_ofstream << 3 << endl;
		} else if (record.activity == "lying") {
			activity_ofstream << 4 << endl;
		} else if (record.activity == "sitting down") {
			activity_ofstream << 5 << endl;
		} else if (record.activity == "sitting") {
			activity_ofstream << 6 << endl;
		} else if (record.activity == "standing up from lying") {
			activity_ofstream << 7 << endl;
		} else if (record.activity == "on all fours") {
			activity_ofstream << 8 << endl;
		} else if (record.activity == "sitting on the ground") {
			activity_ofstream << 9 << endl;
		} else if (record.activity == "standing up from sitting") {
			activity_ofstream << 10 << endl;
		} else {
			activity_ofstream << 11 << endl;
		}

	} while (true);
	cout << counts << endl;
}

void RandomSelect(string index) {

	string filename = root_root + file_name_dataset + sign_split
			+ select_sequence + sign_split + select_tag + suffix;
	ReadFeatureVector dataSet_opeate(filename, N * 5);
	string temp = "trains\\";
	string root = root_root + temp;
	//features vector  array
	vector<vector<double> > features_vecotr_arr;
	//对应的类别
	vector<string> activity_arr;

	string file_name_features_vector = "features_vector";

	file_name_features_vector = "activity";
	file_name_features_vector += index;
	ofstream activity_ofstream(
			(root + file_name_features_vector + sign_split + select_sequence
					+ sign_split + select_tag + suffix).c_str(),
			ios::out | ios::app);

	file_name_features_vector = "features_all";
	file_name_features_vector += index;
	ofstream features_all_ofstream(
			(root + file_name_features_vector + sign_split + select_sequence
					+ sign_split + select_tag + suffix).c_str(),
			ios::out | ios::app);
	int counts = 0;

	//随机函数
	SingleTraveralRandom falling_random(FALLING_SELECT_TRAIN);
	SingleTraveralRandom no_falling_random(NO_FALLING_SELECT_NUMS);
	int falling_counts = 0, no_falling_counts = 0;

	bool is_train = true;
	do {
		FeatureRecord record = dataSet_opeate.readNext();
		if (record.is_empty) {
			// 到了末尾
			break;
		}

		int is_select = -1;
		//判断是否为falling
		switch (record.activity) {
		case FeatureRecord::FALLING:
			is_select = falling_random.SingleTraversal();
			break;
		case FeatureRecord::NO_FALLING:
			is_select = no_falling_random.SingleTraversal();
			break;
		default:
			is_select = -1;
		}
		if (is_select < 0) {
			continue;
		}
		bool change_to_test = false;
		counts++;
		//判断是否为falling
		switch (record.activity) {
		case FeatureRecord::FALLING:
			falling_counts++;

			if (falling_counts > FALLING_SELECT_TRAIN) {
				if (falling_counts > FALLING_SELECT_NUMS) {
					continue;
				} else {
					change_to_test = true;
				}
			} else {
				change_to_test = false;
			}
			break;
		case FeatureRecord::NO_FALLING:
			no_falling_counts++;
			if (no_falling_counts > NO_FALLING_SELECT_TRAIN) {
				if (no_falling_counts > NO_FALLING_SELECT_NUMS) {
					continue;
				} else {
					change_to_test = true;
				}
			} else {
				change_to_test = false;
			}
			break;
		default:
//			assert(false);
			break;
		}
		if (falling_counts > FALLING_SELECT_NUMS
				&& no_falling_counts > NO_FALLING_SELECT_NUMS) {
			break;
		}
		if (change_to_test && is_train) {

			activity_ofstream.close();
			features_all_ofstream.close();
			temp = "test\\";
			root = root_root + temp;

			file_name_features_vector = "activity";
			file_name_features_vector += index;
			activity_ofstream.open(
					(root + file_name_features_vector + sign_split
							+ select_sequence + sign_split + select_tag + suffix).c_str(),
					ios::out | ios::app);

			file_name_features_vector = "features_all";
			file_name_features_vector += index;
			features_all_ofstream.open(
					(root + file_name_features_vector + sign_split
							+ select_sequence + sign_split + select_tag + suffix).c_str(),
					ios::out | ios::app);

			is_train = false;
		} else {
			if (!change_to_test && !is_train) {
				is_train = true;

				activity_ofstream.close();
				features_all_ofstream.close();
				temp = "trains\\";
				root = root_root + temp;

				file_name_features_vector = "activity";
				file_name_features_vector += index;
				activity_ofstream.open(
						(root + file_name_features_vector + sign_split
								+ select_sequence + sign_split + select_tag
								+ suffix).c_str(), ios::out | ios::app);

				file_name_features_vector = "features_all";
				file_name_features_vector += index;
				features_all_ofstream.open(
						(root + file_name_features_vector + sign_split
								+ select_sequence + sign_split + select_tag
								+ suffix).c_str(), ios::out | ios::app);

			}
		}
		//全部特征 包含sma 之类的
		for (size_t i = 0; i != record.feature_vector.size(); ++i) {
			features_all_ofstream << record.feature_vector[i] << "\t";
		}
		features_all_ofstream << endl;

		activity_ofstream << record.activity << endl;

	} while (true);

	activity_ofstream.close();
	features_all_ofstream.close();

	cout << counts << endl;
}

/**
 * 滑动窗口
 * 随机选择 no_falling   falling
 */

void readFeatureRecord() {
	string root = root_root;
	DataSetOperate dataSet_opeate(
			"I:\\Dropbox\\摔倒\\数据集\\Localization Data for Person Activity\\ConfLongDemo_JSI.txt",
			20);

	dataSet_opeate.SetSelectContainSequence(select_sequence);
	dataSet_opeate.SetSelectTagIdentificator(select_tag);

	//features vector  array
	vector<vector<double> > features_vecotr_arr;
	//对应的类别
	vector<string> activity_arr;
	string file_name_features_vector = "dataset";

	ofstream select_dataset_ofstream(
			(root + file_name_features_vector + sign_split + select_sequence
					+ sign_split + select_tag + suffix).c_str(), ios::out);

	int counts = 0;

	//随机函数
	SingleTraveralRandom falling_random(FALLING_SELECT_NUMS);
	SingleTraveralRandom no_falling_random(NO_FALLING_SELECT_NUMS);
	int falling_counts = 0, no_falling_counts = 0;
	do {
		FeatureRecord record = dataSet_opeate.ReadNextFeatureRecord();
		if (record.is_empty) {
			// 到了末尾
			break;
		}

		bool is_select = false;
		int activity_code = 0;
		//判断是否为falling
		switch (record.activity) {
		case FeatureRecord::FALLING:
			is_select = falling_random.SingleTraversal();
			activity_code = 1;
			break;
		case FeatureRecord::NO_FALLING:
			is_select = no_falling_random.SingleTraversal();
			activity_code = 2;
			break;
		default:
			is_select = false;
		}

		counts++;

		//随机选
		if (!is_select) {
			continue;
		}

		//判断是否为falling
		switch (record.activity) {
		case FeatureRecord::FALLING:
			falling_counts++;
			if (falling_counts > FALLING_SELECT_NUMS
					&& no_falling_counts < NO_FALLING_SELECT_NUMS) {

				continue;
			}

			break;
		case FeatureRecord::NO_FALLING:
			no_falling_counts++;
			if (falling_counts < FALLING_SELECT_NUMS
					&& no_falling_counts > NO_FALLING_SELECT_NUMS) {
				continue;
			}
			break;
		default:
			//			assert(false);
			break;
		}
		if (falling_counts > FALLING_SELECT_NUMS
				&& no_falling_counts > NO_FALLING_SELECT_NUMS) {
			break;
		}

		record.out(select_dataset_ofstream);
		if (activity_code == 1) {
			cout << activity_code << endl;
			//		exit(0);
		}
	} while (true);
	select_dataset_ofstream.close();
	cout << counts << endl;
}

void RandomSplitOnMemory(int nums) {
	srand(time(0));
	vector<FeatureRecord> vector_falling_temp ;
	vector<FeatureRecord> vector_no_falling_temp ;
	char a[10];
	string index;

	for (int i = 1; i != nums + 1; i++) {
		vector_falling_temp = vector_feature_falling;
		vector_no_falling_temp = vector_feature_no_falling;
		itoa(i, a, 10);
		index = a;
		string temp = "trains\\";
		string root = root_root + temp;
		string file_name_features_vector = "activity";
		file_name_features_vector += index;
		ofstream activity_ofstream(
				(root + file_name_features_vector + sign_split + select_sequence
						+ sign_split + select_tag + suffix).c_str(),
				ios::out | ios::app);

		file_name_features_vector = "features_all";
		file_name_features_vector += index;
		ofstream features_all_ofstream(
				(root + file_name_features_vector + sign_split + select_sequence
						+ sign_split + select_tag + suffix).c_str(),
				ios::out | ios::app);
		//falling trains
		for (int i = 0; i != FALLING_SELECT_TRAIN; ++i) {
			int p = 0;
			if(vector_falling_temp.size() != 0){
				p = rand() % vector_falling_temp.size();
			}

			for (size_t i = 0; i != vector_falling_temp.at(p).feature_vector.size(); ++i) {
				features_all_ofstream << vector_falling_temp.at(p).feature_vector[i]
						<< "\t";
			}
			features_all_ofstream << endl;
			activity_ofstream << vector_falling_temp.at(p).activity << endl;

			vector<FeatureRecord>::iterator iter= vector_falling_temp.begin() +p;
			vector_falling_temp.erase(iter);
		}

		//no falling trains
		for (int i = 0; i != NO_FALLING_SELECT_TRAIN; ++i) {

			int p = 0;
			if(vector_no_falling_temp.size() != 0){
				p = rand() % vector_no_falling_temp.size();
			}

			for (size_t i = 0; i != vector_no_falling_temp.at(p).feature_vector.size(); ++i) {
				features_all_ofstream << vector_no_falling_temp.at(p).feature_vector[i]
						<< "\t";
			}
			features_all_ofstream << endl;
			activity_ofstream << vector_no_falling_temp.at(p).activity << endl;

			vector<FeatureRecord>::iterator iter= vector_no_falling_temp.begin() +p;
			vector_no_falling_temp.erase(iter);
		}

		if(vector_feature_falling.size() > 75){
			cout<< "vector_feature_falling > 75" <<endl;
		}
		//close
		activity_ofstream.close();
		features_all_ofstream.close();



		temp = "test\\";
		root = root_root + temp;
		file_name_features_vector = "activity";
		file_name_features_vector += index;
		activity_ofstream.open(
				(root + file_name_features_vector + sign_split + select_sequence
						+ sign_split + select_tag + suffix).c_str(),
				ios::out | ios::app);

		file_name_features_vector = "features_all";
		file_name_features_vector += index;
		features_all_ofstream.open(
				(root + file_name_features_vector + sign_split + select_sequence
						+ sign_split + select_tag + suffix).c_str(),
				ios::out | ios::app);
		for(vector<FeatureRecord>::iterator iter = vector_falling_temp.begin();
				iter != vector_falling_temp.end(); ++iter){
			for (size_t i = 0; i != iter->feature_vector.size(); ++i) {
				features_all_ofstream << iter->feature_vector[i]
						<< "\t";
			}
			features_all_ofstream << endl;
			activity_ofstream << iter->activity << endl;
		}
		for(vector<FeatureRecord>::iterator iter = vector_no_falling_temp.begin();
						iter != vector_no_falling_temp.end(); ++iter){
			for (size_t i = 0; i != iter->feature_vector.size(); ++i) {
				features_all_ofstream << iter->feature_vector[i]
						<< "\t";
			}
			features_all_ofstream << endl;
			activity_ofstream << iter->activity << endl;
		}
		//close
		activity_ofstream.close();
		features_all_ofstream.close();
	}

}

void RandomSlpit(int nums) {
	int i = 456;
	char a[10];
	string str;

	itoa(i, a, 10);
	str = a;
	for (int i = 1; i != nums + 1; i++) {
		itoa(i, a, 10);
		str = a;
		RandomSelect(str);
	}
}


/**
 * 滑动窗口
 * 随机选择 no_falling   falling
 */
void TestFeatureRecord() {

	string root = root_root;
	DataSetOperate dataSet_opeate(
			"I:\\Dropbox\\摔倒\\数据集\\Localization Data for Person Activity\\ConfLongDemo_JSI.txt",
			N);

	dataSet_opeate.SetSelectContainSequence(select_sequence);
	dataSet_opeate.SetSelectTagIdentificator(select_tag);

	int counts = 0;

	//随机函数
	SingleTraveralRandom falling_random(FALLING_SELECT_NUMS);
	SingleTraveralRandom no_falling_random(NO_FALLING_SELECT_NUMS);
	int falling_counts = 0, no_falling_counts = 0;
	do {
		FeatureRecord record = dataSet_opeate.ReadNextFeatureRecord();
		if (record.is_empty) {
			// 到了末尾
			break;
		}
		counts++;
		int insert_position = -1;
		int activity_code = 0;
		//判断是否为falling
		switch (record.activity) {
		case FeatureRecord::FALLING:
			insert_position = falling_random.SingleTraversal();
			activity_code = 1;
			//随机选
			if (insert_position < 0) {
				continue;
			} else {
				if (vector_feature_falling.size() == insert_position) {
					vector_feature_falling.push_back(record);
				} else {
					vector_feature_falling[insert_position] = record;
				}
			}

			break;
		case FeatureRecord::NO_FALLING:
			insert_position = no_falling_random.SingleTraversal();
			activity_code = 2;
			//随机选
			if (insert_position < 0) {
				continue;
			} else {
				if (vector_feature_no_falling.size() == insert_position) {
					vector_feature_no_falling.push_back(record);
				} else {
					vector_feature_no_falling[insert_position] = record;
				}
			}
			break;
		default:
			insert_position = -1;
		}

	} while (true);
	cout << counts << endl;
}


int main() {
	vector_feature_select.clear();
	TestFeatureRecord();
	cout<<vector_feature_falling.size()<<" "<<vector_feature_no_falling.size() << endl;
	for(vector<FeatureRecord>::iterator iter = vector_feature_falling.begin();
			iter != vector_feature_falling.end(); ++iter){
		vector_feature_select.push_back(*iter);
	}
	for(vector<FeatureRecord>::iterator iter = vector_feature_no_falling.begin();
				iter != vector_feature_no_falling.end(); ++iter){
			vector_feature_select.push_back(*iter);
	}
	int a = vector_feature_select.size();
	cout<<vector_feature_select.size();
	RandomSplitOnMemory(5);
//	RandomSlpit(5);
}

