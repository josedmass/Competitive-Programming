/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1340
    Título              :  Eu Posso Adivinhar a Estrutura de Dados! / I Can Guess the Data Structure!
    Categoria           :  Estruturas
    Última Modificação  :  16/02/24
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int main() {

    int num;

    while(cin >> num) {

        queue<int> fila;
        priority_queue<int> fila_prioridade;
        stack<int> pilha;

        vector<bool> estruturas(3, true);

        for(int i = 0; i < num; i++) {
            int op, val;
            cin >> op >> val;
            if(op == 1) {
                fila.push(val);
                fila_prioridade.push(val);
                pilha.push(val);
            }
            else if(op == 2) {
                if(fila.front() != val) estruturas[0] = false;
                if(fila_prioridade.top() != val) estruturas[1] = false;
                if(pilha.top() != val) estruturas[2] = false;
                fila.pop();
                fila_prioridade.pop();
                pilha.pop();
            }
        }

        int aux = 0;
        for(int i = 0; i < 3; i++) {
            if(estruturas[i] == true) aux++;
        }

        if(aux == 0) cout << "impossible" << endl;
        else if(aux > 1) cout << "not sure" << endl;
        else if(estruturas[0]) cout << "queue" << endl;
        else if(estruturas[1]) cout << "priority queue" << endl;
        else if(estruturas[2]) cout << "stack" << endl;

    }
 
    return 0;
}