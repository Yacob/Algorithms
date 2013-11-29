#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <set>
#include <sstream>
using namespace std;


vector <vector <unsigned int> > gen_combs(unsigned int n){

        vector< vector<unsigned int> > subset;
	vector<unsigned int> empty;
	subset.push_back(empty);
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
		cout << "for antenna " << i << ": ";
		for(unsigned int k = 0; k < antennas[i].size(); k++){
			cout << antennas[i][k] << " ";
		}
		cout << endl;
	}
}

unsigned int evaluate(vector <unsigned int> combination,  
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
	unsigned int value = usedBases.size();
	return value;
}

//Gets rid of all values that have a duplicate.  ALL VALUES, ie doesn't leave all but one.
//[1, 2, 2, 3] -> [1, 3]
vector<unsigned int> get_rid_of_dups(vector<unsigned int> antennas){
	auto first = antennas.begin();
	auto last = antennas.end();
	auto second = antennas.begin();
	vector<unsigned int> vec;
	if(first == last){
		return antennas;
	}
	while(first != last){
		second = first;
		second++;
		if(*first != *second){
			vec.push_back(*first);
			first++;
		}
		else if(*first == *second){
			while(second != last && *first == *second){
				second++;
			}
			if(second == last){
				break;
			}
			first = second;
		}
	}
	return vec;
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
