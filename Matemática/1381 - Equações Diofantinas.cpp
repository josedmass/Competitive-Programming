/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1381
    Título              :  Equações Diofantinas / Diophantine Equations
    Categoria           :  Matemática
    Última Modificação  :  19/07/24
*/

#include <bits/stdc++.h>

#define lli unsigned long long int
#define MAX 2000001
#define MOD 1300031

using namespace std;

lli fat[MAX];

vector<int> mdc(int m, int n) {
    if(m%n == 0) return {n, 0, 1};
    vector<int> aux = mdc(n, m%n);
    return {aux[0], aux[2], aux[1]-aux[2]*(m/n)};
}

int inv(int a, int n) {
    vector<int> aux = mdc(a, n);
    return (aux[1] % n + n) % n;
}

int main() {

    // Calcula o fatorial de 1 até MAX
    fat[0] = 1;
    for(int i = 1; i < MAX; i++) {
        fat[i] = (fat[i-1]*i) % MOD;
    }

    int T, N, C;
    cin >> T;
    while(T) {
        T--;
        cin >> N >> C;
        // Fórmula da combinação com repetição
        lli num = fat[C+N-1];
        lli den = (fat[N-1]*fat[C])%MOD;
        lli res = (num * inv(den, MOD)) % MOD;
        cout << res << endl;
    }

    return 0;
}