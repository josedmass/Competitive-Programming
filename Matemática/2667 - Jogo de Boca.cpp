/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2667
    Título              :  Jogo de Boca / Mouth Game
    Categoria           :  Matemática
    Última Modificação  :  19/02/24
*/

#include <iostream>
 
using namespace std;

int mod3(string N) {

    int sum = 0;

    for(int i = 0; i < N.size(); i++) {
        sum += N[i] - '0';
    }

    sum = sum % 3;
    return sum;

}
 
int main() {

    string N;
    cin >> N;

    int ans = mod3(N);
    cout << ans << endl;
 
    return 0;
}