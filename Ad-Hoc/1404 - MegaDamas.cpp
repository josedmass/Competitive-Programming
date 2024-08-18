/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1404
    Título              :  MegaDamas / MegaCheckers
    Categoria           :  Ad-Hoc
    Última Modificação  :  31/03/24
*/

#include <iostream>
#include <cmath>
#include <vector>
 
using namespace std;

int NroPecas(vector<vector<int>>& tabuleiro, int i, int j, int N, int M) {
    int aux = 0;
    int maior;

    // Nova posição válida e eu como uma peça e o lugar que eu vou é vago
    if(i+2 < N && j+2 < M && tabuleiro[i+1][j+1] == 2 && tabuleiro[i+2][j+2] == 0) {
        tabuleiro[i+1][j+1] = 0; // comi a peça
        tabuleiro[i][j] = 0; // saí do meu lugar
        tabuleiro[i+2][j+2] = 1; // fui pro novo lugar
        aux += NroPecas(tabuleiro, i+2, j+2, N, M) + 1; // o melhor que eu consigo a partir da nova posição
        // voltamos pra configuração inicial, para podermos testar outra em outro if
        tabuleiro[i+1][j+1] = 2;
        tabuleiro[i][j] = 1;
        tabuleiro[i+2][j+2] = 0;
    }

    maior = aux;
    aux = 0;

    if(i+2 < N && j-2 >= 0 && tabuleiro[i+1][j-1] == 2 && tabuleiro[i+2][j-2] == 0) {
        tabuleiro[i+1][j-1] = 0;
        tabuleiro[i][j] = 0;
        tabuleiro[i+2][j-2] = 1;
        aux += NroPecas(tabuleiro, i+2, j-2, N, M) + 1;
        tabuleiro[i+1][j-1] = 2;
        tabuleiro[i][j] = 1;
        tabuleiro[i+2][j-2] = 0;
    }

    if(aux > maior) maior = aux; // melhorei?
    aux = 0;

    if(i-2 >= 0 && j+2 < M && tabuleiro[i-1][j+1] == 2 && tabuleiro[i-2][j+2] == 0) {
        tabuleiro[i-1][j+1] = 0;
        tabuleiro[i][j] = 0;
        tabuleiro[i-2][j+2] = 1;
        aux += NroPecas(tabuleiro, i-2, j+2, N, M) + 1;
        tabuleiro[i-1][j+1] = 2;
        tabuleiro[i][j] = 1;
        tabuleiro[i-2][j+2] = 0;
    }

    if(aux > maior) maior = aux;
    aux = 0;

    if(i-2 >= 0 && j-2 >= 0 && tabuleiro[i-1][j-1] == 2 && tabuleiro[i-2][j-2] == 0) {
        tabuleiro[i-1][j-1] = 0;
        tabuleiro[i][j] = 0;
        tabuleiro[i-2][j-2] = 1;
        aux += NroPecas(tabuleiro, i-2, j-2, N, M) + 1;
        tabuleiro[i-1][j-1] = 2;
        tabuleiro[i][j] = 1;
        tabuleiro[i-2][j-2] = 0;
    }

    if(aux > maior) maior = aux;

    return maior;
}
 
int main() {
 
    int N, M;
    while(cin >> N >> M) {
        if(N == 0 && M == 0) break;
        vector<vector<int>> tabuleiro(N, vector<int>(M, -1));
        int teto ;
        if((N*M) % 2 == 0) teto = (N*M)/2;
        else teto = ((N*M)/2)+1;

        int a=N-1, b=0; // iteradores
        for(int i = 0; i < teto; i++) { // Montando o tabuleiro
            int peca;
            cin >> peca;
            tabuleiro[a][b] = peca;
            if(b+2 >= M) {
                a--;
                if(M%2 == 0) {
                    b = (((b+2) % M) + 1) % 2;
                    continue;
                }
            }
            b = (b+2) % M;
        }

        int maior = 0;
        //vector<vector<int>> tabaux = tabuleiro;
        for(int i = 0; i < tabuleiro.size(); i++) {
            for(int j = 0; j < tabuleiro[i].size(); j++) {
                if(tabuleiro[i][j] == 1) { // Peça nossa
                    int quant = NroPecas(tabuleiro, i, j, N, M);
                    //tabuleiro = tabaux;
                    if(quant > maior) maior = quant;
                }
            }
        }
        cout << maior << endl;
        
    }
 
    return 0;
}