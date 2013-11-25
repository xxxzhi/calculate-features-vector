/*
 * DataRecord.h
 *
 *  Created on: 2013年11月18日
 *      Author: houzhi
 */

#ifndef DATARECORD_H_
#define DATARECORD_H_

#include<string>
#include<vector>
#include<iostream>
using std::string;
using std::vector;

class DataRecord {
public:

	void printRecord(){
		std::cout<<sequence_name<<" " << tag_identificator<<" "<<timestamp<<" " << date<<" ";
		for(size_t i=0;i != features_vector.size();++i){
			std::cout<<features_vector[i] << " ";
		}

		std::cout<<activity <<std::endl;
	}

	/**
	 * 用作取一个记录的数据
	 */
	void genearateFeaturesVector(){
		features_vector.clear();
		for(size_t i=0;i != data.size(); ++i){
			features_vector.push_back(data[i]);
		}
		features_vector.push_back(smv);
		features_vector.push_back(sma);
	}

	DataRecord(){
		smv = 0;
		sma = 0;

		is_empty = false;

		dimens = 3;
	}

	virtual ~DataRecord(){
	}
	int dimens;
	bool is_empty;

	double smv ;
	double sma ;

	//文件中读取的数据
	vector<double> data;

	// 特征向量 最后两个数据是 smv 和sma
	vector<double> features_vector;

	string sequence_name  ;

	string tag_identificator  ;

	string timestamp  ;

	//格式化的日期
	string date  ;

	//分类
	string activity;

	bool IsFalling(){
		if(activity == "falling"){
			return true;
		}else{
			return false;
		}
	}
};

#endif /* DATARECORD_H_ */
