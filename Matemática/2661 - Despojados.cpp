/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2661
    Título              :  Despojados / Stripped
    Categoria           :  Matemática
    Última Modificação  :  20/03/24
*/

#include <iostream>
#include <cmath>
 
using namespace std;

bool despojado(long long int val) {

    bool nprimo = false;
    for(long long int i = 2; i < sqrt(val); i++) {
        if(val % (i*i) == 0) return false; //não pode ser múltiplo de quadrado perfeito
        if(val % i == 0) nprimo = true; //não é primo
    }

    return nprimo;
}
 
int main() {
 
    long long int N;
    cin >> N;

    long long int sum = 0;
    for(long long int i = 1; i <= sqrt(N); i++) {
        if(N % i == 0) {
            if(despojado(i)) sum++;
            if(i != N/i && despojado(N/i)) sum++;
        }
    }

    cout << sum << endl;
 
    return 0;
}