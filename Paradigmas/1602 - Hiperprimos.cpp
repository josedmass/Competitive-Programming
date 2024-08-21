/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1602
    Título              :  Hiperprimos / Hyperprimes
    Categoria           :  Paradigmas
    Última Modificação  :  17/07/24
*/

#include <bits/stdc++.h>

#define MAX 2000001
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

int fator[MAX], mult[MAX], onde[MAX];
int qtdHiper[MAX];

void crivo() {
    for(int i = 1; i <= MAX; i++) {
        fator[i] = i;
        mult[i] = 1;
    }
    for(int i = 2; i <= MAX; i++) {
        if(fator[i] == i) {
            for(int j = 2*i; j <= MAX; j+=i) {
                fator[j] = i;
                if(fator[j/i] == i) {
                    mult[j] = mult[j/i] + 1;
                    onde[j] = onde[j/i];
                }
                else {
                    mult[j] = 1;
                    onde[j] = j/i;
                }
            }
        }
    }
}

int nro_div(int n) {
    if(onde[n] == 0) return mult[n] + 1;
    int m = n, qt = 1;
    while(onde[m] != 0) {
        qt = qt * (mult[m]+1);
        m = onde[m];
    }
    qt = qt * (mult[m]+1);

    return qt;
}

void nro_Hiper() {
    qtdHiper[1] = 0;
    for(int i = 2; i <= MAX; i++) {
        qtdHiper[i] = qtdHiper[i-1];
        if(fator[i] == i) {qtdHiper[i]++; continue;}
        int ndiv = nro_div(i);
        if(fator[ndiv] == ndiv) qtdHiper[i]++;
    }
}

int main() {
    fastio
    crivo();
    nro_Hiper();
    int n;
    while(cin >> n) {
        cout << qtdHiper[n] << endl;
    }
}