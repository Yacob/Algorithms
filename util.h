#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <set>
#include <sstream>
using namespace std;


vector <vector <unsigned int> > gen_combs(unsigned int n){

        vector< vector<unsigned int> > subset;

        for (unsigned int i = 0; i < n; i++){
                vector< vector<unsigned int> > subsetTemp = subset;

                for (unsigned int j = 0; j < subsetTemp.size(); j++)
                        subsetTemp[j].push_back(i);

                for (unsigned int j = 0; j < subsetTemp.size(); j++)
                        subset.push_back( subsetTemp[j] );
        }
        return subset;
}

void simple_print(vector< vector<unsigned int> > antennas){
	for(unsigned int i = 0; i < antennas.size(); i++){
		cout << "for antenna " << i << " ";
		for(unsigned int k = 0; k < antennas[i].size(); k++){
			cout << antennas[i][k] << " ";
		}
		cout << endl;
	}
}
int evaluate(vector <unsigned int> combination,  
		vector <vector <unsigned int> > full){
	set<int> usedBases;
        set<int> touchedBases;
     	for(auto single : combination){
		auto baseSet = full[single];
		for(unsigned int base : baseSet){
			if(touchedBases.find(base) != touchedBases.end()){
                                if(usedBases.find(base) != usedBases.end())
					usedBases.erase(base);
                        }
                        else{
                                touchedBases.insert(base);
				usedBases.insert(base);
                        }
		}
	}
	return 0;
}

string formatResult(vector <unsigned int> comb, 
			vector <vector <unsigned int> >antennas){ 
	set<int> usedBases;
        set<int> touchedBases;
        stringstream out;
        stringstream bases;
        out << comb.size() << ' ';
        for(auto ant: comb){
                out << ant << ' ';
        }
        out << '\n' << evaluate(comb, antennas);
        return out.str();
}

#endif
