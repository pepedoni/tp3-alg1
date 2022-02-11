#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int calculaSomaPosicao(int linha, int coluna, vector<vector<int>> &macieiras, int totalAcumulado, int numFilieiras, int numMacieiras, vector<vector<int>> &resultados,  vector<vector<vector<int>>> &melhoresCaminhos) {

  if(resultados[linha][coluna] == -1) {
    if(linha == 0) {
      resultados[linha][coluna] = macieiras[linha][coluna];
      return macieiras[linha][coluna];
    }
    int esquerda = 0;
    int direita = 0;
    int meio = macieiras[linha - 1][coluna];

    int posEsquerda = coluna - 1;
    int posMeio = coluna;
    int posDireita = coluna + 1;

    int calculoEsquerda = 0;
    int calculoDireita = 0;
    int totalMeio = totalAcumulado + meio;
    
    int calculoMeio = calculaSomaPosicao(linha - 1, posMeio, macieiras, totalMeio, numFilieiras, numMacieiras, resultados, melhoresCaminhos);

    if(coluna != 0) {
      esquerda = macieiras[linha - 1][posEsquerda];
      int totalEsquerda = totalAcumulado + esquerda;
      calculoEsquerda = calculaSomaPosicao(linha - 1, posEsquerda, macieiras, totalEsquerda, numFilieiras, numMacieiras, resultados, melhoresCaminhos);
    } 
    if (coluna != (numMacieiras - 1)) {
      int totalDireita = totalAcumulado + direita;
      direita = macieiras[numFilieiras - 1][posDireita];
      calculoDireita = calculaSomaPosicao(linha - 1, posDireita, macieiras, totalDireita, numFilieiras, numMacieiras, resultados, melhoresCaminhos);
    }

    if(calculoEsquerda >= calculoMeio) {
      if(calculoEsquerda >= calculoDireita) {
        resultados[linha][coluna] = macieiras[linha][coluna] + calculoEsquerda;
        melhoresCaminhos[linha][coluna].insert(melhoresCaminhos[linha][coluna].end(), melhoresCaminhos[linha - 1][posEsquerda].begin(), melhoresCaminhos[linha - 1][posEsquerda].end());
      } else {
        resultados[linha][coluna] = macieiras[linha][coluna] + calculoDireita;
        melhoresCaminhos[linha][coluna].insert(melhoresCaminhos[linha][coluna].end(), melhoresCaminhos[linha - 1][posDireita].begin(), melhoresCaminhos[linha - 1][posDireita].end());
      }
    } else if(calculoMeio >= calculoDireita) {
      resultados[linha][coluna] = macieiras[linha][coluna] + calculoMeio;
      melhoresCaminhos[linha][coluna].insert(melhoresCaminhos[linha][coluna].end(), melhoresCaminhos[linha - 1][posMeio].begin(), melhoresCaminhos[linha - 1][posMeio].end());
    } else {
      resultados[linha][coluna] = macieiras[linha][coluna] + calculoDireita;
      melhoresCaminhos[linha][coluna].insert(melhoresCaminhos[linha][coluna].end(), melhoresCaminhos[linha - 1][posDireita].begin(), melhoresCaminhos[linha - 1][posDireita].end());
      
    }
    
  } 
  return resultados[linha][coluna];
}

int main() {
  int numFilieiras = 0, numMacieiras = 0;
  
  vector<vector<int>> macieiras ;

  // Obtem os dados do grid
  scanf("%d %d", &numFilieiras, &numMacieiras);
  vector<vector<int>> resultados;
  vector<vector<int>> melhoresCaminho;
  vector<vector<vector<int>>> melhoresCaminhos;
  // Le as macieiras
  for(int i=0; i < numFilieiras; i++){
    vector<int> filaMacieira;
    vector<int> resultadoLinha;
    vector<vector<int>> melhorCaminho;
    for(int j=0; j < numMacieiras; j++) {
      // Le valor das maças
      int macieira = 0;
      scanf("%d", &macieira);
      filaMacieira.push_back(macieira);

      // Inicializa as variaveis
      vector<int> preencheMelhorCaminho = {j};
      melhorCaminho.push_back(preencheMelhorCaminho);
      resultadoLinha.push_back(-1);
    
    }
    melhoresCaminhos.push_back(melhorCaminho);
    resultados.push_back(resultadoLinha);
    macieiras.push_back(filaMacieira);
  } 
  int melhorColunaCaminho = 0;
  int maxValor = 0;
  
  for(int j=0; j < numMacieiras; j++) {
    int valorPosicao = calculaSomaPosicao(numFilieiras - 1, j, macieiras, macieiras[numFilieiras - 1][j], numFilieiras, numMacieiras, resultados, melhoresCaminhos);
    if(valorPosicao > maxValor) {
      maxValor = valorPosicao;
      melhorColunaCaminho = j;
    }
    
  }
 
  vector<int> caminhoPrint = melhoresCaminhos[numFilieiras - 1][melhorColunaCaminho];
  printf("%d\n", maxValor);
  for(std::vector<int>::size_type k = caminhoPrint.size() - 1; k < caminhoPrint.size(); k--) {
    if(k != 0) {
      printf("%d ", caminhoPrint[k]);
    } else {
      printf("%d", caminhoPrint[k]);
    }
  }
   
}