/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2653
    Título              :  Dijkstra
    Categoria           :  Iniciante
    Última Modificação  :  20/03/24
*/

#include <iostream>
#include <set>

using namespace std;

int main() {

    string s;
    set<string> c;
    while(cin >> s) {
        c.insert(s);
    }

    cout << c.size() << endl;

    return 0;
}