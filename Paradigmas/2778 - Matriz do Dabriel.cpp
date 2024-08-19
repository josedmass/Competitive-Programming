/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2778
    Título              :  Matriz do Dabriel / Dabriel's Matrix
    Categoria           :  Paradigmas
    Última Modificação  :  29/04/24
*/

#include <bits/stdc++.h>

using namespace std;

int N, M, X, Y;
int it = 1;
int memo[100][100][21][21][2];
int matriz[100][100], visited[100][100][21][21][2];

// memo[i][j][x][y][z] = menor caminho a partir da posição (i, j) até (N, M) podendo passar por X valores nulos,
// Y valores negativos e sob a restrição z;

// z=0, se você vai pra esquerda, z=1, se você vai pra direita

int solve(int i, int j, int x, int y, int z) {

    if(i < 0 || j < 0 || i >= N || j >= M || x < 0 || y < 0) return INT_MAX/2;
    if(i == N-1 && j == M-1) return matriz[i][j];
    if(visited[i][j][x][y][z] == it) return memo[i][j][x][y][z];

    visited[i][j][x][y][z] = it;

    int newx = x, newy = y;
    if(matriz[i][j] == 0) newx--;
    else if(matriz[i][j] < 0) newy--;

    int ans = INT_MAX/2;
    ans = min(ans, solve(i+1, j, newx, newy, 0));
    ans = min(ans, solve(i+1, j, newx, newy, 1));

    if(z == 1) { // só pode ir pra esquerda
        ans = min(ans, solve(i, j-1, newx, newy, 1));
    }
    else if(z == 0) { // só pode ir pra direita
        ans = min(ans, solve(i, j+1, newx, newy, 0));
    }

    if(ans == INT_MAX/2) 
        memo[i][j][x][y][z] = ans;
    else 
        memo[i][j][x][y][z] = matriz[i][j] + ans;

    return memo[i][j][x][y][z];

}


int main() {

    while(cin >> N >> M >> X >> Y) {

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                cin >> matriz[i][j];
            }
        }

        it++;
        int res = solve(0, 0, X, Y, 0);
        if(res == INT_MAX/2) cout << "Impossivel" << endl;
        else cout << res << endl;
    }


    return 0;
}