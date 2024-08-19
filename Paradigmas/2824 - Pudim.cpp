/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2824
    Título              :  Pudim
    Categoria           :  Paradigmas
    Última Modificação  :  09/04/24
*/

#include <bits/stdc++.h>
 
using namespace std;

int LCS(string& s1, string& s2, int m, int n, vector<vector<int>>& memo) {

    if(m == 0 || n == 0) return 0;
    if(s1[m-1] == s2[n-1]) { // casou um símbolo
        memo[m-1][n-1] = LCS(s1, s2, m-1, n-1, memo) + 1;
        return memo[m-1][n-1];
    }
        
    if(memo[m-1][n-1] != -1) return memo[m-1][n-1];
    memo[m-1][n-1] = max(LCS(s1, s2, m-1, n, memo), LCS(s1, s2, m, n-1, memo));
    return memo[m-1][n-1];

}
 
int main() {
 
    string s1, s2;
    cin >> s1 >> s2;

    vector<vector<int>> memo(s1.size()+1, vector<int>(s2.size()+1, -1));
    cout << LCS(s1, s2, s1.size(), s2.size(), memo) << endl;
 
    return 0;
}