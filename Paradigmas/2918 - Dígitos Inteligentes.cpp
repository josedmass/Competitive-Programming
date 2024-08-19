/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2918
    Título              :  Dígitos Inteligentes / Smart Digits
    Categoria           :  Paradigmas
    Última Modificação  :  27/04/24
*/

#include <bits/stdc++.h>

#define lli unsigned long long int
#define MOD 1000000007

using namespace std;

//https://www.geeksforgeeks.org/count-sum-of-digits-in-numbers-from-1-to-n/

lli sum1toN(lli n) {
    if(n < 10) return n*(n+1)/2; // base -> somatório de uma PA
    lli d = log10(n); // nro de dígitos - 1 de n

    vector<lli> table(d+1); // guarda a soma de 1 até (10^i)-1, para todo i=1:d
    table[0] = 0, table[1] = 45;
    for (int i=2; i<=d; i++)
        table[i] = table[i-1]*10 + 45*ceil(pow(10,i-1));
    
    lli p = ceil(pow(10, d)); //10^d
    lli msd = n/p; // dígito mais significativo

    return msd*table[d] + (msd*(msd-1)/2)*p + msd*(1+n%p) + sum1toN(n%p);

}

int main() {

    lli L, R;
    while(cin >> L >> R) {
        cout << (sum1toN(R) - sum1toN(L-1))%MOD << endl;
    }

    return 0;
}