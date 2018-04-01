#include "bits/stdc++.h"
using namespace std;
#define delCount 15

string tokens[100];

void init(){
	for(int i = 0 ; i < delCount ; i++)
		cin >> delimiters[i];
	for(int i = 0 ; i < tokenCount ; i++)
		cin >> tokens[i];
}

bool isDelimiter(char s){
	for(int i = 0 ; i < delCount ; i++){
		if(s == delimiters[i])
			return true;
	}
	return false;
}

int main(int argc, char const *argv[])
{
	freopen("TOKENS.txt","r",stdin);
	init();
	cin.clear();
	freopen("INPUT.txt", "r", stdin);
	freopen("OUTPUT.txt", "w", stdout);
	string line;
  	while(getline(cin, line)){
  		int left = 0, right = 0;
  		int length = line.length();
  		if(line.find("//") != string::npos) 
   			length = line.find("//") - 1;
  		bool inQuotes = false;
  		while(right < length && left <= right){
  			line.erase(remove(line.begin(), line.end(), '\t'), line.end());
  			if((isDelimiter(line[right]) || line[right] == ' ') && inQuotes == false){
  				if(left != right){
  					cout << line.substr(left, right - left) << endl;
  				}
  				if(line[right] != ' ')
  					cout << line[right] << endl;
  				left = right + 1;
  			}
  			else{
  				if(line[right] == '"' && line[right - 1] != '\\'){
  					inQuotes = !inQuotes;
  				}
  			}
  			right++;
  		}
  	}
	return 0;
}