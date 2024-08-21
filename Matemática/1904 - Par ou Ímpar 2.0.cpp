/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1904
    Título              :  Par ou Ímpar 2.0 / Odds and Evens 2.0
    Categoria           :  Matemática
    Última Modificação  :  20/07/24
*/

#include <bits/stdc++.h>

#define MAX 10000001
#define lli unsigned long long

using namespace std;

bool ehprimo[MAX];

void crivo() {
    memset(ehprimo, true, sizeof(ehprimo));
    ehprimo[0] = ehprimo[1] = false;
    for(lli i = 2; i <= MAX; i++) {
        if(ehprimo[i]) {
            for(lli j = 2*i; j <= MAX; j += i) 
                ehprimo[j] = false;
        }
    }
}

// Quantidade de números primos entre a e b
int quant_primos(int a, int b) {
    int res = 0;
    for(int i = a; i <= b; i++) 
        if(ehprimo[i]) res++;
    return res;
}

// https://www.ime.usp.br/~yw/lic-mat-not-2005/mac110/eps/ep1.pdf
bool ehimpar(int n, int k) {
    for(int i = 0; i < 32; i++) {
        if((k & (1 << i)) > (n & (1 << i))) return false;
    }
    return true;
}

int main() {
    crivo();
    int a, b;
    cin >> a >> b;
    if(a == b) cout << '?' << endl;
    else {
        if(a < b) swap(a, b);
        int qpr = quant_primos(b, a);
        int k = a-b;
        int n = qpr + k - 1;
        bool res = ehimpar(n, k);
        if(res) cout << "Alice" << endl;
        else cout << "Bob" << endl;
    }

    return 0;
}