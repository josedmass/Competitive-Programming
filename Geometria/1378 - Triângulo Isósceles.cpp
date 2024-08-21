/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1378
    Título              :  Triângulo Isósceles / Isosceles Triangles
    Categoria           :  Geometria
    Última Modificação  :  08/08/24
*/

#include <bits/stdc++.h>

#define lli long long int

using namespace std;

struct ponto {
    lli x;
    lli y;
};

lli dist2(ponto a, ponto b) { // retorna o quadrado da distância
    lli p1 = (a.x - b.x)*(a.x - b.x);
    lli p2 = (a.y - b.y)*(a.y - b.y);
    return p1 + p2;
}

int main() {
    int n;
    vector<ponto> pts(1000);
    while(cin >> n && n) {
        lli u, v;
        for(int i = 0; i < n; i++) {
            cin >> u >> v;
            pts[i] = {u, v};
        }

        lli res = 0;
        for(int i = 0; i < n; i++) {
            map<lli, lli> m;
            for(int j = 0; j < n; j++) {
                if (i == j) continue;
                lli d = dist2(pts[i], pts[j]);
                res += m[d];
                m[d]++;
            }
        }
        
        cout << res << endl;
    }

    return 0;
}
