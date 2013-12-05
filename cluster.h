#ifndef PRUNING_H
#define PRUNING_H

#include <vector>
#include <algorithm>
#include <iostream>

vector<unsigned int> prune(vector< vector<unsigned int> > antennas, unsigned int heuristic){
	vector<unsigned int> output;
	for(unsigned int i = 0; i < antennas.size(); i++){
		sort(antennas[i].begin(), antennas[i].end());
	}
	//create 3d vector where it is same as 2d vector antennas but is seperated into groups of 10.
	vector< vector< vector<unsigned int> > >clusters();

	//adding the groups of 10 to clusters
	for(unsigned int i = 0; i < antennas.size(); i = i + 10){
		vector< vector<unsigned int> > holding_vector;
		clusters.push_back(holding_vector);
		for(unsigned int j = i; j < antennas.size() && j < i + 10; j++){
			clusters[i].push_back(antennas[j]);
		}
	}

	//holds all greedy solutions to each cluster of 10 antennas
	vector< vector<unsigned int> > broken_clusters();

	//Greedy solution for each group of 10
	for(unsigned int i = 0; i < clusters.size(); i++){
		vector<unsigned int> best_estimate_base_stations();
		for(unsigned int j = 0; j < clusters[i].size(); j++){

			vector<unsigned int> estimate_base_stations();
			vector<bool> valid_sets (clusters[i].size(), true);

			for(unsigned int k = 0; k < clusters[i][j].size(); k++){
				estimate_base_stations.push_back(clusters[i][j][k]);
			}

			sort(estimate_base_stations.begin(), estimate_base_stations.end());
			
			unsigned int set_diff = 0;
			unsigned int best_diff = 0;
			int index_to_add = -1;
			
			while(find(valid_sets.begin(), valid_sets.end(), true) != valid_sets.end()){
				best_diff = estimate_base_stations.size();
				for(unsigned int m = 0; m < clusters[i].size(); m++){
					if(!valid_sets[m]){
						continue;
					}
					vector<unsigned int> v(estimate_base_stations.size() + clusters[i][m].size());
					vector<unsigned int>::iterator it;
					it = set_symmetric_difference(estimate_base_stations.begin(),
							estimate_base_stations.end(),
							clusters[i][m].begin(),
							clusters[i][m].end(), v.begin();
					set_diff = (it - v.begin());
					if(set_diff <= estimate_base_stations.size()){
						valid_sets[m] = false;
					}
					else if(set_diff > best_diff){
						best_diff = set_diff;
						index_to_add = m;
					}
				}
				if(index_to_add != -1){
					for(unsigned int m = 0; m < clusters[i][index_to_add].size(); m++){
						estimate_base_stations.push_back(clusters[i][index_to_add][m]);
					}
					valid_sets[index_to_add] = false;
					index_to_add = -1;
				}
				sort(estimate_base_stations.begin(), estimate_base_stations.end());
			}
			auto temp = get_rid_of_dups(estimate_base_stations);
			if(temp.size() > best_estimate_base_stations.size()){
				best_estimate_base_stations = temp;
			}
		}
		broken_clusters.push_back(best_estimate_base_stations);
	}
	return output;	
}
#endif
