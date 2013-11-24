#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>

using namespace std;

void simple_print(vector< vector<unsigned int> > antennas){
	for(unsigned int i = 0; i < antennas.size(); i++){
		cout << "for antenna " << i << " ";
		for(unsigned int k = 0; k < antennas[i].size(); k++){
			cout << antennas[i][k] << " ";
		}
		cout << endl;
	}
}

#endif
