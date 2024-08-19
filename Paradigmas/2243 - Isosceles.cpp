/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2243
    Título              :  Isosceles
    Categoria           :  Paradigmas
    Última Modificação  :  10/04/24
*/

#include <bits/stdc++.h>
 
using namespace std;

int MaxVal(int N, vector<int> h) {
    int max = 1;
    for(int i = 1; i < N; i++) {
        if(N - i <= max) break; // não tem mais como ter triângulo a partir dessa posição
        if(h[i] < max+1) continue;
        int aux = max;
        bool flag = false;
        int k1 = i-1; // iterador pra esquerda
        int k2 = i+1; // iterador pra direita
        for(int j = 0; j < max; j++) {
            if(h[k1] < aux || h[k2] < aux) {
                flag = true;
                break;
            }
            aux--;
            k1--;
            k2++;
        }
        
        if(flag) continue;
        max++;
    }
    return max;
}
 
int main() {
 
    int N;
    cin >> N;
    vector<int> h(N); // vetor de alturas
    for(int i = 0; i < N; i++) {
        cin >> h[i];
    }

    cout << MaxVal(N, h) << endl;
 
    return 0;
}