/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2677
    Título              :  Par ou Ímpar / Even or Odd
    Categoria           :  Paradigmas
    Última Modificação  :  24/04/24
*/

#include <bits/stdc++.h>

using namespace std;

int solve(vector<int>& vals) {

    int n = vals.size();

    // dp[j][k] = maior valor que o primeiro jogador consegue fazer com o intervalo [j...k] do vetor 
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i; j++) {
            int k = i + j; // coluna a ser iterada
            if(i == 0) dp[j][k] = 0;
            else if(i % 2 == 0) { // vez do segundo jogador
                dp[j][k] = min(dp[j+1][k], dp[j][k-1]);
            } 
            else if(i % 2 != 0) { // vez do primeiro jogador
                int prim = vals[j] % 2 == 0;
                int ulti = vals[k] % 2 == 0;
                dp[j][k] = max(dp[j+1][k] + prim, dp[j][k-1] + ulti);
            }
        }
    }

    return dp[0][n - 1];

}

int main() {

    int N;
    while(cin >> N) {
        if(N == 0) break;
        vector<int> vals(2*N);
        for(int i = 0; i < 2*N; i++) {
            cin >> vals[i];
        }

        cout << solve(vals) << endl;

    }


}