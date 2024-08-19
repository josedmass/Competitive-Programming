/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1288
    Título              :  Canhão de Destruição / Destruction Cannon
    Categoria           :  Paradigmas
    Última Modificação  :  21/04/24
*/

#include <bits/stdc++.h>

using namespace std;

struct Projetil {
    int poder;
    int peso;
};

int Atacar(int K, int i, vector<Projetil>& proj, vector<vector<int>>& memo) {
    if(K < 0) return INT_MIN;
    if(i == proj.size()) return 0;
    if(memo[K][i] != -1) return memo[K][i];

    memo[K][i] = max(Atacar(K-proj[i].peso, i+1, proj, memo) + proj[i].poder, Atacar(K, i+1, proj, memo));
    return memo[K][i];
}

int main() {

    int T;
    cin >> T;
    for(int i = 0; i < T; i++) {
        int N;
        cin >> N;
        vector<Projetil> proj(N);
        for(int j = 0; j < N; j++) {
            cin >> proj[j].poder >> proj[j].peso;
        }
        int K, R;
        cin >> K >> R;
        vector<vector<int>> memo(K+1, vector<int>(N, -1));
        int poder = Atacar(K, 0, proj, memo);
        if(poder >= R) cout << "Missao completada com sucesso" << endl;
        else cout << "Falha na missao" << endl;
    }


    return 0;
}