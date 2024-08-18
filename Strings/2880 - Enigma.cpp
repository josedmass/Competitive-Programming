/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2880
    Título              :  Enigma
    Categoria           :  Strings
    Última Modificação  :  19/02/24
*/

#include <iostream>
 
using namespace std;

int possiveis(string msg, string crib) {

    int quant = 0;
    int possibs = msg.size() - crib.size() + 1;

    for(int i = 0; i < possibs; i++) {

        bool flag = true;

        for(int j = 0; j < crib.size(); j++) {
            if(crib[j] == msg[i+j]) {
                flag = false; 
                break;
            }
        }

        if(flag) quant++;
        
    }

    return quant;

}
 
int main() {
 
    string msg, crib;
    cin >> msg >> crib;

    int ans = possiveis(msg, crib);
    cout << ans << endl;
 
    return 0;
}