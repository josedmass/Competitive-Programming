/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1697
    Título              :  Jaida e o Jogo Multiplicativo / Jaida and Multiply Game
    Categoria           :  Matemática
    Última Modificação  :  20/07/24
*/

#include <bits/stdc++.h>

#define MAX 2000000
#define lli unsigned long long

using namespace std;

bool ehprimo[MAX];
lli primos[MAX];

void crivo() {
    memset(ehprimo, true, sizeof(ehprimo));
    primos[0] = 1; //sim o 1 eh primo
    int cont_prim = 1;
    for(int i = 2; i < MAX; i++) {
        if(ehprimo[i]) {
            primos[cont_prim++] = i;
            for(lli j = 2*i; j < MAX; j += i) {
                ehprimo[j] = false;
            }
        }
    }
}

bool buscabinaria(vector<lli>& vals, lli val, int inicio, int fim) {
    if(inicio > fim) return false;
    if(inicio == fim) return vals[inicio] == val;
    int mid = (inicio + fim) / 2;
    if(vals[mid] == val) return true;
    else if(vals[mid] < val) { //está pra direita
        return buscabinaria(vals, val, mid+1, fim);
    } else return buscabinaria(vals, val, inicio, mid);
}

int main() {

    crivo();
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        vector<lli> vals(n);
        for(int i = 0; i < n; i++) {
            cin >> vals[i];
        }
        sort(vals.begin(), vals.end());
        int i = 0;
        while(true) {
            if(!buscabinaria(vals, primos[i], 0, vals.size()-1)) break;
            else i++;
        }
        cout << primos[i]-1 << endl;
    } 

    return 0;
}