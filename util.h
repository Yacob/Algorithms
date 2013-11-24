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

string formatResult(set<unsigned int> comb){ 
	set usedBases;
        set touchedBases;
        stringsteam out;
        stringsteam bases;
        ss << comb.size() << ' ';
        for(auto ant: comb){
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
        return ss.str();
}

#endif
