/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1194
    Título              :  Prefixa, Infixa e Posfixa / Pre, In and Post
    Categoria           :  Grafos
    Última Modificação  :  14/02/24
*/

#include <iostream>
#include <string>
 
using namespace std;

struct No {
    char letra;
    No* esq;
    No* dir;
};

int Indice(string infixa, char letra) {
    for(int i = 0; i < infixa.size(); i++) {
        if(infixa[i] == letra) return i;
    }

    return -1;
}
 
No* makeTree(string prefixa, string infixa, int& indice, int inicio, int fim) {

    if (inicio > fim) return NULL;

    No* raiz = new No();
    raiz->letra = prefixa[indice];

    int ind = Indice(infixa, prefixa[indice]);
    indice++;

    raiz->esq = makeTree(prefixa, infixa, indice, inicio, ind-1);
    raiz->dir = makeTree(prefixa, infixa, indice, ind+1, fim);

    return raiz;
}

void printPosfixa(No* raiz) {
    if (raiz == NULL) return;

    printPosfixa(raiz->esq);
    printPosfixa(raiz->dir);
    cout << raiz->letra;
}

int main() {
 
    int numcasos;
    cin >> numcasos;

    for(int caso = 0; caso < numcasos; caso++) {

        int numnodos;
        string prefixa, infixa;
        cin >> numnodos >> prefixa >> infixa;

        int indice = 0;
        No* raiz = makeTree(prefixa, infixa, indice, 0, numnodos-1);
        printPosfixa(raiz);
        cout << endl;
    }
 
    return 0;
}