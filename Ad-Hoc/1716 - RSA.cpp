/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1716
    Título              :  RSA
    Categoria           :  Ad-Hoc
    Última Modificação  :  19/07/24
*/

#include <bits/stdc++.h>

#define lli unsigned long long int

using namespace std;

lli tot(lli n) { // para n = p*q, onde p e q são primos
    lli res = n;
    for(int i = 2; i <= sqrt(n) + 1; i++) {
        if(n%i == 0) {
            n /= i;
            res -= res/i;
        }
    }
    if(n > 1) res -= res/n;
    return res;
}

vector<int> mdc(int m, int n) {
    if(m%n == 0) return {n, 0, 1};
    vector<int> aux = mdc(n, m%n);
    return {aux[0], aux[2], aux[1]-aux[2]*(m/n)};
}

int inv(int a, int n) {
    vector<int> aux = mdc(a, n);
    return (aux[1] % n + n) % n;
}

// encontra M = C^D mod N
lli potmod(lli C, lli D, lli N) {
    if(D == 0) return 1;
    lli X = potmod(C, D/2, N);
    if(D%2 == 0) return (X*X) % N;
    else return (((X*X)%N) * C) % N;
}

int main() {
    lli N, E, C;
    while(cin >> N >> E >> C) {
        lli totN = tot(N);
        lli D = inv(E, totN);
        cout << potmod(C, D, N) << endl;
    }

    return 0;
}