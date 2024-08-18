/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2884
    Título              :  Interruptores
    Categoria           :  Ad-Hoc
    Última Modificação  :  20/03/24
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
 
using namespace std;
 
int main() {
 
    int n, m;
    cin >> n >> m;

    int L;
    cin >> L;
    string s(m, '0'); // 0=desligada, 1=acessa (inicio)
    for(int i = 0; i < L; i++) {
        int j;
        cin >> j;
        s[j-1] = '1';
    }

    vector<string> lamp(n, string(m, '0')); //lampadas associadas ao interruptor i
    for(int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for(int j = 0; j < k; j++) {
            int ki;
            cin >> ki;
            lamp[i][ki-1] = '1';
        }
    }

    map<pair<string, int>, int> mapa; //configuração x iteração -> val
    int it = 0;
    int numit = 0;
    while(true) {
        string aux = lamp[it];
        for(int i = 0; i < aux.size(); i++) { //inverte lâmpadas 
            if(aux[i] == '1') {
                if(s[i] == '1') s[i] = '0';
                else if(s[i] == '0') s[i] = '1';
            }
        }

        numit++;
        if(s == string(m, '0')) break; //deu certo

        mapa[{s, it}]++;
        if(mapa[{s, it}] == 2) { //deu errado
            numit = -1;
            break;
        }
        it = (it+1) % n;
    }

    cout << numit << endl;
 
    return 0;
}