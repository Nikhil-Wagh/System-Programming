#include "bits/stdc++.h"
using namespace std;
typedef struct table{
	int address;
	string value;
}table;

table mnt[50], mdt[50], pt[50];

int main(){

	freopen("PASS1_INPUT.txt", "r", stdin);

	int mntc = 0, mdtc = 0, ptc = 0;
	string read_each_line;
	while(getline(cin,read_each_line)){
		vector<string> v;
		istringstream iss(read_each_line);
		copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(v)); 

		if(v[0].find("MACRO") != string::npos){
			vector<string> vi;
			getline(cin,read_each_line);
			istringstream iss(read_each_line);
			copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(vi)); 

			mnt[mntc].value = vi[0];
			mnt[mntc].address = mdtc;
			// mntc++;

			for(int i = 1 ; i < vi.size() ; i++){
				pt[ptc].value = vi[i].substr(0, vi[i].length() - 1);
				pt[ptc].address = mntc;
				ptc++;
			}
			while(true){
				vector<string> vii;
				getline(cin,read_each_line);
				istringstream iss(read_each_line);
				copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(vii)); 

				if (vii[0].find("MEND") != string::npos){
					mntc++;
					break;
				}
				mdt[mdtc++].value = read_each_line;
			}
		}
	}

	cin.clear();
	freopen("PASS1_OUTPUT.txt", "w", stdout);

	cout << "/********* MACRO NAME TABLE *********/" << endl;
	cout << "Index\t" << "Name\t" << "Address\t" << endl;
	for(int i = 0 ; i < mntc ; i++)
		cout << i  << "\t\t" << mnt[i].value << "\t\t" << mnt[i].address << endl;
	cout << endl;

	cout << "/********* MACRO DEFINITION TABLE *********/" << endl;
	cout << "Index\t" << "Instruction" << endl;
	for(int i = 0 ; i < mdtc ; i++)
		cout << i << "\t\t" << mdt[i].value << endl;
	cout << endl;

	cout << "/********* PARAMETER TABLE *********/" << endl;
	cout << "Index\t" << "Address\t" << "Parameter" << endl;
	for(int i = 0 ; i < ptc ; i++)
		cout << i << "\t\t" << pt[i].address << "\t\t" << pt[i].value << endl;
}