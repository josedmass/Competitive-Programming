/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2784
    Título              :  Ilhas / Islands
    Categoria           :  Grafos
    Última Modificação  :  20/03/24
*/

#include <iostream>
#include <climits>
#include <set>
#include <vector>

using namespace std;

struct Aresta {
    int vert;
    int peso;
};

vector<int> Dijkstra(vector<vector<Aresta>> la, int a, int n) {
    vector<int> D(n, INT_MAX);
    D[a] = 0;

    set<pair<int, int>> Q;
    Q.insert({0, a});

    while(!Q.empty()) {
        int v = Q.begin()->second;
        Q.erase(Q.begin());
        for(int i = 0; i < la[v].size(); i++) {
            int u = la[v][i].vert;
            int w = la[v][i].peso;
            if(D[u] > D[v] + w) {
                Q.erase({D[u], u});
                D[u] = D[v] + w;
                Q.insert({D[u], u});
            }
        }
    }

    return D;
}
 
int main() {
 
    int n, m;
    cin >> n >> m;
    vector<vector<Aresta>> la(n, vector<Aresta>());
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        la[u-1].push_back({v-1, w});
        la[v-1].push_back({u-1, w});
    }

    int inicio;
    cin >> inicio;

    vector<int> rede = Dijkstra(la, inicio-1, n);

    int min = INT_MAX;
    int max = INT_MIN;
    for(int i = 0; i < rede.size(); i++) {
        if(rede[i] == INT_MAX || i == inicio-1) continue;
        if(rede[i] < min) min = rede[i];
        if(rede[i] > max) max = rede[i];
    }

    cout << max - min << endl;
 
    return 0;
}