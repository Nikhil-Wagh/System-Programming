#include "bits/stdc++.h"
using namespace std;
struct table{
  string value;
  string type;
  int ind;
  int address;
  int pool;
};

struct table optab[18], reg[5], compare[7], littab[50], symtab[50];
int ind, symCount = 1, litCount = 1, lineNum = 1, current_pool = 1;

void initTables(){
  for (size_t i = 1; i <= 17; i++) {
    cin >> optab[i].value >> optab[i].ind >> optab[i].type;
  }
  for (size_t i = 1; i <= 4; i++) {
    cin >> reg[i].value >> reg[i].ind;
  }
  for (size_t i = 1; i <= 7; i++) {
    cin >> compare[i].value >> compare[i].ind;
  }
}

bool isAD(std::vector<string> v){
  for (size_t i = 0; i < v.size(); i++) {
    string s = v[i];
    if(s == "START" || s == "END" || s == "EQU" || s == "ORIGIN" || s == "LTORG")
      return true;
  }
  return false;
}

void filterWords(std::vector<string> words){
  for (size_t i = 0; i < words.size(); i++) {
    if (words[i] == ",") {
      words.erase(words.begin() + i);
      return;
    }
  }
}

int inOpTable(string s){
  for (size_t i = 1; i <= 17; i++) {
    if (optab[i].value == s) {
      return i;
    }
  }
  return 0;
}

int isSymbol(string s){
  for (size_t i = 1; i < symCount; i++) {
    if (symtab[i].value == s) {
      return i;
    }
  }
  return 0;
}

int isReg(string s){
  for (size_t i = 1; i <= 4; i++) {
    if (reg[i].value == s) {
      return i;
    }
  }
  return 0;
}

int isComparitive(string s){
  for (size_t i = 1; i <= 7; i++) {
    if (compare[i].value == s) {
      return i;
    }
  }
  return 0;
}

int isLiteral(string s, int cpool){
  for (size_t i = 1; i < litCount; i++) {
    if (littab[i].value == s && littab[i].pool == cpool) {
      return i;
    }
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  freopen("MOT_IN.txt","r",stdin);
  initTables();
  cin.clear();

  freopen("SOURCE_CODE.txt", "r", stdin);
  freopen("PASS1_OUTPUT.txt", "w", stdout);

  string line;
  while(getline(cin, line)){
    istringstream iss(line);
    std::vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};
    if (!isAD(words)) {
      cout << ++lineNum << " ";
    }
    for (size_t i = 0; i < words.size(); i++) {
      if(words[i] != ","){
        if((ind = inOpTable(words[i]))){
          cout << "(" << optab[ind].type << ", " << optab[ind].ind << ")";
        }
        else if((ind = isReg(words[i]))){
          cout << " " << reg[ind].ind << " ";
        }
        else if((ind = isComparitive(words[i]))){
          cout << compare[ind].ind << " ";
        }
        else if(!(ind = isSymbol(words[i])) && isalpha(words[i][0]) && (i == 0 || i == words.size()-1)){
          symtab[symCount].ind = symCount;
          symtab[symCount].value = words[i];
          if(i == 0){
            symtab[symCount].address = lineNum;
          }
          else{
            symtab[symCount].address = -1;
          }
          symCount++;
        }
        else if(!(ind = isLiteral(words[i], current_pool)) && words[i][0] == '='){
          littab[litCount].ind = litCount;
          littab[litCount].value = words[i];
          littab[litCount].address = -1;
          littab[litCount].pool = current_pool;
          litCount++;
        }
        if((ind = isSymbol(words[i]))){
          if(i == 0){
            symtab[ind].address = lineNum;
          }else{
            cout << "(S, " << symtab[ind].ind << ")";
          }
        }
        if((ind = isLiteral(words[i], current_pool))){
          cout << "(L, " << littab[ind].ind << ")";
        }
        if(i > 0 && words[i - 1] == "START" && isdigit(words[i][0])){
          cout << "(C, " << words[i] << ")";
          lineNum = stoi(words[i]) - 1;
        }
        if (words[i] == "LTORG" || words[i] == "END") {
          for (int j = 0; j < litCount; j++) {
            if(littab[j].address == -1){
              littab[j].address = ++lineNum;
            }
          }
          current_pool++;
        }
        if(i > 0 && words[i - 1] == "DC" && isdigit(words[i][1])){
          cout << "(C, " << words[i] << ")";
        }
        if(i > 0 && words[i - 1] == "DS" && isdigit(words[i][0])){
          cout << "(C, " << words[i] << ")";
          lineNum += (words[i][0] - '0') - 1;
        }
        if(words[i] == "EQU"){
          int left, right;
          left = isSymbol(words[i - 1]);
          right = isSymbol(words[i + 1]);
          if(left && right){
            symtab[left].address = symtab[right].address;
          }
        }
      }
    }
    cout << endl;
  }
  //cout<<"Symcount "<<symCount<<endl;
  cout.clear();
  freopen("TABLE_OUTPUT.txt", "w", stdout);
  cout << "Symbol Table" << endl;
  cout << "Index\tSymbol\tAddress" << endl;
  for (size_t i = 1; i < symCount; i++) {
    cout << symtab[i].ind << "\t\t" << symtab[i].value << "\t\t" << symtab[i].address << endl;
  }
  cout << endl << endl;

  cout << "Literal Table" << endl;
  cout << "Index\tSymbol\tAddress\tPool" << endl;
  for (size_t i = 1; i < litCount; i++) {
    cout << littab[i].ind << "\t\t" << littab[i].value << "\t" << littab[i].address << "\t\t" << littab[i].pool << endl;
  }

  cin.clear();
	cout.clear();

  freopen("PASS2_INPUT.txt","w",stdout);
  for (size_t i = 1; i < symCount; i++) {
    cout << symtab[i].ind << " " << symtab[i].value << " " << symtab[i].address << endl;
  }
  cout<<"-1 NULL -1"<<endl;

  for (size_t i = 0; i < litCount; i++) {
    cout << littab[i].ind << " " << littab[i].value << " " << littab[i].address << " " << littab[i].pool << endl;
  }
  cout<<"-1 NULL -1 -1"<<endl;
  cout.clear();
}
