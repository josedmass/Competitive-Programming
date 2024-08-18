/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1205
    Título              :  Cerco a Leningrado / Siege of Leningrad
    Categoria           :  Grafos
    Última Modificação  :  19/02/24
*/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
 
using namespace std;

vector<int> Dijkstra(int inicio, vector<vector<int>> lista_adj, vector<int> pesos) {

    vector<int> D(lista_adj.size(), INT_MAX);
    D[inicio] = pesos[inicio];

    set<pair<int, int>> Q;
    Q.insert({pesos[inicio], inicio});

    while(!Q.empty()) {

        int v = Q.begin()->second;
        Q.erase(Q.begin());

        for(int i = 0; i < lista_adj[v].size(); i++) {
            int u = lista_adj[v][i];
            int peso = pesos[u];

            if(D[u] > D[v] + peso) {
                Q.erase({D[u], u});
                D[u] = D[v] + peso;
                Q.insert({D[u], u});
            }
        }
    }

    return D;

}
 
int main() {
 
    int nro_pontos, nro_estradas, nro_balas;
    float probabilidade;

    while(cin >> nro_pontos >> nro_estradas >> nro_balas >> probabilidade) {

        vector<vector<int>> lista_adj(nro_pontos);
        vector<int> pesos(nro_pontos, 0);

        for(int i = 0; i < nro_estradas; i++) {
            int p1, p2;
            cin >> p1 >> p2;
            lista_adj[p1-1].push_back(p2-1);
            lista_adj[p2-1].push_back(p1-1);
        }

        int nro_atiradores;
        cin >> nro_atiradores;
        for(int i = 0; i < nro_atiradores; i++) {
            int local;
            cin >> local;
            pesos[local-1]++;
        }

        int inicio, fim;
        cin >> inicio >> fim;

        vector<int> result = Dijkstra(inicio-1, lista_adj, pesos);

        int aux = result[fim-1];
        if(aux > nro_balas) cout << "0.000" << endl;
        else {
            float ans = pow(probabilidade, aux);
            cout << fixed << setprecision(3) << ans << endl;
        }

    }
 
    return 0;
}