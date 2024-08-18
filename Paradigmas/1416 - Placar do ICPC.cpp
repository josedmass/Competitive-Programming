/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1416
    Título              :  Placar do ICPC / ICPC Scoreboard
    Categoria           :  Paradigmas
    Última Modificação  :  26/03/24
*/

#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <tuple>
 
using namespace std;

class Afim {
    public:
        int a; // acompanha o x
        int b; // termo independente
};

double resolve(Afim f1, Afim f2) { //encontra o y
    if((f1.a == 0 && f2.a == 0) || (f1.a == f2.a)) {
        if(f1.b == f2.b) return -1;
        return 0;
    }
    double ans = ((double)f2.b - (double)f1.b) / ((double)f1.a - (double)f2.a);
    return ans;
}

tuple<int, int, bool> solve(vector<vector<Afim>> times) {
    int min = INT_MIN;
    int max = INT_MAX;
    int flag  = false;
    for(int i = 0; i < times.size(); i++) {
        flag = false;
        for(int j = 0; j < times[i].size(); j++) {
            flag = false;
            for(int k = j+1; k < times[i].size(); k++) {
                double ans = resolve(times[i][j], times[i][k]);
                if(ans < 20 && ans >= 0 && ans > min) {
                    min = floor(ans);
                    flag = false;
                }
                else if(ans > 20 && ans < max) {
                    max = ceil(ans);
                    flag = false;
                }
                else if(ans == 20) return make_tuple(20, 20, false);
                else if(ans == -1) {
                    flag = true;
                    continue;
                }
            }
        }
    }
    return make_tuple(min, max, flag);
}

pair<int, string> separa(string problema) {
    int A;
    string S;
    string aux;
    for(int i = 0; i < problema.size(); i++) {
        if(problema[i] == '/') {
            A = stoi(aux);
            aux = "";
            continue;
        }
        aux += problema[i];
    }
    
    S = aux;
    return {A, S};
}
 
int main() {
 
    int T, P;
    while(cin >> T >> P) {
        if(T == 0 && P == 0) break;
        vector<vector<Afim>> times(P+1);
        for(int i = 0; i < T; i++) {
            int a = 0, b = 0;
            int quant_resolvida = 0;
            for(int j = 0; j < P; j++) {
                string problema;
                cin >> problema;
                pair<int, string> dados = separa(problema);
                int A = dados.first;
                string S = dados.second;
                if(S != "-") {
                    quant_resolvida++;
                    b += stoi(S);
                    a += A - 1;
                }
            }
            times[quant_resolvida].push_back({a, b});
        }
        // Lógica pra resolver o problema
        tuple<int, int, bool> ans = solve(times);
        if(get<2>(ans)) {
            if(get<0>(ans) == INT_MIN || get<0>(ans) == 0) get<0>(ans) = 1;
            cout << get<0>(ans) << " ";
            if(get<1>(ans) == INT_MAX) cout << "*" << endl;
            else cout << get<1>(ans) << endl;
        }
        else {
            if(get<0>(ans) == INT_MIN || get<0>(ans) == 0) get<0>(ans) = 1;
            else if(get<0>(ans) != 20) get<0>(ans) += 1;
            cout << get<0>(ans) << " ";
            if(get<1>(ans) == INT_MAX) cout << "*" << endl;
            else if(get<1>(ans) != 20) cout << get<1>(ans) - 1 << endl;
            else cout << get<1>(ans) << endl;
        }
    }
 
    return 0;
}