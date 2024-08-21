/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2898
    Título              :  Olimpíadas / Olympiads
    Categoria           :  Ad-Hoc
    Última Modificação  :  10/05/24
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

// Recupera os caminhos utilizados no fluxo
vector<pair<int, int>> get_paths(dinitz& g, int s, int t) {
    int maxflow = g.max_flow(s, t);
    vector<pair<int, int>> paths; //fluxo x distância
    queue<pair<int, pair<int, int>>> q; //vértice x fluxo x distância
    q.push({s, {maxflow, 0}});

    while(!q.empty()) {
        int u = q.front().first; //vértice
        int flow = q.front().second.first; //fluxo
        int d = q.front().second.second; //distancia
        q.pop();
        if(u == t) {
            paths.push_back({flow, d});
            continue;
        }
        for(auto& e : g.g[u]) {
            if(e.flow > 0) {
                int f = min(e.flow, flow); //o que foi mandado pra aresta
                if(f != 0) {
                    q.push({e.to, {f, d+1}});
                    flow -= f;
                    e.flow -= f;
                }
            }
        }
    }

    return paths;

}

int main() {
    int N, M, A;
    while(cin >> N >> M >> A && (N || M || A)) {
        dinitz grafo(N+1);
        for(int i = 0; i < M; i++) {
            ll O, D, S;
            cin >> O >> D >> S;
            grafo.add(O, D, S);
        }
        
        vector<pair<int, int>> paths = get_paths(grafo, 1, N);

        int days = 0, flow = 0;
        while(true) { //buscamos a primeira ocorrência que supera
            flow = 0;
            for(auto path : paths)
                flow += path.first * max(0, days-path.second+1);
            if(flow >= A) break;
            days++;
        }

        cout << days << endl;
    }
}