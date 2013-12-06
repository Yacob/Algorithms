#ifndef CLUSTER_H
#define CLUSTER_H

#include <deque>
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>


//merges clusters up
vector<unsigned int> merge_up(pair<deque< vector<unsigned int> >, deque< vector< unsigned int> > > base_and_antennas){
	auto broken_clusters = base_and_antennas.first;
	auto final_antennas = base_and_antennas.second;

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
			
			vector<unsigned int> bases(broken_clusters[0].size() + broken_clusters[1].size());
			it = set_union(broken_clusters[0].begin(), broken_clusters[0].end(), broken_clusters[1].begin(), broken_clusters[1].end(), bases.begin());
			bases.resize(it - bases.begin());

			broken_clusters.push_back(bases);
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


//Create Cluster
vector< vector< vector<unsigned int> > > create_cluster(vector< vector<unsigned int> > antennas, unsigned int cluster_size){
	vector< vector< vector<unsigned int> > > clusters;
	for(unsigned int i = 0; i < antennas.size(); i = i + cluster_size){
		vector< vector<unsigned int> > holding_vector;
		clusters.push_back(holding_vector);
		for(unsigned int j = i; j < antennas.size() && j < i + cluster_size; j++){
			clusters[i / cluster_size].push_back(antennas[j]);
		}
	}
	return clusters;
}

//Brute force solution to each cluster
pair< deque< vector<unsigned int> >, deque< vector<unsigned int> > > brute(vector< vector< vector<unsigned int> > > clusters,
	       	vector< vector<unsigned int> > antennas, unsigned int cluster_size){


	deque< vector<unsigned int> > broken_clusters;
	deque< vector<unsigned int> > final_antennas;

	for(unsigned int i = 0; i < clusters.size(); i++){
		auto vec = bruteForce(clusters[i]);
		vector<unsigned int> bruteRes;        
		for(int j = 0; j < vec.size(); j++){
			bruteRes.push_back(i * cluster_size + vec[j]);
		}
		vector<unsigned int> bases;
		for(auto ant : bruteRes){
			vector<unsigned int> hold(bases.size() + antennas[ant].size());
			auto it = set_symmetric_difference(antennas[ant].begin(), antennas[ant].end(), 
					bases.begin(), bases.end(), hold.begin());
			bases.assign(hold.begin(), it);
		}
		broken_clusters.push_back(bases);
		final_antennas.push_back(bruteRes);
	}
	return make_pair(broken_clusters, final_antennas);
}


//runs greedy algorithm on each cluster
pair< deque< vector<unsigned int> >, deque< vector<unsigned int> > > greedy(vector< vector< vector<unsigned int> > > clusters, unsigned int cluster_size){
	deque < vector<unsigned int> > final_antennas;
	deque < vector<unsigned int> > broken_clusters;

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
					estimate_antennas.push_back(index_to_add + i * cluster_size);
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
	return make_pair(broken_clusters, final_antennas);
}


vector<unsigned int> cluster(vector< vector<unsigned int> > antennas){
	unsigned int BIG_BRUTE_CLUSTER_SIZE = 7;
	unsigned int BRUTE_CLUSTER_SIZE = 6;
	unsigned int SMALL_BRUTE_CLUSTER_SIZE = 5;
	unsigned int GREEDY_CLUSTER_SIZE = 10;
	unsigned int BGREEDY_CLUSTER_SIZE = 15;

	for(unsigned int i = 0; i < antennas.size(); i++){
		sort(antennas[i].begin(), antennas[i].end());
	}

	auto bbrute_cluster = create_cluster(antennas, BIG_BRUTE_CLUSTER_SIZE);
	auto bbrute_bases_and_antennas = brute(bbrute_cluster, antennas, BIG_BRUTE_CLUSTER_SIZE);
	auto bbrute = merge_up(bbrute_bases_and_antennas);


	auto bgreedy_cluster = create_cluster(antennas, BGREEDY_CLUSTER_SIZE);
	auto bgreedy_bases_and_antennas = greedy(bgreedy_cluster, BGREEDY_CLUSTER_SIZE);
	auto bgreedy = merge_up(bgreedy_bases_and_antennas);


	auto sbrute_cluster = create_cluster(antennas, SMALL_BRUTE_CLUSTER_SIZE);
	auto sbrute_bases_and_antennas = brute(sbrute_cluster, antennas, SMALL_BRUTE_CLUSTER_SIZE);
	auto sbrute = merge_up(sbrute_bases_and_antennas);


	auto brute_cluster = create_cluster(antennas, BRUTE_CLUSTER_SIZE);
	auto brute_bases_and_antennas = brute(brute_cluster, antennas, BRUTE_CLUSTER_SIZE);
	auto brute = merge_up(brute_bases_and_antennas);

	
	auto greedy_cluster = create_cluster(antennas, GREEDY_CLUSTER_SIZE);
	auto greedy_bases_and_antennas = greedy(greedy_cluster, GREEDY_CLUSTER_SIZE);
	auto greedy = merge_up(greedy_bases_and_antennas);


	auto bbrute_size = evaluate(bbrute, antennas);
	auto brute_size = evaluate(brute, antennas);
	auto sbrute_size = evaluate(sbrute, antennas);
	auto greedy_size = evaluate(greedy, antennas);
	auto bgreedy_size = evaluate(bgreedy, antennas);

	/*
	cout << "Big brute size of " << bbrute_size << endl;
	cout << "Brute size of " << brute_size << endl;
	cout << "Small brute size of " << sbrute_size << endl;
	cout << "Greedy size of " << greedy_size << endl;
	cout << "Big Greedy size of " << bgreedy_size << endl;
	*/

	
	if(bbrute_size > brute_size && bbrute_size > sbrute_size && bbrute_size > greedy_size && bbrute_size > bgreedy_size){
		return bbrute;
	}
	else if(brute_size > sbrute_size && brute_size > greedy_size && brute_size > bgreedy_size){
		return brute;
	}
	else if(sbrute_size > greedy_size && sbrute_size > bgreedy_size){
		return sbrute;
	}
	else if(greedy_size > bgreedy_size){
		return greedy;
	}
	else {
		return bgreedy;
	}
}



#endif
