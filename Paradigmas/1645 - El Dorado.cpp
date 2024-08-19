/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1645
    Título              :  El Dorado
    Categoria           :  Paradigmas
    Última Modificação  :  21/04/24
*/

#include <bits/stdc++.h>

#define lli unsigned long long int

using namespace std;

// dp[i][j] = número de subsequências de tamanho i que terminam com o elemento vals[j] 

lli nroLIS(vector<int>& vals, int k) {
    vector<vector<lli>> dp(k+1, vector<lli>(vals.size(), 0));
    for(int i = 0; i < vals.size(); i++) dp[1][i] = 1;
    
    for(int i = 2; i <= k; i++) {
        for(int j = i-1; j < vals.size(); j++) {
            for(int m = 0; m < j; m++) {
                if(vals[m] < vals[j]) { 
                    /*
                        o número de subsequências de tamanho i que terminam em vals[j] é acrescido do
                        número de subsequências de tamanho i-1 que terminam em vals[m], já que vals[m]
                        é MENOR que vals[j] -> um contem o outro
                    */
                    dp[i][j] += dp[i-1][m];
                }
            }
        }
    }

    // Agora basta encontrar o valor total
    lli ans = 0;
    for(int i = 0; i < vals.size(); i++) ans += dp[k][i];

    return ans;

}

int main() {

    int n, k;
    while(cin >> n >> k) {
        if(n == 0 && k == 0) break;
        vector<int> vals(n);
        for(int j = 0; j < n; j++) cin >> vals[j];
        cout << nroLIS(vals, k) << endl;
    }


    return 0;
}