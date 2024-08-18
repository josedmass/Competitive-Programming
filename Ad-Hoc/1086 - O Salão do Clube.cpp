/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1086
    Título              :  O Salão do Clube / The Club Ballroom
    Categoria           :  Ad-Hoc
    Última Modificação  :  15/02/24
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int buscabinaria(vector<int>& comprimentos, int valor, int inicio) {
    int esq = inicio, dir = comprimentos.size() - 1;
    while (esq <= dir) {
        if(comprimentos[esq] == valor) return esq;
        if(comprimentos[dir] == valor) return dir;
        int mid = esq + (dir - esq) / 2;
        if (comprimentos[mid] == valor) return mid;
        else if (comprimentos[mid] < valor) {
            if(comprimentos[mid] == 0) esq++;
            else dir = mid - 1;
        }
        else esq = mid + 1;
    }
    return -1;
}

int solve(vector<int> comprimentos, int& indice, int dim, int numit) {

    int quant = 0, ajuste = 0;

    for(int i = 0; i < numit; i++) {
        if(indice == comprimentos.size()) break;
        int maior = comprimentos[indice];
        if(maior > dim) {
            comprimentos[indice] = 0;
            indice++;
            i--;
        }
        else {
            if(maior == dim) {
                comprimentos[indice] = 0;
                indice++;
                quant++;
                ajuste++;
            }
            else {
                if(maior < dim) {
                    bool flag = true;
                    int j = buscabinaria(comprimentos, dim - maior, indice+1);
                    if(j != -1) {
                        comprimentos[j] = 0;
                        quant += 2;
                        ajuste++;
                        flag = false;
                    }
                    comprimentos[indice] = 0;
                    indice++;
                    if(flag) i--;
                }
            }
        }
    }

    if(ajuste == numit) return quant;
    return INT_MAX;
}

int main() {

    while(true) {
        int dimx, dimy;
        cin >> dimx >> dimy;

        if(dimx == 0 && dimy == 0) break;
        dimx *= 100;
        dimy *= 100;

        int largura, numtabuas;
        cin >> largura >> numtabuas;

        vector<int> comprimentos(numtabuas);

        for(int i = 0; i < numtabuas; i++) {
            cin >> comprimentos[i];
            comprimentos[i] *= 100;
        }

        sort(comprimentos.begin(), comprimentos.end(), [](const int& a, const int& b) {
            return a > b;
        });

        int min1 = dimx * dimy, min2 = dimx * dimy;
        int indice = 0;

        if(dimx % largura == 0) {
            min1 = solve(comprimentos, indice, dimy, dimx / largura);
            indice = 0;
        }
        if(dimy % largura == 0) {
            min2 = solve(comprimentos, indice, dimx, dimy / largura);
        }

        int result = min(min1, min2);
        if(result != INT_MAX && result != dimx * dimy) cout << result << endl;
        else cout << "impossivel" << endl;
    }
 
    return 0;
}