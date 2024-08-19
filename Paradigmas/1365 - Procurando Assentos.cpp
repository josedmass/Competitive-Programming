/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1365
    Título              :  Procurando Assentos / Finding Seats
    Categoria           :  Paradigmas
    Última Modificação  :  25/04/24
*/

#include <bits/stdc++.h>

using namespace std;

int vagos(int iL, int fL, int iC, int fC, vector<vector<int>>& quant) {

    return quant[fL][fC] - quant[fL][iC-1] - quant[iL-1][fC] + quant[iL-1][iC-1];

}

int main() {

    int R, C, K;
    while(cin >> R >> C >> K) {
        if(R == 0 && C == 0 && K == 0) break;
        vector<vector<bool>> assentos(R+1, vector<bool>(C+1, false));
        vector<vector<int>> quant(R+1, vector<int>(C+1, 0));
        for(int i = 1; i <= R; i++) {
            string fila;
            cin >> fila;
            for(int j = 1; j <= C; j++) {
                if(fila[j-1] == '.') assentos[i][j] = true;
                quant[i][j] = assentos[i][j] + quant[i-1][j] + quant[i][j-1] - quant[i-1][j-1];
            }
        }

        int res = INT_MAX;

        for(int i = 1; i <= R; i++) {
            for(int j = 1; j <= C; j++) {
                if(quant[i][j] < K) continue;
                int k = 1;
                for(int l = 1; l <= j; l++) { // testa todos os subretângulos -> 
                    while(vagos(k, i, l, j, quant) >= K && k < i) k++;
                    while(vagos(k, i, l, j, quant) < K && k > 1) k--;
                    if(vagos(k, i, l, j, quant) >= K) res = min(res, (i-k+1)*(j-l+1));
                }
            }
        }

        cout << res << endl;

    }


    return 0;
}