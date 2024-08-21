/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1394
    Título              :  Hooligan
    Categoria           :  Grafos
    Última Modificação  :  06/05/24
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define INF INT_MAX

//https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/dinitz.cpp (vlw :D)
struct dinitz {
	const bool scaling = false;
	int lim;
	struct edge {
		int to, cap, rev, flow;
		bool res;
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinitz(int n) : g(n), F(0) {}

	void add(int a, int b, int c) {
		g[a].emplace_back(b, c, g[b].size(), false);
		g[b].emplace_back(a, 0, g[a].size()-1, true);
	}
	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = INF) {
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}
};

int main() {

    int N, M, G;
    while(cin >> N >> M >> G && (N || M || G)) {
        vector<int> pontos(N, 0);
        vector<vector<int>> jogadas(N, vector<int>(N, 0));

        for(int i = 0; i < G; i++) {
            int a, b;
            char c;
            cin >> a >> c >> b;
            if(c == '<') {
                pontos[b] += 2;
            }
            else {
                pontos[a]++;
                pontos[b]++;
            }
            jogadas[a][b]++;
            jogadas[b][a]++;
        }

        // Maximizando a pontuação de 0
        int aux = 0;
        for(int i = 1; i < N; i++) {
            pontos[0] += 2 * (M-jogadas[0][i]); // zero ganha todas as partidas restantes
            aux += M-jogadas[0][i];
        }
        
        int pfalta = (((N*N - N)/2)*M) - G - aux; // quantidade de partidas que faltam
        dinitz grafo(pfalta + N + 1);

        int source = 0;
        aux = 0;
        for(int i = 1; i < N; i++) {
            for(int j = i+1; j < N; j++) {
                int falta = M-jogadas[i][j];
                if(falta > 0) {
                    grafo.add(source, aux+N, falta*2);
                    grafo.add(aux+N, i, falta*2);
                    grafo.add(aux+N, j, falta*2);
                    aux++;
                }
            }
        }

        int sink = N + pfalta;
        for(int i = 1; i < N; i++) {
            if(pontos[0] <= pontos[i]) break;
            grafo.add(i, sink, pontos[0] - pontos[i] - 1);
        }

        ll maxflow = grafo.max_flow(source, sink);
        if(maxflow < 2 * pfalta) cout << 'N' << endl;
        else cout << 'Y' << endl;

    }

    return 0;
}