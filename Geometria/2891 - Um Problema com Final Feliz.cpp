/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2891
    Título              :  Um Problema com Final Feliz / A Problem With A Happy Ending
    Categoria           :  Geometria
    Última Modificação  :  06/08/24
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

int area(vector<ponto>& fig) { // área do polígono
    int ret = 0;
    for(int i = 0; i < fig.size(); i++) {
        ret += orientacao({0, 0}, fig[i], fig[(i+1) % fig.size()]);
    }
    return abs(ret/2);
}

void convex_hull(vector<ponto>& fig) {
    sort(fig.begin(), fig.end());
    fig.erase(unique(fig.begin(), fig.end()), fig.end());
    vector<ponto> aux1, aux2;
    if(fig.size() > 1) {
        for(int i = 0; i < fig.size(); i++) {
            while(aux1.size() > 1 && (orientacao(aux1.end()[-2], aux1.end()[-1], fig[i]) <= 0))
                aux1.pop_back();
            aux1.push_back(fig[i]);
        }
        for(int i = fig.size()-1; i >= 0; i--) {
            while(aux2.size() > 1 && (orientacao(aux2.end()[-2], aux2.end()[-1], fig[i]) <= 0))
                aux2.pop_back();
            aux2.push_back(fig[i]);
        }
        aux1.pop_back(), aux2.pop_back();
        for(ponto i : aux2) aux1.push_back(i);
        fig = aux1;
    }
}

int main() {
    int comb[5][4] = {{0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 3, 4}, {0, 2, 3, 4}, {1, 2, 3, 4}};
    int x1, x2, x3, x4, x5;
    int y1, y2, y3, y4, y5;
    while(cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5) {
        if(!(x1 || x2 || x3 || x4 || x5 || y1 || y2 || y3 || y4 || y5)) break;
        int A = -1;
        ponto pts[5] = {{x1,y1}, {x2, y2}, {x3, y3}, {x4, y4}, {x5, y5}};
        for(int i = 0; i < 5; i++) {
            vector<ponto> aux;
            for(int j = 0; j < 4; j++) {
                aux.push_back(pts[comb[i][j]]);
            }
            convex_hull(aux);
            if(aux.size() == 4) A = max(A, area(aux));
        }
        cout << A << endl;
    }

    return 0;
}