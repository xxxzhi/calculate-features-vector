/*
 * FeatureRecord.h
 *
 *  Created on: 2013��11��25��
 *      Author: houzhi
 */

#ifndef FEATURERECORD_H_
#define FEATURERECORD_H_

#include<vector>
#include<iostream>
#include<string>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class FeatureRecord {
public:
	enum Status{

		FALLING = 1,
		NO_FALLING = 2,
	};



	FeatureRecord(){
		is_empty = false;
	}

	void out(std::ostream& o){
		//ȫ������ ����sma ֮���
		for (size_t i = 0; i !=  feature_vector.size(); ++i) {
			double b = feature_vector[i];
			o << feature_vector[i] << "\t";
		}
		o << activity << endl;
	}


	bool is_empty;
		//�������ڵ���������
		vector<double> feature_vector;

		Status activity;
};

#endif /* FEATURERECORD_H_ */
