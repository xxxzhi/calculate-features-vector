/*
 * FeatureRecord.h
 *
 *  Created on: 2013年11月25日
 *      Author: houzhi
 */

#ifndef FEATURERECORD_H_
#define FEATURERECORD_H_

#include<vector>
#include<string>

using std::string;
using std::vector;


class FeatureRecord {
public:
	enum Status{

		FALLING = 1,
		NO_FALLING = 2,
	};

	bool is_empty;
	//滑动窗口的特征向量
	vector<double> feature_vector;

	Status activity;

	FeatureRecord(){
		is_empty = false;
	}
};

#endif /* FEATURERECORD_H_ */
