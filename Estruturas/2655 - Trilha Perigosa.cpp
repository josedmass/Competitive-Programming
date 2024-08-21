/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2655
    Título              :  Trilha Perigosa / Dangerous Trail
    Categoria           :  Estruturas
    Última Modificação  :  10/08/24
*/

#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(0)

using namespace std;

// binary indexed tree
int tree[100005][55];
int a[100005];

void atualiza(int idx, int monstro, int w, int n) {
    while(idx <= n) {
        tree[idx][monstro] += w;
        idx += (idx & -idx);
    }
}

int consulta(int idx, int monstro) {
    int res = 0;
    while(idx > 0) {
        res += tree[idx][monstro];
        idx -= (idx & -idx);
    }
    return res;
}

int main() {

    fastio;

    int n, q, m;
    cin >> n >> q >> m;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        atualiza(i, a[i], 1, n);
    }

    int op, x1, x2;
    for(int i = 1; i <= q; i++) {
        cin >> op >> x1 >> x2;
        if(op == 1) { // consulta
            int res = 0;
            for(int i = 1; i <= m; i++) {
                int aux = consulta(x2, i) - consulta(x1-1, i);
                if(aux) res++;
            }
            cout << res << endl;
        } else { // atualiza
            atualiza(x1, x2, 1, n);
            atualiza(x1, a[x1], -1, n);
            a[x1] = x2;
        }
    }

    return 0;
}