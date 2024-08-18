/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1767
    Título              :  Saco do Papai Noel / Santa Claus Bag
    Categoria           :  Paradigmas
    Última Modificação  :  22/03/24
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Item {
    int q; //quantidade
    int p; //peso
    bool usado; //pacote usado
};

int mochila(int Q, vector<Item>& itens, int Pac) {
    vector<vector<int>> memoizacao(Q + 1, vector<int>(Pac + 1, 0));

    for (int i = 1; i <= Pac; i++) {
        for (int j = 0; j <= Q; j++) {
            if (itens[i - 1].p > j) memoizacao[j][i] = memoizacao[j][i - 1]; //o peso do objeto ultrapassa a capacidade atual
            else memoizacao[j][i] = max(memoizacao[j][i - 1], memoizacao[j - itens[i-1].p][i-1] + itens[i-1].q); //max entre escolher e não escolher o item
        }
    }

    int q_atual = Q;
    for (int i = Pac; i > 0; i--) {
        if (memoizacao[q_atual][i] != memoizacao[q_atual][i-1]) { //item foi usado
            itens[i-1].usado = true;
            q_atual -= itens[i-1].p;
        }
    }

    return memoizacao[Q][Pac];
}

int main() {

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int Pac;
        cin >> Pac;
        vector<Item> itens(Pac); //vetor de itens

        for (int j = 0; j < Pac; j++) {
            int qt, peso;
            cin >> qt >> peso;
            itens[j] = {qt, peso, false};
        }

        int max_valor = mochila(50, itens, Pac);
        cout << max_valor << " brinquedos" << endl;

        int pt = 0;
        int nro = 0;
        for (int j = 0; j < Pac; ++j) {
            if(itens[j].usado) {
                nro++;
                pt += itens[j].p;
            }
        }
        cout << "Peso: " << pt << " kg" << endl;
        cout << "sobra(m) " << Pac - nro << " pacote(s)" << endl << endl;
    }

    return 0;
}