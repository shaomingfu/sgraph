#include <string>
#include <sstream>
//#include <iomanip>
#include "iostream"
//#include <fstream>
#include <vector>

#include "stdafx.h"
#include "statistics.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "interpolation.h"

using namespace std;
using namespace alglib;

string vector2string(const vector<int> &x){
	string result_str = "[";

	for( int i=0; i<x.size(); i++){
		stringstream ss;
		ss << x[i];

		if(i != x.size()-1)
			result_str += ss.str() + ",";
		else
			result_str += ss.str() + "]";
	}
	return result_str;
}

double compute_mann_whitney_pvalue(const vector<int> &x, const vector<int> &y){
	
	real_1d_array x1 = vector2string(x).c_str();
	real_1d_array y1 = vector2string(y).c_str();

	ae_int_t n = x.size();
	ae_int_t m = y.size();

	double bothtails,lefttail,righttail;

	mannwhitneyutest(x1,n,y1,m,bothtails,lefttail,righttail);	

	printf("%.5f\n", double(bothtails));
   	printf("%.5f\n", double(lefttail));
   	printf("%.5f\n", double(righttail));
    
	return double(bothtails);
}

int main(int argc, char **argv){
	
	int xx[] = {15,15,15,15,15,14,14,14,13,13,12,12,10};
	int yy[] = {10,10,10,9,9,8,8,8,8,7,7,4,4,2,2,2,3,2,2};

	vector<int> x(xx, xx + sizeof(xx) / sizeof(int));
	vector<int> y(yy, yy + sizeof(yy) / sizeof(int));
	double pvalue = compute_mann_whitney_pvalue(x, y);

	return 0;
}
