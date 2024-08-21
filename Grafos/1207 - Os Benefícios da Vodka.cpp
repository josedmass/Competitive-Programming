/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1207
    Título              :  Os Benefícios da Vodka / The Benefits of Vodka
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

    int N, M;
    while(cin >> N >> M) {
        dinitz grafo(N+M+2);
        int source = 0, sink = N+M+1;
        for(int i = 0; i < N; i++) {
            int cap;
            cin >> cap;
            grafo.add(M+1+i, sink, cap);
        }
        vector<int> quant(M);
        for(int i = 0; i < M; i++) cin >> quant[i];

        ll total = 0;
        for(int i = 0; i < M; i++) {
            int ben;
            cin >> ben;
            grafo.add(source, i+1, ben);
            total += ben;
            for(int j = 0; j < quant[i]; j++) {
                int e;
                cin >> e;
                grafo.add(i+1, M+e, INF);
            }
        }

        ll maxflow = grafo.max_flow(source, sink);
        cout << total - maxflow << endl;

    }

    return 0;
}