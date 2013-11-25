/*
 * DataRecord.h
 *
 *  Created on: 2013��11��18��
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
	 * ����ȡһ����¼������
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

	//�ļ��ж�ȡ������
	vector<double> data;

	// �������� ������������� smv ��sma
	vector<double> features_vector;

	string sequence_name  ;

	string tag_identificator  ;

	string timestamp  ;

	//��ʽ��������
	string date  ;

	//����
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
