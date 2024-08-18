/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1021
    Título              :  Notas e Moedas / Banknotes and Coins
    Categoria           :  Iniciante
    Última Modificação  :  13/02/24
*/


#include <iostream>
 
using namespace std;
 
int main() {

    float valor;
    cin >> valor;

    valor += 0.0009;

    int n100, n50, n20, n10, n5, n2, n1, n050, n025, n010, n005, n001;
    n100 = n50 = n20 = n10 = n5 = n2 = n1 = n050 = n025 = n010 = n005 = n001 = 0;

    if((int)(valor / 100) >= 1) {
        n100 = valor / 100;
        valor -= 100 * n100;
    }

    if((int)(valor / 50) >= 1) {
        n50 = valor / 50;
        valor -= 50 * n50;
    }

    if((int)(valor / 20) >= 1) {
        n20 = valor / 20;
        valor -= 20 * n20;
    }

    if((int)(valor / 10) >= 1) {
        n10 = valor / 10;
        valor -= 10 * n10;
    }

    if((int)(valor / 5) >= 1) {
        n5 = valor / 5;
        valor -= 5 * n5;
    }

    if((int)(valor / 2) >= 1) {
        n2 = valor / 2;
        valor -= 2 * n2;
    }

    if((int)(valor / 1) >= 1) {
        n1 = valor / 1;
        valor -= 1 * n1;
    }

    if((int)(valor / 0.50) >= 1) {
        n050 = valor / 0.50;
        valor -= 0.50 * n050;
    }

    if((int)(valor / 0.25) >= 1) {
        n025 = valor / 0.25;
        valor -= 0.25 * n025;
    }

    if((int)(valor / 0.10) >= 1) {
        n010 = valor / 0.10;
        valor -= 0.10 * n010;
    }

    if((int)(valor / 0.05) >= 1) {
        n005 = valor / 0.05;
        valor -= 0.05 * n005;
    }

    if((int)(valor / 0.01) >= 1) {
        n001 = valor / 0.01;
        valor -= 0.01 * n001;
    }

    cout << "NOTAS:" << endl;
    cout << n100 << " nota(s) de R$ 100.00" << endl;
    cout << n50 << " nota(s) de R$ 50.00" << endl;
    cout << n20 << " nota(s) de R$ 20.00" << endl;
    cout << n10 << " nota(s) de R$ 10.00" << endl;
    cout << n5 << " nota(s) de R$ 5.00" << endl;
    cout << n2 << " nota(s) de R$ 2.00" << endl;
    
    cout << "MOEDAS:" << endl;
    cout << n1 << " moeda(s) de R$ 1.00" << endl;
    cout << n050 << " moeda(s) de R$ 0.50" << endl;
    cout << n025 << " moeda(s) de R$ 0.25" << endl;
    cout << n010 << " moeda(s) de R$ 0.10" << endl;
    cout << n005 << " moeda(s) de R$ 0.05" << endl;
    cout << n001 << " moeda(s) de R$ 0.01" << endl;

    return 0;
}