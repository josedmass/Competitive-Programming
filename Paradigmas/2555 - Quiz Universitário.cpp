/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2555
    Título              :  Quiz Universitário / University Quiz
    Categoria           :  Paradigmas
    Última Modificação  :  28/04/24
*/

#include <bits/stdc++.h>

using namespace std;

// memo[i][k] = valor esperado para responder todas as perguntas a partir da i-ésima, com k pulos

double solve(int i, int k, vector<int>& premio, vector<double>& prob, vector<vector<double>>& memo) {
    if(i == premio.size()) return 0;
    if(memo[i][k] != -1) return memo[i][k];

    double ans = prob[i] * (premio[i] + solve(i+1, k, premio, prob, memo));
    if(k > 0) ans = max(ans, premio[i] + solve(i+1, k-1, premio, prob, memo));

    memo[i][k] = ans;
    return memo[i][k];
}

int main() {

    int N, K;
    while(cin >> N >> K) {
        vector<int> premio(N);
        vector<double> prob(N);
        for(int i = 0; i < N; i++) cin >> premio[i];
        for(int i = 0; i < N; i++) {
            cin >> prob[i];
            prob[i] /= 100.0;
        }

        vector<vector<double>> memo(N, vector<double>(K+1, -1));
        cout << fixed << setprecision(2) << solve(0, K, premio, prob, memo) << endl;

    }

    return 0;
}