/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1362
    Título              :  Minha Camiseta me Serve / My T-Shirt Suits Me
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

    int T;
    cin >> T;
    for(int i = 0; i < T; i++) {
        int N, M;
        cin >> N >> M;

        int source = 0, sink = M+6+1;
        dinitz grafo(6 + M + 2);

        for(int j = 1; j <= 6; j++) grafo.add(source, j, N/6);
        for(int j = 0; j < M; j++) grafo.add(j+6+1, sink, 1);

        for(int j = 0; j < M; j++) {
            string c1, c2;
            cin >> c1 >> c2;
            if(c1 == "XXL" || c2 == "XXL") grafo.add(1, j+1+6, INF);
            if(c1 == "XL" || c2 == "XL") grafo.add(2, j+1+6, INF);
            if(c1 == "L" || c2 == "L") grafo.add(3, j+1+6, INF);
            if(c1 == "M" || c2 == "M") grafo.add(4, j+1+6, INF);
            if(c1 == "S" || c2 == "S") grafo.add(5, j+1+6, INF);
            if(c1 == "XS" || c2 == "XS") grafo.add(6, j+1+6, INF);
        }

        ll maxflow = grafo.max_flow(source, sink);
        if(maxflow >= M) cout << "YES" << endl;
        else cout << "NO" << endl;

    }

    return 0;
}