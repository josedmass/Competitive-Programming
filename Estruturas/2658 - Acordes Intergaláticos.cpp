/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2658
    Título              :  Acordes Intergaláticos / Intergalactic Chords
    Categoria           :  Estruturas
    Última Modificação  :  10/08/24
*/

#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(0)

using namespace std;

struct No {
    int nts[10];
    int lazy;
};

No tree[400004];
int ans[400004];

void constroi(int no, int l, int r) {
    if(l == r) {
        tree[no].nts[1] = 1;
        tree[no].lazy = 0;
    } else {
        int meio = (l+r)/2;
        constroi(2*no, l, meio);
        constroi(2*no+1, meio + 1, r);
        for(int i = 0; i < 9; i++) 
            tree[no].nts[i] = tree[2*no].nts[i] + tree[2*no+1].nts[i];
    }
}

void propaga(int no, int l, int r) {
    while(tree[no].lazy >= 9) tree[no].lazy -= 9;
    if(tree[no].lazy) {
        No aux = tree[400002];
        for(int i = 0; i < 9; i++) {
            int paux = i + tree[no].lazy;
            if(paux >= 9) paux -= 9;
            aux.nts[paux] = tree[no].nts[i];
        }
        for(int i = 0; i < 9; i++) tree[no].nts[i] = aux.nts[i];
        if(l != r) {
            tree[2*no].lazy += tree[no].lazy;
            tree[2*no+1].lazy += tree[no].lazy;
        }
        tree[no].lazy = 0;
    }
}

void rangeUpdate(int no, int l, int r, int ul, int ur, int d) {
    propaga(no, l, r);
    if(l > r || l > ur || r < ul) return;
    if(l >= ul && r <= ur) {
        tree[no].lazy += d;
        propaga(no, l, r);
        return;
    }
    int meio = (l+r)/2;
    rangeUpdate(2*no, l, meio, ul, ur, d);
    rangeUpdate(2*no+1, meio+1, r, ul, ur, d);
    for(int i = 0; i < 9; i++) 
        tree[no].nts[i] = tree[2*no].nts[i] + tree[2*no+1].nts[i];  
}

No consulta(int no, int l, int r, int ql, int qr) {
    propaga(no, l, r);    
    if(l > qr || r < ql) return tree[400002];
    if(l >= ql && r <= qr) return tree[no];
    int meio = (l+r)/2;
    No A = consulta(2*no, l, meio, ql, qr);
    No B = consulta(2*no+1, meio+1, r, ql, qr);
    No res = tree[400002];
    for(int i = 0; i < 9; i++) res.nts[i] = A.nts[i] + B.nts[i];
    return res;
}

void solve(int no, int l, int r) {
    propaga(no, l, r);
    if(l == r) {
        for(int i = 0; i < 9; i++) {
            if(tree[no].nts[i]) {
                ans[l] = i;
                return;
            }
        }
    }
    int meio = (l+r)/2;
    solve(2*no, l, meio);
    solve(2*no+1, meio+1, r);
}

int main() {
    fastio;
    int n, q;
    cin >> n >> q;
    constroi(1, 0, n-1);
    int a, b;
    for(int i = 0; i < q; i++) {
        cin >> a >> b;
        if(a > b) swap(a, b);
        No aux = consulta(1, 0, n-1, a, b);
        int maior = 0, nota = -1;
        for(int i = 0; i < 9; i++) {
            if(aux.nts[i] >= maior) {
                maior = aux.nts[i];
                nota = i;
            }
        }
        rangeUpdate(1, 0, n-1, a, b, nota);
    }
    solve(1, 0, n-1);
    for(int i = 0; i < n; i++)
        cout << ans[i] << endl;

    return 0;
}
