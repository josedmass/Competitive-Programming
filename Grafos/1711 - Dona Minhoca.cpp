/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1711
    Título              :  Dona Minhoca / Miss Worm
    Categoria           :  Grafos
    Última Modificação  :  03/04/24
*/

#include <iostream>
#include <climits>
#include <vector>
#include <set>

#define INF INT_MAX/2

using namespace std;

struct Aresta {
    int v; // vértice
    int p; // peso
};

void DFS(int v, int pai, int& t, vector<vector<Aresta>>& la, vector<int>& ciclos) {
    ciclos[v] = t++;
    for(int i = 0; i < la[v].size(); i++) {
        int u = la[v][i].v;
        if(ciclos[u] == -1) {
            DFS(u, v, t, la, ciclos);
            ciclos[v] = min(ciclos[v], ciclos[u]); // Garantir mesmo representante de ciclo
        }
        else if(u != pai && ciclos[v] > ciclos[u]) ciclos[v] = ciclos[u]; // Achou ciclo >= 3
    }
}

vector<int> Dijkstra(int a, int M, vector<vector<Aresta>>& la, vector<int>& tamanho, vector<int>& ciclos) {
    vector<int> D(la.size(), INF);
    D[a] = 0;
    set<pair<int, int>> Q; // custo x vertice
    Q.insert({0, a});
    while(!Q.empty()) {
        int v = Q.begin()->second;
        int w = Q.begin()->first;
        Q.erase(Q.begin());
        for(int i = 0; i < la[v].size(); i++) {
            int u = la[v][i].v;
            int p = la[v][i].p;
            if(D[u] > D[v] + p) {
                Q.erase({D[u], u});
                D[u] = D[v] + p;
                Q.insert({D[u], u});
            }
        }
    }

    return D;
}

int main() {
 
    int S, T;
    while(cin >> S >> T) {
        vector<vector<Aresta>> la(S);
        for(int i = 0; i < T; i++) {
            int A, B, C;
            cin >> A >> B >> C;
            la[A-1].push_back({B-1, C});
            la[B-1].push_back({A-1, C});
        }

        vector<int> ciclos(S, -1);
        int t = 0;
        DFS(0, -1, t, la, ciclos);

        vector<int> tamanho(S, 0);
        int maior = -1;

        for(int i = 0; i < S; i++) {
            for(int j = 0; j < la[i].size(); j++) {
                int u = la[i][j].v;
                int w = la[i][j].p;
                if(ciclos[i] == ciclos[u]) tamanho[ciclos[i]] += w; // mesmo representante do ciclo : somar peso
            }
            maior = max(maior, tamanho[ciclos[i]]/2); // divide por 2 pois guardamos 2x
        }

        for(int i = 0; i < S; i++) tamanho[i] /= 2;

        int Q;
        cin >> Q;
        for(int i = 0; i < Q; i++) {
            int X, M;
            cin >> X >> M;
            vector<int> caminho = Dijkstra(X-1, M, la, tamanho, ciclos);
            if(M > maior) cout << "-1" << endl;
            else {
                int menor = INF;
                for(int j = 0; j < S; j++) {
                    if(M <= tamanho[ciclos[j]]) // Minhoca consegue dar a volta no ciclo
                        menor = min(menor, caminho[j] + tamanho[ciclos[j]] + caminho[j]); // início até ciclo + comprimento do ciclo + volta pro início
                }
                cout << menor << endl;
            }
        }
    }
 
    return 0;
}