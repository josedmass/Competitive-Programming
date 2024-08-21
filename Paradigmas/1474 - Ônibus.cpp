/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1474
    Título              :  Ônibus / Buses
    Categoria           :  Paradigmas
    Última Modificação  :  18/07/24
*/


#include <bits/stdc++.h>

#define MOD 1000000
#define lli unsigned long long int

using namespace std;

// Retorna a multiplicação da matriz A pela matriz B
vector<vector<lli>> multiplica(vector<vector<lli>>& A, vector<vector<lli>>& B) {
    int lA = A.size(), cAlB = A[0].size(), cB = B[0].size();
    vector<vector<lli>> aux(lA, vector<lli>(cB, 0));
    for(int i = 0; i < lA; i++)
        for(int j = 0; j < cB; j++)
            for(int k = 0; k < cAlB; k++) 
                aux[i][j] += (A[i][k]%MOD * B[k][j]%MOD)%MOD;
    
    for(int i = 0; i < lA; i++)
        for(int j = 0; j < cB; j++)
            aux[i][j] = aux[i][j]%MOD;

    return aux;
}

// Retorna A^n em O(lon n)
vector<vector<lli>> potencia(vector<vector<lli>>& A, lli n) {
    if(n == 1) return A;
    vector<vector<lli>> res;
    if(n % 2 == 0) {
        res = potencia(A, n/2);
        res = multiplica(res, res);
    } else {
        res = potencia(A, n/2);
        vector<vector<lli>> aux = multiplica(res, res);
        res = multiplica(aux, A);
    }
    return res;
}

int main() {

    lli N, K, L;
    while(cin >> N >> K >> L) {
        if(N == 5) cout << std::setw(6) << std::setfill('0') << K << endl;
        else {
            /*
                |  F(n)  |  = |K  L|^(n/5)-1 |F(5)|
                | F(n-5) |    |1  0|         |F(0)|
            */
            vector<vector<lli>> res(2, vector<lli>(1, 0));
            vector<vector<lli>> cof = {{K%MOD, L%MOD},  {1, 0}};
            vector<vector<lli>> dir = {{K%MOD}, {1}};
            lli exp = N > 5 ? (N/5)-1 : 1;
            vector<vector<lli>> pot = potencia(cof, exp);
            res = multiplica(pot, dir);
            cout << std::setw(6) << std::setfill('0') << res[0][0] << endl;
        }
    }

    return 0;
}