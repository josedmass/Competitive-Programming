/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  2962
    Título              :  Arte Valiosa / Artwork
    Categoria           :  Grafos
    Última Modificação  :  30/03/24
*/

#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
 
using namespace std;

struct Sensor {
    int rep; // representante do sensor
    int size; // tamanho do representante
    int x;
    int y;
    int raio;
};

double distancia(int x1, int y1, int x2, int y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

int find(int sen, vector<Sensor>& sensores) {
    if(sen != sensores[sen].rep) sensores[sen].rep = find(sensores[sen].rep, sensores);
    return sensores[sen].rep;
}

void unir(int sen1, int sen2, vector<Sensor>& sensores) {
    if(sensores[sensores[sen1].rep].size < sensores[sensores[sen2].rep].size) {
        unir(sen2, sen1, sensores);
        return;
    }
    int a = find(sen1, sensores);
    int b = find(sen2, sensores);
    sensores[b].rep = a;
    sensores[a].size += sensores[b].size;
}

void conjuntos(vector<Sensor>& sensores) {
    for(int i = 0; i < sensores.size(); i++) {
        for(int j = i+1; j < sensores.size(); j++) {
            if(distancia(sensores[i].x, sensores[i].y, sensores[j].x, sensores[j].y) <= sensores[i].raio + sensores[j].raio) {
                // Sensores se interseptam
                unir(i, j, sensores);
            }
        }
    }
}
 
int main() {
 
    int M, N, K;
    cin >> M >> N >> K;

    vector<Sensor> sensores(K);

    for(int i = 0; i < K; i++) {
        int X, Y, S;
        cin >> X >> Y >> S;
        sensores[i] = {i, 1, X, Y, S}; // Ele começa representando a si mesmo
    }

    conjuntos(sensores); // Encontra o conjunto de sensores
    vector<vector<Sensor>> conj_sensores(K);
    for(int i = 0; i < K; i++) {
        conj_sensores[sensores[i].rep].push_back(sensores[i]);
    }

    // Uma vez instanciados os conjuntos de sensores, vamos checar se eles bloqueiam a entrada
    bool flag = true;
    for(int i = 0; i < K; i++) {
        int minx = INT_MAX, miny = INT_MAX;
        int maxx = INT_MIN, maxy = INT_MIN;
        for(int j = 0; j < conj_sensores[i].size(); j++) {
            if(conj_sensores[i][j].x - conj_sensores[i][j].raio < minx) minx = conj_sensores[i][j].x - conj_sensores[i][j].raio; // POR O RAIO
            if(conj_sensores[i][j].x + conj_sensores[i][j].raio > maxx) maxx = conj_sensores[i][j].x + conj_sensores[i][j].raio;
            if(conj_sensores[i][j].y - conj_sensores[i][j].raio < miny) miny = conj_sensores[i][j].y - conj_sensores[i][j].raio;
            if(conj_sensores[i][j].y + conj_sensores[i][j].raio > maxy) maxy = conj_sensores[i][j].y + conj_sensores[i][j].raio;
        }
        if(minx <= 0 && maxx >= M) {
            flag = false;
            break;
        }
        if(miny <= 0 && maxy >= N){
            flag = false;
            break;
        }
        if(maxx >= M && maxy >= N){
            flag = false;
            break;
        }
        if(minx <= 0 && miny <= 0){
            flag = false;
            break;
        }
    }

    if(flag) cout << 'S' << endl;
    else cout << 'N' << endl;
 
    return 0;
}