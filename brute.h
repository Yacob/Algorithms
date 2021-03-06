#ifndef BRUTE_H_
#define BRUTE_H_

#include <vector>
#include <algorithm>
#include "util.h"

using namespace std;



vector<unsigned int> bruteForce(vector <vector <unsigned int> > antennas){
	
	vector< vector<unsigned int> > combs =  gen_combs(antennas.size());
	vector <unsigned int> best_comb;
	int best_value = 0;
	for( auto comb: combs){
		int value = evaluate(comb, antennas);
		if(value > best_value){
			best_value = value;
			best_comb = comb;
		}
	}
	//string out = formatResult(best_comb, antennas);
	return best_comb;
}

#endif
