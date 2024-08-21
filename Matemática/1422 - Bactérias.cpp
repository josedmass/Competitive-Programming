/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1422
    Título              :  Bactérias / Bacteria
    Categoria           :  Matemática
    Última Modificação  :  21/07/24
*/

#include <bits/stdc++.h>

#define MOD 13371337
#define lli unsigned long long

#include <bits/stdc++.h>

#define MOD 13371337
#define lli unsigned long long

using namespace std;

void constroi(vector<vector<lli>>& M) {
    M[0][0] = 1; M[0][1] = 1; M[0][2] = 1; M[0][3] = 1;
    M[1][0] = 1; M[1][1] = 0; M[1][2] = 0; M[1][3] = 0;
    M[2][0] = 0; M[2][1] = 1; M[2][2] = 0; M[2][3] = 0;
    M[3][0] = 0; M[3][1] = 0; M[3][2] = 1; M[3][3] = 0;
}

// Retorna a multiplicação da matriz A pela matriz B
vector<vector<lli>> multiplica(vector<vector<lli>>& A, vector<vector<lli>>& B) {
    int lA = A.size(), cAlB = A[0].size(), cB = B[0].size();
    vector<vector<lli>> aux(lA, vector<lli>(cB, 0));
    for(int i = 0; i < lA; i++)
        for(int j = 0; j < cB; j++)
            for(int k = 0; k < cAlB; k++) 
                aux[i][j] = aux[i][j]%MOD + (((A[i][k]%MOD)*(B[k][j]%MOD))%MOD);
    
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

    lli n;
    while(cin >> n && n) {
        vector<lli> vals(4);
        for(int i = 0; i < 4; i++) cin >> vals[i];
        vector<vector<lli>> M(4, vector<lli>(4)); constroi(M);
        vector<vector<lli>> dir = {{vals[3]}, {vals[2]}, {vals[1]}, {vals[0]}};
        M = potencia(M, n-3);
        dir = multiplica(M, dir);
        cout << dir[0][0] << endl;
    }

    return 0;
}