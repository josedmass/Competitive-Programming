/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2971
    Título              :  Jogo de Baralho / Jar of Water Game
    Categoria           :  Ad-Hoc
    Última Modificação  :  30/03/24
*/

#include <iostream>
#include <vector>
 
using namespace std;

pair<bool, int> um_naipe(vector<vector<int>> contador) {
    int quant = 0;
    for(int i = 0; i < contador.size(); i++) {
        for(int j = 0; j < contador[i].size(); j++) {
            if(contador[i][j] > 0) quant++;
            if(quant > 1) {
                quant = 0;
                break;
            }
        }
        if(quant == 1) return {true, i};
        quant = 0;
    }
    return {false, -1};
}

int solve(vector<vector<int>>& contador, int K) {
    bool curinga = false;
    int i = K;
    pair<bool, int> retorno;
    while(true) {

        if(curinga && contador[i][13] > 0) {
            contador[i][13]--;
            contador[(i+1) % contador.size()][13]++;
            curinga = false;
        }

        else {
            if(contador[i][13] > 0) {
                curinga = true;
            }
            // Encontrar a menos usada
            int min = 1000;
            int idx = 0;
            for(int j = 0; j < contador[i].size()-1; j++) {
                if(contador[i][j] > 0 && contador[i][j] < min) {
                    min = contador[i][j];
                    idx = j;
                }
            }
            contador[i][idx]--;
            contador[(i+1) % contador.size()][idx]++;
        }

        retorno = um_naipe(contador);
        if(retorno.first) break;
        i = (i+1) % contador.size();
    }
    return retorno.second;
}


int main() {
 
    int N, K;
    cin >> N >> K;

    vector<vector<int>> contador(N, vector<int>(14, 0)); // jogador x naipe -> quantidade; contador[13] é o curinga

    for(int i = 0; i < N; i++) {
        string mao;
        cin >> mao;
        for(int j = 0; j < mao.size(); j++) {
            int k;
            switch (mao[j]){
                case 'A':
                    k = 0;
                    break;
                case '2':
                    k = 1;
                    break;
                case '3':
                    k = 2;
                    break;
                case '4':
                    k = 3;
                    break;
                case '5':
                    k = 4;
                    break;
                case '6':
                    k = 5;
                    break;
                case '7':
                    k = 6;
                    break;
                case '8':
                    k = 7;
                    break;
                case '9':
                    k = 8;
                    break;
                case 'D':
                    k = 9;
                    break;
                case 'Q':
                    k = 10;
                    break;
                case 'J':
                    k = 11;
                    break;
                case 'K':
                    k = 12;
                    break;
            }
            contador[i][k]++;
        }
    }

    contador[K-1][13] = 1;

    cout << solve(contador, K-1) + 1 << endl;
 
    return 0;
}