/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1357
    Título              :  Em Braille / In Braille
    Categoria           :  Ad-Hoc
    Última Modificação  :  16/02/24
*/

#include <iostream>
#include <vector>
#include <string>
 
using namespace std;

vector<vector<bool>> msg_to_braille(string msg) {

    vector<vector<bool>> braille(msg.size(), vector<bool>(6, false));
    for(int i = 0; i < msg.size(); i++) {
        if(msg[i] == '0') {
            braille[i][0] = false;
            braille[i][1] = true;
            braille[i][2] = true;
            braille[i][3] = true;
            braille[i][4] = false;
            braille[i][5] = false;
        }
        else if(msg[i] == '1') {
            braille[i][0] = true;
            braille[i][1] = false;
            braille[i][2] = false;
            braille[i][3] = false;
            braille[i][4] = false;
            braille[i][5] = false;
        }
        else if(msg[i] == '2') {
            braille[i][0] = true;
            braille[i][1] = false;
            braille[i][2] = true;
            braille[i][3] = false;
            braille[i][4] = false;
            braille[i][5] = false;
        }
        else if(msg[i] == '3') {
            braille[i][0] = true;
            braille[i][1] = true;
            braille[i][2] = false;
            braille[i][3] = false;
            braille[i][4] = false;
            braille[i][5] = false;
        }
        else if(msg[i] == '4') {
            braille[i][0] = true;
            braille[i][1] = true;
            braille[i][2] = false;
            braille[i][3] = true;
            braille[i][4] = false;
            braille[i][5] = false;
        }
        else if(msg[i] == '5') {
            braille[i][0] = true;
            braille[i][1] = false;
            braille[i][2] = false;
            braille[i][3] = true;
            braille[i][4] = false;
            braille[i][5] = false;
        }
        else if(msg[i] == '6') {
            braille[i][0] = true;
            braille[i][1] = true;
            braille[i][2] = true;
            braille[i][3] = false;
            braille[i][4] = false;
            braille[i][5] = false;
        }
        else if(msg[i] == '7') {
            braille[i][0] = true;
            braille[i][1] = true;
            braille[i][2] = true;
            braille[i][3] = true;
            braille[i][4] = false;
            braille[i][5] = false;
        }
        else if(msg[i] == '8') {
            braille[i][0] = true;
            braille[i][1] = false;
            braille[i][2] = true;
            braille[i][3] = true;
            braille[i][4] = false;
            braille[i][5] = false;
        }
        else if(msg[i] == '9') {
            braille[i][0] = false;
            braille[i][1] = true;
            braille[i][2] = true;
            braille[i][3] = false;
            braille[i][4] = false;
            braille[i][5] = false;
        }
    }
    return braille;
}

string braille_to_msg(const vector<vector<bool>>& braille) {

    string msg;
    for(int i = 0; i < braille.size(); i++) {
        if(braille[i][0] == false && braille[i][1] == true && braille[i][2] == true && braille[i][3] == true) msg += '0';
        if(braille[i][0] == true && braille[i][1] == false && braille[i][2] == false && braille[i][3] == false) msg += '1';
        if(braille[i][0] == true && braille[i][1] == false && braille[i][2] == true && braille[i][3] == false) msg += '2';
        if(braille[i][0] == true && braille[i][1] == true && braille[i][2] == false && braille[i][3] == false) msg += '3';
        if(braille[i][0] == true && braille[i][1] == true && braille[i][2] == false && braille[i][3] == true) msg += '4';
        if(braille[i][0] == true && braille[i][1] == false && braille[i][2] == false && braille[i][3] == true) msg += '5';
        if(braille[i][0] == true && braille[i][1] == true && braille[i][2] == true && braille[i][3] == false) msg += '6';
        if(braille[i][0] == true && braille[i][1] == true && braille[i][2] == true && braille[i][3] == true) msg += '7';
        if(braille[i][0] == true && braille[i][1] == false && braille[i][2] == true && braille[i][3] == true) msg += '8';
        if(braille[i][0] == false && braille[i][1] == true && braille[i][2] == true && braille[i][3] == false) msg += '9';
    }
    return msg;
    
}
 
int main() {
 
    int numdigitos;

    while(cin >> numdigitos) {
        if(numdigitos == 0) break;

        char op;
        cin >> op;

        if(op == 'S') {
            string msg;
            cin >> msg;

            vector<vector<bool>> braille = msg_to_braille(msg);
            int aux = 0;
            for(int i = 0; i < 6; i+=2) {
                for(int j = 0; j < numdigitos; j++) {
                    if(braille[j][i]) cout << "*";
                    else cout << ".";
                    if(braille[j][i+1]) cout << "*";
                    else cout << ".";
                    if(j != numdigitos-1) cout << " ";
                }
                cout << endl;
            }
        }

        else if(op == 'B') {
            int aux = 0;
            vector<vector<bool>> braille(numdigitos, vector<bool>(4, false));
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < numdigitos; j++) {
                    string frag;
                    cin >> frag;
                    if(i != 2) {
                        if(frag[0] == '*') braille[j][aux] = true;
                        if(frag[1] == '*') braille[j][aux+1] = true;
                    }
                }
                aux += 2;
            }
            
            string ans = braille_to_msg(braille);
            std::cout << ans << endl;

        }

    }
 
    return 0;
}