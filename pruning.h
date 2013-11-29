#ifndef PRUNING_H
#define PRUNING_H

#include <vector>
#include <algorithm>
#include <iostream>

vector<unsigned int> prune(vector< vector<unsigned int> > antennas){
	vector<unsigned int> output;
	for(unsigned int i = 0; i < antennas.size(); i++){
		sort(antennas[i].begin(), antennas[i].end());
	}
	//CHANGE THIS FOR LOOP FOR BETTER RESULTS.  EACH SPOT IS THE STARTING ANTENNA.
	for(unsigned int i = 0; i < 1; i++){
		vector<bool> valid_sets (antennas.size(), true);
		vector<unsigned int> cover_antennas;
		valid_sets[i] = false;
		for(unsigned int j = 0; j < antennas[i].size(); j++){
			cover_antennas.push_back(antennas[i][j]);
		}
		sort(cover_antennas.begin(), cover_antennas.end());
		unsigned int set_diff = 0;
		unsigned int best_diff = 0;
		int index_to_add = -1;
		while(find(valid_sets.begin(), valid_sets.end(), true) != valid_sets.end()){
			best_diff = cover_antennas.size();
			for(unsigned int j = 0; j < antennas.size(); j++){
				if(i == j || !valid_sets[j]) {
					continue;
				}
				vector<unsigned int> v(cover_antennas.size() + antennas[j].size());
				vector<unsigned int>::iterator it;
				it = set_symmetric_difference(cover_antennas.begin(),
					       	cover_antennas.end(),antennas[j].begin(),
					       	antennas[j].end(), v.begin());
				set_diff = (it - v.begin());
				if(set_diff <= cover_antennas.size()){
					valid_sets[j] = false;
				}
				else if(set_diff > best_diff){
					best_diff = set_diff;
					index_to_add = j;
				}
			}
			if(index_to_add != -1){
				for(unsigned int j = 0; j < antennas[index_to_add].size(); j++){
					cover_antennas.push_back(antennas[index_to_add][j]);
				}
				valid_sets[index_to_add] = false;
				index_to_add = -1;
			}
			sort(cover_antennas.begin(), cover_antennas.end());
		}
		auto temp = get_rid_of_dups(cover_antennas);
		if(temp.size() >= output.size()){
			output = temp;
		}
	}
	return output;
}
#endif
