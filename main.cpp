#include <vector>
#include <iostream>
#include "string.h"
#include <string>
#include <sstream>
#include <algorithm>
#include "util.h"
#include "brute.h"

using namespace std;

int main(int argc, char *argv[]){
	//argv[1] is algorithm to use
	
	vector< vector<unsigned int> > antennas; 
	unsigned int num_antennas;
	unsigned int num_receivers;
	string antenna_and_receivers;

	cin >> num_antennas >> num_receivers;

	//creating vector of antennas with each antenna having a vector
	//of recievers it covers
	antennas.resize(num_antennas);
	/*for(int i = 0; i < num_antennas; i++){
		getline(cin, antenna_and_receivers);
		istringstream iss(antenna_and_receivers);
		copy(istream_iterator<unsigned int>(iss), 
			istream_iterator<unsigned int>(),
			back_inserter< vector<unsigned int> >(antennas[i]));
	}*/
	unsigned int receiver_count;
	unsigned int base_station;
	for(unsigned int i = 0; i < num_antennas; i++){
		cin >> receiver_count;
		antennas[i].resize(receiver_count);
		for(unsigned int k = 0; k < receiver_count; k++){
			cin >> base_station;
			antennas[i][k] = base_station;
		}
	}
	simple_print(antennas);
	cout << "Doing brute force attempt" << endl;
	string output = bruteForce(antennas);	
	cout << output << endl;
}
