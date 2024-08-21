/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1464
    Título              :  Camadas da Cebola / Onion Layers
    Categoria           :  Geometria
    Última Modificação  :  07/08/24
*/

#include <bits/stdc++.h>

using namespace std;

struct ponto { // ponto
    int x, y;
    ponto(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator < (const ponto p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator == (const ponto p) const {
		return x == p.x and y == p.y;
	}
};

int orientacao(ponto a, ponto b, ponto c) { // >0 : ccw; <0 : cw
    return (b.x-a.x)*(c.y-b.y) - (b.y-a.y)*(c.x-b.x);
}

void convex_hull(vector<ponto>& fig) {
    sort(fig.begin(), fig.end());
    fig.erase(unique(fig.begin(), fig.end()), fig.end());
    vector<ponto> aux1, aux2;
    if(fig.size() > 1) { // dá para fazer convex hull
        for(int i = 0; i < fig.size(); i++) {
            while(aux1.size() > 1 && (orientacao(aux1.end()[-2], aux1.end()[-1], fig[i]) < 0))
                aux1.pop_back();
            aux1.push_back(fig[i]);
        }
        for(int i = fig.size()-1; i >= 0; i--) {
            while(aux2.size() > 1 && (orientacao(aux2.end()[-2], aux2.end()[-1], fig[i]) < 0))
                aux2.pop_back();
            aux2.push_back(fig[i]);
        }
        aux1.pop_back(), aux2.pop_back();
        for(ponto i : aux2) aux1.push_back(i);
        for(ponto pt : aux1)
            fig.erase(remove(fig.begin(), fig.end(), pt), fig.end());
    }
}

int main() {

    int n;
    while(cin >> n && n) {
        int u, v;
        vector<ponto> fig;
        for(int i = 0; i < n; i++) {
            cin >> u >> v;
            fig.push_back({u, v});
        }
        int res = 0;
        while(fig.size() > 2) {
            convex_hull(fig);
            res++;
        }

        if(res % 2 == 0) cout << "Do not take this onion to the lab!" << endl;
        else cout << "Take this onion to the lab!" << endl;
    }

    return 0;
}