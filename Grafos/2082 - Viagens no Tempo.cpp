/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2082
    Título              :  Viagens no Tempo / Time Travel
    Categoria           :  Grafos
    Última Modificação  :  11/05/24
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define INF INT_MAX

ll res = INF;

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

    int T;
    cin >> T;
    for(int i = 0; i < T; i++) {
        int N, M;
        cin >> N >> M;
        map<pair<int, int>, int> edges;
        dinitz grafo(N);
        for(int j = 0; j < M; j++) {
            int u, v, c;
            cin >> u >> v >> c;
            if(u > v) edges[{u-1, v-1}] = c;
            else edges[{v-1, u-1}] = c;
        }

        for(auto e : edges) {
            grafo.add(e.first.first, e.first.second, e.second);
            grafo.add(e.first.second, e.first.first, e.second);
        }

        for(int source = 1; source < N; source++) {
            dinitz aux = grafo;
            ll maxflow = aux.max_flow(source, 0);
            if(maxflow) res = min(res, maxflow);
        }

        cout << res << endl;
        res = INF;
    }

    return 0;
}