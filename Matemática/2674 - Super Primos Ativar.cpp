/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2674
    Título              :  Super Primos: Ativar! / Super Primes: Engage!
    Categoria           :  Matemática
    Última Modificação  :  18/07/24
*/

#include <bits/stdc++.h>

#define MAX 100001
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

int fator[MAX], mult[MAX], onde[MAX];

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



int main() {
    fastio
    crivo();
    int n;
    while(cin >> n) {
        if(fator[n] != n || n < 2) cout << "Nada" << endl;
        else {
            bool f = true;
            while(n > 0) {
                int d = n % 10;
                if(fator[d] != d || d < 2) {
                    cout << "Primo" << endl;
                    f = false;
                    break;
                }
                n -= d;
                n = n/10;
            }
            if(f) cout << "Super" << endl;
        }
    }
}   