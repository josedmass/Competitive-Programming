/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1642
    Título              :  Teclado Quebrado / Broken Keyboard
    Categoria           :  Paradigmas
    Última Modificação  :  29/03/24
*/

#include <iostream>
#include <map>
 
using namespace std;

int solve(string texto, int m) {

    int inicio=0, fim=m-1, maior=0;
    map<char, int> usados;

    for(int i = 0; i < m; i++) usados[texto[i]]++;

    while(fim < texto.size() - 1) {

        fim++;
        usados[texto[fim]]++;

        if(usados.size() > m) {
            usados[texto[inicio]]--;
            if(usados[texto[inicio]] == 0) usados.erase(texto[inicio]);
            inicio++;
        }

        if(fim - inicio + 1 > maior) maior = fim - inicio + 1;
        
    }

    return maior;
}
 
int main() {
 
    int m;
    while(cin >> m) {
        if(m == 0) break;
        string texto;
        cin.ignore();
        getline(cin, texto);
        cout << solve(texto, m) << endl;
    }

    return 0;
}