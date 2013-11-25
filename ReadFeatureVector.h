/*
 * ReadFeatureVector.h
 *
 *  Created on: 2013Äê11ÔÂ25ÈÕ
 *      Author: houzhi
 */

#ifndef READFEATUREVECTOR_H_
#define READFEATUREVECTOR_H_


#include "FeatureRecord.h"

#include <string>
#include <fstream>


using namespace std;

class ReadFeatureVector {
public:
	ReadFeatureVector(string filename,int dimens){
		infile.open(filename.c_str(),ios::in);
		if(!infile.is_open()){
			cout<<"open file error!"<<filename<<endl;
		}

		this -> dimens = dimens;
	}

	FeatureRecord readNext(){


		FeatureRecord record ;
		if(infile.eof()){
			infile.close();
			record.is_empty = true;
			return record;
		}

		for(size_t i = 0; i != dimens; ++i){
			double d ;
			infile >> d;
			record.feature_vector.push_back(d);
		}
		int s;
		infile>> s;
		switch(s){
		case FeatureRecord::FALLING:
			record.activity = FeatureRecord::FALLING;
			break;
		case FeatureRecord::NO_FALLING:
			record.activity = FeatureRecord::NO_FALLING;
			break;
		}
		return record;
	}
private :
	std::ifstream infile;
	int dimens;
};

#endif /* READFEATUREVECTOR_H_ */
