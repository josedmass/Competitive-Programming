/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2973
    Título              :  Maratona Brasileira de Comedores de Pipoca
    Categoria           :  Paradigmas
    Última Modificação  :  04/04/24
*/

#include <iostream>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;
 
int main() {
 
    int N, C, T;
    cin >> N >> C >> T;
    vector<int> pipocas(N);
    int mint = INT_MIN, maxt = 0;
    for(int i = 0; i < N; i++) {
        cin >> pipocas[i];
        mint = max(mint, pipocas[i]);
        maxt += pipocas[i];
    }

    mint = ceil(mint/(T*1.0)); // menor tempo possível
    maxt = ceil(maxt/(T*1.0)); // maior tempo possível

    int aux = mint;
    bool flag = true;

    while (mint < maxt) {
        int mid = mint + (maxt - mint) / 2;
        int subseq = 0, cont = 1;
    
        for (int i = 0; i < N; i++) {
            subseq += pipocas[i];
            if (ceil(subseq / (T * 1.0)) > mid) {
                subseq = pipocas[i];
                cont++;
            }
            if (cont > C) {
                break;
            }
        }
    
        if (cont <= C) {
            maxt = mid;
        } else {
            mint = mid + 1;
        }
    }

    cout << mint << endl;
 
    return 0;
}