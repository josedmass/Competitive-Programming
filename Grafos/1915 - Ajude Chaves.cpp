/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1915
    Título              :  Ajude Chaves / Help Chaves
    Categoria           :  Grafos
    Última Modificação  :  07/05/24
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define INF INT_MAX

int letras[26] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};

void codifica(int j, string& s, vector<vector<int>>& seq) {
    map<char, int> m;
    seq[j] = vector<int>(s.size());
    for(int i = 0; i < s.size(); i++) {
        seq[j][i] = m[s[i]]*26 + letras[s[i] - 'A'];
        m[s[i]]++;
    }
}

int LCS(vector<int>& seq1, vector<int>& seq2)
{
    int n = seq1.size();
    int m = seq2.size();

    vector<int> prev(m+1, 0), cur(m+1, 0);

    for(int idx2 = 0; idx2 < m + 1; idx2++)
        cur[idx2] = 0;

    for(int idx1 = 1; idx1 < n+1; idx1++) {
        for(int idx2 = 1; idx2 < m+1; idx2++) {
            if (seq1[idx1 - 1] == seq2[idx2 - 1])
                cur[idx2] = 1 + prev[idx2 - 1];
            else
                cur[idx2] = 0 + max(cur[idx2 - 1], prev[idx2]);
        }
        prev = cur;
    }

    return cur[m];
}

bool deseja(vector<int>& p, vector<int>& b) { //retorna se a pessoa p deseja o brinquedo b
    return ((p.size() + b.size() - 2*LCS(p, b)) % 5) == 0;
}

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
    while(cin >> N >> M && (N || M)) {
        dinitz grafo(N+M+2);
        int source = 0, sink = N+M+1;
        vector<vector<int>> seqp(N);
        for(int i = 0; i < N; i++) {
            string p;
            cin >> p;
            codifica(i, p, seqp);
            grafo.add(source, i+1, 1);
        }
        vector<vector<int>> seqb(M);
        for(int i = 0; i < M; i++) {
            string p;
            cin >> p;
            codifica(i, p, seqb);
            grafo.add(N+i+1, sink, 1);
        }
        
        for(int i = 0; i < N; i++) { //cada pessoa
            for(int j = 0; j < M; j++) { //cada brinquedo
                if(deseja(seqp[i], seqb[j])) grafo.add(i+1, N+1+j, 1);
            }
        }

        ll maxflow = grafo.max_flow(source, sink);
        cout << "P = " << fixed << setprecision(2) << double(maxflow)*100/N << endl;

    }

    return 0;
}