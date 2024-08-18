/*
    Autor               :  José Eduardo Duarte Massucato
    Tag                 :  1385
    Título              :  Recuperação de Relatório / Report Recovery
    Categoria           :  Strings
    Última Modificação  :  29/03/24
*/


#include <iostream>
#include <climits>
#include <vector>

using namespace std;

void gerarCombinacoes(vector<string>& result, string prefixo, string sufixo, int it, int sum, vector<int> maior, int nro_prod, bool pra_valores) {
    if(it == 0) {
        if(sufixo.size() >= 6) return;
        if(stoi(sufixo) == sum) result.push_back(prefixo + " " + sufixo);
        return;
    }

    for(int i = 0; i < sufixo.size(); i++) {
        if(i == 5) break;
        string parte = sufixo.substr(0, i);
        if(!parte.empty()) {
            if(parte.size() > 1 && parte[0] == '0') break;
            int valor = stoi(parte);
            if(pra_valores && valor > maior[nro_prod - it]) break;
            string novo_prefixo = prefixo + " " + parte;
            sum += valor;
            string novo_sufixo = sufixo.substr(i);
            gerarCombinacoes(result, novo_prefixo, novo_sufixo, it - 1, sum, maior, nro_prod, pra_valores);
            sum -= valor;
        }
    }

    return;
}

void gerarPermutacoesRec(vector<vector<string>>& possibilidades, int nivel, vector<string>& permutacoes, string permutacaoAtual) {
    if(nivel == possibilidades.size()) {
        permutacoes.push_back(permutacaoAtual);
        return;
    }

    for(const string& elemento : possibilidades[nivel]) {
        string novaPermutacao = permutacaoAtual + '\n' + elemento;
        gerarPermutacoesRec(possibilidades, nivel+1, permutacoes, novaPermutacao);
    }
}

vector<string> gerarPermutacoes(vector<vector<string>>& possibilidades) {
    vector<string> permutacoes;
    gerarPermutacoesRec(possibilidades, 0, permutacoes, "");
    return permutacoes;
}

vector<vector<int>> preProcessa(string permutacao) {

    vector<vector<int>> result;
    string val;
    vector<int> aux;

    for(int i = 2; i < permutacao.size(); i++) {

        if(permutacao[i] == ' ' && !val.empty()) {
            aux.push_back(stoi(val));
            val = "";
        }
        
        else if(permutacao[i] == '\n' && !val.empty()) {
            aux.push_back(stoi(val));
            result.push_back(aux);
            val = "";
            aux.clear();
            i++;
        }
        else val += permutacao[i];

        if(i+1 == permutacao.size()) {
            aux.push_back(stoi(val));
            result.push_back(aux);
        }
        
    }
    return result;
}

void check(string fim, string permutacao, int nro_produtos, bool& flag, vector<string> nomes) {

    vector<vector<int>> valores = preProcessa(permutacao);

    int aux = 0;
    string result;

    for(int i = 0; i < nro_produtos + 1; i++) {
        if(!flag) break;
        int sum = 0;
        for(int j = 0; j < valores.size(); j++) sum += valores[j][i];

        string val;
        for(int j = aux; j < fim.size(); j++) {
            val += fim[j];
            aux++;
            if(stoi(val) == sum) {
                result += val + ' ';
                break;
            }
            else if(stoi(val) > sum) {
                flag = false;
                break;
            }
        }
    }

    if(flag) {
        for(int i = 0; i < valores.size(); i++) {
            cout << nomes[i] << ' ';
            for(int j = 0; j < valores[i].size(); j++) {
                cout << valores[i][j];
                if(j+1 != valores[i].size()) cout << ' ';
            }
            cout << endl;
        }
        result.pop_back();
        cout << "TP " << result << endl; 
    }
}

int main() {

    int nro_casos;
    cin >> nro_casos;

    for(int i = 0; i < nro_casos; i++) {
        string cabecalho;
        cin >> cabecalho;

        int nro_produtos = 0;
        for(int j = 0; j < cabecalho.size(); j+=2) {
            if(cabecalho[j] == 'P') {
                cout << 'P' << nro_produtos+1 << ' ';
                nro_produtos++; 
            }
            else if(cabecalho[j] == 'T') {
                cout << "Totals\n";
                break;
            }
        }

        vector<string> nomes;
        vector<string> valores;
        string fim;

        while(true) {
            string linha;
            cin >> linha;
            if(linha[0] == 'T' && linha[1] == 'P') {
                for(int j = 2; j < linha.size(); j++) fim += linha[j];
                break;
            }

            int aux = 0;
            string nome;
            for(int j = 0; j < linha.size(); j++) {
                if(isdigit(linha[j])) {
                    break;
                }
                nome += linha[j];
                aux++;
            }
            nomes.push_back(nome);

            string val;
            for(int j = aux; j < linha.size(); j++) {
                val += linha[j];
            }
            valores.push_back(val);
        }
        
        vector<int> possibs_maior;
        vector<string> possibs_fins;
        gerarCombinacoes(possibs_fins, "", fim, nro_produtos, 0, possibs_maior, nro_produtos, false);

        possibs_maior.resize(nro_produtos, INT_MIN);
        for(int j = 0; j < possibs_fins.size(); j++) {
            string aux;
            int it = 0;
            for(int k = 1; k < possibs_fins[j].size(); k++) {
                if(possibs_fins[j][k] == ' ') {
                    if(stoi(aux) > possibs_maior[it]) possibs_maior[it] = stoi(aux);
                    aux = "";
                    it++;
                }
                else aux += possibs_fins[j][k];
            }
        }

        vector<vector<string>> possibs_vals(valores.size());
        for(int j = 0; j < valores.size(); j++) {
            gerarCombinacoes(possibs_vals[j], "", valores[j], nro_produtos, 0, possibs_maior, nro_produtos, true);
        }

        vector<string> permutacoes = gerarPermutacoes(possibs_vals);

        bool flag = true;
        for(int j = 0; j < permutacoes.size(); j++) {
            check(fim, permutacoes[j], nro_produtos, flag, nomes);
            if(flag) break;
            flag = true;
        }  
    }

    return 0;
}