#ifndef CLUSTER_H
#define CLUSTER_H

#include <deque>
#include <vector>
#include <algorithm>
#include <iostream>

vector<unsigned int> cluster(vector< vector<unsigned int> > antennas){
	const unsigned int CLUSTER_SIZE = 6;
	for(unsigned int i = 0; i < antennas.size(); i++){
		sort(antennas[i].begin(), antennas[i].end());
	}
	//create 3d vector where it is same as 2d vector antennas but is seperated into groups of 10.
	vector< vector< vector<unsigned int> > >clusters;
	//create vector to hold antennas
	deque < vector<unsigned int> > final_antennas;

	//adding the groups of 10 to clusters
	for(unsigned int i = 0; i < antennas.size(); i = i + CLUSTER_SIZE){
		vector< vector<unsigned int> > holding_vector;
		clusters.push_back(holding_vector);
		for(unsigned int j = i; j < antennas.size() && j < i + CLUSTER_SIZE; j++){
			clusters[i / CLUSTER_SIZE].push_back(antennas[j]);
		}
	}

	//holds all greedy solutions to each cluster of 10 antennas
	deque < vector<unsigned int> > broken_clusters;
	
	
	
	for(unsigned int i = 0; i < clusters.size(); i++){
		auto vec = bruteForce(clusters[i]);
		vector<unsigned int> bruteRes;        
		for(int j = 0; j < vec.size(); j++){
			bruteRes.push_back(i*CLUSTER_SIZE + vec[j]);
		}
		vector<unsigned int> bases;
		for(auto ant : bruteRes){
			vector<unsigned int> hold;
			hold.resize(bases.size() + antennas[ant].size());
			auto it = set_symmetric_difference(antennas[ant].begin(), antennas[ant].end(), 
					bases.begin(), bases.end(), hold.begin());
			bases.assign(hold.begin(), it);
		}
		broken_clusters.push_back(bases);
		final_antennas.push_back(bruteRes);
	}
	
	
	//greedy solution for each group of 10
	
	/*

	for(unsigned int i = 0; i < clusters.size(); i++){
		vector<unsigned int> best_estimate_base_stations;
		vector<unsigned int> best_estimate_antennas;
		for(unsigned int j = 0; j < clusters[i].size(); j++){

			vector<unsigned int> estimate_base_stations;
			vector<unsigned int> estimate_antennas;
			vector<bool> valid_sets (clusters[i].size(), true);

			for(unsigned int k = 0; k < clusters[i][j].size(); k++){
				estimate_base_stations.push_back(clusters[i][j][k]);
			}
			estimate_antennas.push_back(j);

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
							clusters[i][m].end(), v.begin());
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
					estimate_antennas.push_back(index_to_add + i * CLUSTER_SIZE);
					valid_sets[index_to_add] = false;
					index_to_add = -1;
				}
				sort(estimate_base_stations.begin(), estimate_base_stations.end());
			}
			auto temp = get_rid_of_dups(estimate_base_stations);
			if(temp.size() > best_estimate_base_stations.size()){
				best_estimate_base_stations = estimate_base_stations;
				best_estimate_antennas = estimate_antennas;
			}
		}
		broken_clusters.push_back(best_estimate_base_stations);
		final_antennas.push_back(best_estimate_antennas);
	}
	
	*/

	for(auto vec : broken_clusters){
		sort(vec.begin(), vec.end());
	}

	while(broken_clusters.size() > 1 && final_antennas.size() > 1){
		vector<unsigned int> v(broken_clusters[0].size() + broken_clusters[1].size());
		vector<unsigned int>::iterator it;
		it = set_symmetric_difference(broken_clusters[0].begin(), broken_clusters[0].end(),
				broken_clusters[1].begin(), broken_clusters[1].end(),
				v.begin());
		unsigned int cluster_diff = (it - v.begin());
		if(cluster_diff > broken_clusters[0].size() && cluster_diff > broken_clusters[1].size()){
			
			vector<unsigned int>::iterator it;
			
			vector<unsigned int> base(broken_clusters[0].size() + broken_clusters[1].size());
			it = set_union(broken_clusters[0].begin(), broken_clusters[0].end(), broken_clusters[1].begin(), broken_clusters[1].end(), base.begin());
			base.resize(it - base.begin());

			broken_clusters.push_back(base);
			broken_clusters.pop_front();
			broken_clusters.pop_front();

			vector<unsigned int> ant(final_antennas[0].size() + final_antennas[1].size());
			it = set_union(final_antennas[0].begin(), final_antennas[0].end(), final_antennas[1].begin(), final_antennas[1].end(), ant.begin());
			ant.resize(it - ant.begin());

			final_antennas.push_back(ant);
			final_antennas.pop_front();
			final_antennas.pop_front();
		}
		else if(broken_clusters[0].size() > broken_clusters[1].size()){
			broken_clusters.push_back(broken_clusters[0]);
			broken_clusters.pop_front();
			broken_clusters.pop_front();

			final_antennas.push_back(final_antennas[0]);
			final_antennas.pop_front();
			final_antennas.pop_front();
		}
		else {
			broken_clusters.push_back(broken_clusters[1]);
			broken_clusters.pop_front();
			broken_clusters.pop_front();

			final_antennas.push_back(final_antennas[1]);
			final_antennas.pop_front();
			final_antennas.pop_front();
			
		}
	}

	return final_antennas[0];	
}
#endif
