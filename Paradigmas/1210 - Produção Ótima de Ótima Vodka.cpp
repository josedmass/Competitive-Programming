/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1210
    Título              :  Produção Ótima de Ótima Vodka / Optimal Production of Great Vodka
    Categoria           :  Paradigmas
    Última Modificação  :  04/05/24
*/

#include <bits/stdc++.h>

using namespace std;

// DP[i][j] = menor custo para produção a partir do ano i com destilador de j anos

int DP[2001][2001];
int N, M, L, P;

int main() {

    while(cin >> N >> L >> M >> P) {
        vector<int> C(M), V(M+1);
        for(int i = 0; i < M; i++) cin >> C[i];
        for(int i = 1; i <= M; i++) cin >> V[i];

        // marca o caminho feito
        vector<vector<bool>> mark(N+1, vector<bool>(M+1, false));
        
        // 1. Montar a base da DP
        for(int i = 1; i < M; i++) {
            int troca = P-V[i]+C[0];
            int ntroca = C[i];
            if(troca <= ntroca) {
                mark[N][i] = true;
                DP[N][i] = troca;
            }
            else DP[N][i] = ntroca;
        }

        mark[N][M] = true;
        DP[N][M] = P-V[M]+C[0];

        for(int i = N-1; i > 0; i--) {
            for(int j = 1; j <= M; j++) {
                if(j == M) { //precisa trocar
                    mark[i][j] = true;
                    DP[i][j] = P-V[j]+C[0] + DP[i+1][1];
                }
                else {
                    int troca = DP[i+1][1]+P-V[j]+C[0];
                    int ntroca = DP[i+1][j+1]+C[j];
                    if(troca <= ntroca) {
                        mark[i][j] = true;
                        DP[i][j] = troca;
                    } else DP[i][j] = ntroca;
                }
            }
        }
        cout << DP[1][L] << endl; // valor ótimo
        int j = L, cont = 0;
        for(int i = 1; i <= N; i++) { // reconstrói o caminho
            if(mark[i][j]) {
                cont++;
                if(cont == 1) cout << i;
                else cout << " " << i;
                j = 1;
            }
            else j++;
        }
        if(cont == 0) cout << cont;
        cout << endl;
    }

    return 0;
}