/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2123
    Título              :  A Lei Vai a Cavalo! / The Law Goes on Horseback!
    Categoria           :  Grafos
    Última Modificação  :  07/05/24
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

    int n, m, k;
    int it = 1;
    while(cin >> n >> m >> k) {
		dinitz grafo(n+m+2);
		int source = 0, sink = n+m+1;
		for(int i = 0; i < n; i++) {
			int c;
			cin >> c;
			grafo.add(source, i+1, c);
		}
		for(int i = 0; i < k; i++) {
			int u, v;
			cin >> u >> v;
			grafo.add(u, v+n, 1);
		}
		for(int i = 1; i <= m; i++) grafo.add(i+n, sink, 1);
		ll maxflow = grafo.max_flow(source, sink);
		cout << "Instancia " << it << endl;
		cout << maxflow << endl << endl;
        it++;
    }

    return 0;
}