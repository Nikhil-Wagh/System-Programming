#include "bits/stdc++.h"
using namespace std;

typedef struct table{
	int index, address, pool;
	string symbol;
}table;

table symtab[50], littab[50];
int litCount = 0;

void init(){
	for(int i = 1 ; i < 50 ; i++){
		cin >> symtab[i].index >> symtab[i].symbol >> symtab[i].address;
		if (symtab[i].index == -1){
			break;
		}
	}
	for(int i = 1 ; i < 50 ; i++){
		cin >> littab[i].index >> littab[i].symbol >> littab[i].address >> littab[i].pool;
		if (littab[i].index == -1){
			break;
		}
		litCount++;
	}
}
int getIndex(string s){
	//cout << "STRING TO INT" << s.substr(0, s.length() - 1) << endl;
	return stoi(s.substr(0, s.length() - 1));
}
int main(){
	freopen("PASS2_INPUT.txt", "r+", stdin);
	init();
	cin.clear();
	freopen("PASS1_OUTPUT.txt","r+",stdin);
	freopen("PASS2_OUTPUT.txt","w",stdout);

	string read_each_line;
	int count = 0;
	while(getline(cin,read_each_line)){
		vector<string> v;
		istringstream iss(read_each_line);
		copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(v));
		for(int i = 0 ; i < v.size() ; i++){
			if (v[i].find("AD") != string::npos)
			{
				if(v.size() > 3 && v[i + 2].find("C") != string::npos){
					count = getIndex(v[i + 3]);
				}
				break;
			}
			if(isdigit(v[i][0])){
				int address = stoi(v[i]);
				while(count < address){
					cout << count++ << endl;
				}
				if(v[i + 1].find("DL") != string::npos){
					cout << count << " " << setfill('0') << setw(2) << v[i + 2].substr(0, v[i + 2].size() - 1) << endl;
					if(isdigit(v[i + 4][0]))
						count += getIndex(v[i + 4]);
					else
						count++;
				}
				else if (v[i + 1].find("IS") != string::npos){
					cout << count++ << " " << setfill('0') << setw(2) << v[i + 2].substr(0, v[i + 2].size() - 1) << " " << v[i + 3];
					int address;
					if (v[i + 4].find("L") != string::npos){
						int in = getIndex(v[i + 5]);
						address = littab[in].address ;
					}
					else if(v[i + 4].find("S") != string::npos){
						int in = getIndex(v[i + 5]);
						address = symtab[in].address;
					}
					cout << " " << address << endl;
				}
				break;
			}
		}
	}
	int lastAdd = littab[litCount].address;
	while(count <= lastAdd){
		cout << count++ << endl;
	}
	cin.clear();
	cout.clear();
}