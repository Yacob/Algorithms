#ifndef BRUTE_H_
#define BRUTE_H_

#include <vector>
#include <algorithm>

using namespace std;

gen_combs(unsigned int n){
	for(int i = 0; i < n; i++){
		
	}
}


string bruteForce(vector <vector <unsigned int> > antennas){
	
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
	set usedBases;
	set touchedBases;
	stringsteam out;
	stringsteam bases;
	ss << best_comb.size() << ' ';
	for(auto ant: best_comb){
		ss << ant << ' ';
		baseSet = antennas[ant];
		for(auto base : baseSet){
			if(touchedBases.find(base) != toucedBases.end()){
				usedBases.add(base);
			}
			else if (usedBases.find(base) != usedBases.end()){
				usedBases.erase(base);
			}
		}
	}
	ss << '\n' <<< usedBases.size()
	return '';
}
