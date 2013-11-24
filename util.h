#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <set>
#include <sstream>
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

string formatResult(set<unsigned int> comb, 
			vector <vector <unsigned int> >antennas){ 
	set<int> usedBases;
        set<int> touchedBases;
        stringstream out;
        stringstream bases;
        out << comb.size() << ' ';
        for(auto ant: comb){
                out << ant << ' ';
                auto baseSet = antennas[ant];
                for(auto base : baseSet){
                        if(touchedBases.find(base) != touchedBases.end()){
                                usedBases.insert(base);
                        }
                        else if (usedBases.find(base) != usedBases.end()){
                                usedBases.erase(base);
                        }
                }
        }
        out << '\n' << usedBases.size();
        return out.str();
}

#endif
