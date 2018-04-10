/*
S -> iB-iB | iA/jB
A -> +iB | +iA
B -> +b | *c | #
*/
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long int ll;
typedef vector<long long int> vi;
string input;
bool B(int & l){
    int t = l;
    if(input[l] == '+'){
        l++;
        if(input[l] == 'b'){
            return true;
        }
    }
    else if(input[l] == '*'){
        l++;
        if(input[l] == 'c'){
            return true;
        }
    }
    l = t - 1;
    return true;
}
bool A(int & l){
    int t = l;
    vi v;
    if(input[l] == '+' && input[l + 1] == 'i'){
        l += 2;
        if(A(l))
            return true;
        if(B(l))
            return true;
        if(input[l] == '#')
            return true;
    }
    return false;
}
bool S(int & l){
    int initL = l;
    if(input[l] == 'i'){
        l++;
        int t = l;
        if(B(l)){
            l++;
            if(input[l] == '-' && input[l + 1] == 'i'){
                l += 2;
                if(B(l)){
                    l++;
                    if(input[l] == '#')
                        return true;
                }
            }
        }
        l = t;
        if(A(l)){
            l++;
            if(input[l] == '/' && input[l + 1] == 'j'){
                l += 2;
                if(B(l)){
                    l++;
                    if(input[l] == '$')
                        return true;
                }
            }
        }
    }
    return false;
}
int main(){
    int n, sum = 0, count = 0, m, flag = 0, ans = 0, k;
    cout << "Enter a String :: " << endl;
    cin >> input; 
    if(S(count))
    {
        cout << "String ACCEPTED" << endl;
    }
    else {
        cout << "String REJECTED" << endl;
    }
    return 0;
}

