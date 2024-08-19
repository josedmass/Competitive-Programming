/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2532
    Título              :  Demogorgon
    Categoria           :  Paradigmas
    Última Modificação  :  09/04/24
*/

#include <bits/stdc++.h>

using namespace std;

struct Feitico {
    int dano;
    int mana;
};

int MinMana(int P, int i, vector<Feitico>& feiticos, vector<vector<int>>& memo) {
    if(P < 0) return 0;
    if(i == feiticos.size()) {
        if(P > 0) return INT_MAX/2;
        else return 0;
    }
    if(memo[P][i] != -1) return memo[P][i];
    memo[P][i] = min(MinMana(P-feiticos[i].dano, i+1, feiticos, memo) + feiticos[i].mana, MinMana(P, i+1, feiticos, memo));
    return memo[P][i];
}
 
int main() {
 
    int N, P;
    while(cin >> N >> P) {
        vector<Feitico> feiticos(N);
        for(int i = 0; i < N; i++) {
            cin >> feiticos[i].dano >> feiticos[i].mana;
        }

        vector<vector<int>> memo(P+1, vector<int>(N, -1));

        int ans = MinMana(P, 0, feiticos, memo);
        if(ans >= INT_MAX/2) cout << "-1" << endl;
        else cout << ans << endl;

    }
 
    return 0;
}