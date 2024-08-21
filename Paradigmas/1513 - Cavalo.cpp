/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1513
    Título              :  Cavalo / Horse
    Categoria           :  Paradigmas
    Última Modificação  :  13/05/24
*/

#include <bits/stdc++.h>

using namespace std;

vector<int> BFS(vector<vector<int>> g, int a) {
    vector<int> d(g.size(), INT_MAX);
    d[a] = 0;
    queue<int> q; q.push(a);
    while(!q.empty()) {
        int v = q.front(); q.pop();
        for(int u : g[v]) {
            if(d[u] == INT_MAX) {
                d[u] = d[v] + 1;
                q.push(u);
            }
        }
    }
    return d;
}

int quant(int k) {
    int res = 0;
    for(int i = k; i >= 0; i--) res += pow(2, i);
    return res;
}

//memo[i][j] = quantidade de movimentos necessarios a partir da posição i para consumir os peões restantes nas posições j
//mask: 0: tem peão; 1: não tem peão
int solve(int pos, int mask, vector<vector<int>>& dist, vector<vector<int>>& memo) {
    if(memo[pos][mask] != -1) return memo[pos][mask];
    int K = dist.size();
    if(mask == ((1 << K)-1)) return dist[0][pos]; //não tem mais peões para avaliar
    int res = INT_MAX;
    for(int i = 0; i < K; i++) {
        if(i != pos && !(mask & (1 << i))) { //não é a mesma posição e tem peão ali
            int newmask = (mask | (1 << i));
            res = min(res, solve(i, newmask, dist, memo)+dist[pos][i]);
        }
    }
    memo[pos][mask] = res;
    return memo[pos][mask];
}

int main() {

    int N, M, K;
    while(cin >> N >> M >> K && (N || M || K)) {
        vector<vector<int>> tab(N, vector<int>(M)); //posições do tabuleiro
        vector<vector<int>> aux(N, vector<int>(M)); //nros das posições
        vector<int> posK; //guarda as posições dos cavalos

        int it = 0;
        int inicio;
        for(int i = 0; i < N; i++) {
            string line;
            cin >> line;
            for(int j = 0; j < M; j++) {
                aux[i][j] = it;
                it++;
                if(line[j] == '#') tab[i][j] = 0; //invalido
                else if(line[j] == '.') tab[i][j] = 1; //valido
                else if(line[j] == 'P') { //peao
                    tab[i][j] = 2;
                    //cout << "||" << aux[i][j] << "||" << endl;
                    posK.push_back(aux[i][j]);
                }
                else if(line[j] == 'C') {tab[i][j] = 3; inicio = aux[i][j];} //cavalo
            }
        }

        it = 0;
        vector<vector<int>> grafo(N*M); //movimentos possíveis para cada posição
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(i-1 >= 0 && j-2 >= 0 && tab[i-1][j-2] != 0) grafo[it].push_back(aux[i-1][j-2]);
                if(i+1 < N && j-2 >= 0 && tab[i+1][j-2] != 0) grafo[it].push_back(aux[i+1][j-2]);
                if(i-2 >= 0 && j-1 >= 0 && tab[i-2][j-1] != 0) grafo[it].push_back(aux[i-2][j-1]);
                if(i+2 < N && j-1 >= 0 && tab[i+2][j-1] != 0) grafo[it].push_back(aux[i+2][j-1]);
                if(i-2 >= 0 && j+1 < M && tab[i-2][j+1] != 0) grafo[it].push_back(aux[i-2][j+1]);
                if(i+2 < N && j+1 < M && tab[i+2][j+1] != 0) grafo[it].push_back(aux[i+2][j+1]);
                if(i-1 >= 0 && j+2 < M && tab[i-1][j+2] != 0) grafo[it].push_back(aux[i-1][j+2]);
                if(i+1 < N && j+2 < M && tab[i+1][j+2] != 0) grafo[it].push_back(aux[i+1][j+2]);
                it++;
            }
        }

        vector<vector<int>> dist(K+1, vector<int>(K+1, 0)); //distância de cada ponto importante para cada outro
        it = 1;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                int pos = aux[i][j];
                if(tab[i][j] == 3) { //cavalo
                    vector<int> aux = BFS(grafo, pos);
                    for(int l = 1; l <= K; l++)
                        dist[0][l] = aux[posK[l-1]];
                }
                else if(tab[i][j] == 2) { //peão
                    vector<int> aux = BFS(grafo, pos);
                    dist[it][0] = aux[inicio];
                    for(int l = 1; l <= K; l++)
                        dist[it][l] = aux[posK[l-1]];
                    it++;
                }
            }
        }

        int nro = quant(K);
        vector<vector<int>> memo(K+1, vector<int>(nro+1, -1));
        cout << solve(0, 1, dist, memo) << endl; //a partir do início, só a posição 0 não tem peão

    }

    return 0;
}