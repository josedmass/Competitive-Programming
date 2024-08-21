/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1644
    Título              :  Decifre o Texto / Decode the Strings
    Categoria           :  Matemática
    Última Modificação  :  20/07/24
*/

#include <bits/stdc++.h>

using namespace std;

// Retorna A x B
vector<vector<int>> multiplica(vector<vector<int>>& A, vector<vector<int>>& B) {
    int lA = A.size(), cAlB = A[0].size(), cB = B[0].size();
    vector<vector<int>> aux(lA, vector<int>(cB, 0));
    for(int i = 0; i < lA; i++)
        for(int j = 0; j < cB; j++)
            for(int k = 0; k < cAlB; k++) 
                aux[i][j] += (A[i][k] * B[k][j]);
    
    for(int i = 0; i < lA; i++)
        for(int j = 0; j < cB; j++)
            aux[i][j] = aux[i][j];

    return aux;
}

// Retorna A^n
vector<vector<int>> potencia(vector<vector<int>>& A, int n) {
    if(n == 1 || n == 0) return A;
    vector<vector<int>> res;
    if(n % 2 == 0) {
        res = potencia(A, n/2);
        res = multiplica(res, res);
    } else {
        res = potencia(A, n/2);
        vector<vector<int>> aux = multiplica(res, res);
        res = multiplica(aux, A);
    }
    return res;
}

// Dada uma coluna de M, acha a linha lin tal que M[lin][col] = 1
int acha1(vector<vector<int>> M, int col) {
    int i = 0;
    for(i = 0; i < M.size(); i++) {
        if(M[i][col] == 1) break;
    }
    return i;
}

int main() {

    int n, m;
    while(cin >> n >> m && (n || m)) {
        vector<int> vals(n);
        for(int i = 0; i < n; i++) cin >> vals[i];
        string texto;
        cin.ignore();
        getline(cin, texto);

        vector<vector<int>> perm(n, vector<int>(n, 0)); // Matriz de permutações
        for(int i = 0; i < n; i++) {
            perm[vals[i]-1][i] = 1;
        }
        perm = potencia(perm, m); // perm^m
        string res =  texto;
        for(int i = 0; i < n; i++) {
            res[acha1(perm, i)] = texto[i];
        }
        cout << res << endl;
    } 

    return 0;
}