/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1470
    Título              :  Máquina Dobradora / Folding Machine
    Categoria           :  Ad-Hoc
    Última Modificação  :  20/02/24
*/

#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

vector<int> dobra(const vector<int>& entrada, int casas) {

    if(casas == 0) return entrada;

    if(casas == entrada.size()) {
        vector<int> saida = entrada;
        reverse(saida.begin(), saida.end());
        return saida;
    }
    

    vector<int> saida;

    if(casas <= entrada.size() / 2) {

        for(int i = 0; i < casas; i++) 
            saida.insert(saida.begin(), entrada[casas+i] + entrada[casas-1-i]);
        
        for(int i = 0; i < entrada.size() - casas - casas; i++) 
            saida.insert(saida.begin(), entrada[casas+casas+i]);
    }

    else {

        for(int i = 0; i < entrada.size() - casas; i++) 
            saida.insert(saida.begin(), entrada[casas+i] + entrada[casas-1-i]);

        for(int i = 2*casas - entrada.size() - 1; i >= 0; i--) 
            saida.insert(saida.begin(), entrada[i]);
    }

    return saida;
}

bool confere(const vector<int>& s1, const vector<int>& s2) {

    return s1 == s2;
    
}

bool check(const vector<int>& fita_entrada, const vector<int>& fita_saida) {

    vector<int> aux = fita_entrada;

    if(fita_entrada.size() == 1) return confere(fita_entrada, fita_saida);

    if(aux.size() < fita_saida.size()) return false;
    if(aux.size() == fita_saida.size()) {
        vector<int> aux2 = dobra(aux, aux.size());
        if(confere(aux, fita_saida) || confere(aux2, fita_saida)) return true;
    }

    for(int i = 1; i <= aux.size(); i++) {
        aux = dobra(fita_entrada, i);
        if(confere(aux, fita_saida)) return true;
        if(check(aux, fita_saida)) return true;
    }

    return false;

}
 
int main() {
 
    int tam_entrada;

    while(cin >> tam_entrada) {

        vector<int> fita_entrada(tam_entrada);
        for(int i = 0; i < tam_entrada; i++) cin >> fita_entrada[i];

        int tam_saida;
        cin >> tam_saida;
        vector<int> fita_saida(tam_saida);
        for(int i = 0; i < tam_saida; i++) cin >> fita_saida[i];

        if(check(fita_entrada, fita_saida)) cout << 'S' << endl;
        else cout << 'N' << endl;
    }
    
    return 0;
}