/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1485
    Título              :  Roleta Turca / Turkish Roulette
    Categoria           :  Paradigmas
    Última Modificação  :  26/04/24
*/

#include <bits/stdc++.h>

using namespace std;

// table[i][j]: melhor arrecadação se a i-ésima bola está na j-ésima posição

int roleta(vector<int>& vals, vector<int>& bols) {
    int S = vals.size(), B = bols.size();
    int ans = INT_MAX;
    for(int i = 0; i < S; i++) {
        vector<vector<int>> table(B, vector<int>(S));
        table[0][0] = INT_MAX;
        for(int j = 1; j < S; j++) table[0][j] = bols[0] * (vals[j-1] + vals[j]);
        for(int j = 1; j < B; j++)
            for(int k = 0; k < 3; k++)
                table[j][k] = INT_MAX;

        for(int j = 1; j < B; j++) {
            int aux = INT_MAX;
            for(int k = 3; k < S; k++) {
                aux = min(aux, table[j-1][k-2]); // mínimo das posições anteriores válidas
                if(aux == INT_MAX) table[j][k] = INT_MAX; // não tem como colocar nessa posição
                else {
                    table[j][k] = aux + bols[j] * (vals[k-1] + vals[k]); // colocando a bola nessa posição válida
                }
            }
        }

        ans = min(ans, table[B-1][S-1]);

        // Mudando a ordem de vals, para testar novos inícios
        int aux1, aux2 = vals[0];
        for(int i = 1; i < S; i++) {
            aux1 = vals[i];
            vals[i] = aux2;
            aux2 = aux1;
        }
        vals[0] = aux2;
    }

    return ans;

}

int main() {

    int S, B;
    while(cin >> S >> B) {
        if(S == 0 && B == 0) break;
        vector<int> vals(S);
        vector<int> bols(B);
        for(int i = 0; i < S; i++) cin >> vals[i];
        for(int i = 0; i < B; i++) cin >> bols[i];

        cout << -roleta(vals, bols) << endl;
    }

    return 0;
}