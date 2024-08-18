/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2683
    Título              :  Espaço de Projeto / Design Space
    Categoria           :  Grafos
    Última Modificação  :  24/03/24
*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
 
void make_set(vector<pair<int, int>>& G) {
    for(int i = 0; i < G.size(); i++) {
        G[i].first = i; //pai
        G[i].second = 1; //tamanho
    }
}

int find(std::vector<std::pair<int, int>>& G, int v) {
    if(v != G[v].first) {
        G[v].first = find(G, G[v].first);
    }
    return G[v].first;
}

void union_find(std::vector<std::pair<int, int>>& G, int a, int b) {
    if(G[G[a].first].second < G[G[b].first].second) union_find(G, b, a);
    else {
        a = find(G, a);
        b = find(G, b);
        G[b].first = a;
        G[a].second += G[b].second;
    }
}

int kruskal(vector<pair<int, pair<int, int>>>& grafo, int V) {
    std::vector<std::pair<int, int>> G(V);
    make_set(G);
    int valor = 0;
    sort(grafo.begin(), grafo.end());
    for(auto edge : grafo) {
        int u = edge.second.first - 1;
        int v = edge.second.second - 1;
        int w = edge.first;
        if(find(G, u) != find(G, v)) {
            valor += w;
            union_find(G, u, v);
        }
    }
    return valor;
}

int main() {
 
    int N;
    cin >> N;
    vector<pair<int, pair<int, int>>> grafo;
    vector<pair<int, pair<int, int>>> antigrafo;
    set<int> contador;

    for(int i = 0; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        contador.insert(u);
        contador.insert(v);
        grafo.push_back({w, {u, v}});
        antigrafo.push_back({-w, {u, v}});
    }

    int val1 = kruskal(grafo, contador.size());
    int val2 = kruskal(antigrafo, contador.size());
    cout << -val2 << endl << val1 << endl;


    return 0;
}