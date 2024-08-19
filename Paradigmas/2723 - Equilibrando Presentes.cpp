/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2723
    Título              :  Equilibrando Presentes / Balancing Gifts
    Categoria           :  Paradigmas
    Última Modificação  :  24/04/24
*/

#include <bits/stdc++.h>

using namespace std;

// memo[p1][p2][i] = 1, se é possível equilibrar os presentes se a condição inicial do lado A é p1, do B é p2, 
// e estamos avaliando o vetor a partir do ponto i

int solve(int p1, int p2, int i, vector<int>& pesos, vector<vector<vector<int>>>& memo) {

    if(pesos.size() == 0) return 1;
    if(i == pesos.size() || abs(p1-p2) > 5) return 0;
    if(i == pesos.size()-1 && abs(p1-p2) > 5) return 0;
    if(i == pesos.size()-1 && (abs(p1+pesos[i]-p2) <= 5 || abs(p1 - pesos[i] - p2) <= 5)) return 1;

    if(memo[p1][p2][i] != -1) return memo[p1][p2][i];

    int newdifA = abs(p1 + pesos[i] - p2);
    int newdifB = abs(p2 + pesos[i] - p1);

    if(newdifA > 5 && newdifB > 5) return 0;

    int newP1 = p1 + pesos[i], newP2 = p2 + pesos[i];

    // caso 1: vc pôe no lado A
    int sub1 = min(newP1, p2);
    newP1 -= sub1;

    // caso 2: vc põe no lado B
    int sub2 = min(newP2, p1);
    newP2 -= sub2;

    memo[p1][p2][i] = max(solve(newP1, p2-sub1, i+1, pesos, memo), solve(p1-sub2, newP2, i+1, pesos, memo));
    return memo[p1][p2][i];

}

int main() {

    int T;
    cin >> T;
    for(int i = 0; i < T; i++) {
        int N;
        cin >> N;
        vector<int> pesos(N);
        for(int j = 0; j < N; j++) {
            cin >> pesos[j];
        }

        vector<vector<vector<int>>> memo(20, vector<vector<int>>(20, vector<int>(N, -1)));
        if(solve(0, 0, 0, pesos, memo) == 1) cout << "Feliz Natal!" << endl;
        else cout << "Ho Ho Ho!" << endl;

    }

    return 0;
}