/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1082
    Título              :  Componentes Conexos / Connected Components
    Categoria           :  Grafos
    Última Modificação  :  13/02/24
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void DFS(int u, vector<vector<int>>& matriz, vector<bool>& visitado, string& comp) {
    visitado[u] = true;
    comp += (char)(u + 'a'); // Adiciona o vértice à componente conectada

    for(int i = 0; i < matriz.size(); i++) {
        if(matriz[u][i] == 1 && !visitado[i]) {
            DFS(i, matriz, visitado, comp);
        }
    }
}

int main() {
    int N, V, E;
    cin >> N;

    for(int caso = 0; caso < N; caso++) {

        cout << "Case #" << caso + 1 << ":" << endl;

        cin >> V >> E;
        vector<vector<int>> matriz_adj(V, vector<int>(V, 0));
        vector<bool> visitado(V, false);

        for(int j = 0; j < E; j++) {
            char u, v;
            cin >> u >> v;
            matriz_adj[u - 'a'][v - 'a'] = 1; // aresta existente
            matriz_adj[v - 'a'][u - 'a'] = 1;
        }

        int cont = 0;

        for(int j = 0; j < V; j++) {
            if (!visitado[j]) {
                cont++;
                string componente;
                DFS(j, matriz_adj, visitado, componente);
                sort(componente.begin(), componente.end());
                for(int k = 0; k < componente.size(); k++) {
                    cout << componente[k] << ',';
                }
                cout << endl;
            }
        }
        cout << cont << " connected components" << endl << endl;
    }

    return 0;
}