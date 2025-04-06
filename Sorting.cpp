// Aten��o: usa c�digo C++11
// para saber se o seu compilador tem suporte, execute:
// cout << __cplusplus;
// O resultado deve ser 201103L ou maior.
// o do google collab � C++14
// A grande maioria dos compiladores atuais suporta nativamente c++11.
// Outros exigem a configura��o de par�metros de compila��o... Verifique a documenta��o do seu.

#include<iostream>
#include<tuple>
#include<random>
#include<bits/stdc++.h>

//TODO: executar v�rias vezes os algoritmos, com tamanhos diferentes (e.g., 100, 1000 e 10000)

#define MAX 50                                                                  // quantidade de n�meros no array

using namespace std;

typedef int array_size_t;                                                       // Tipo para especificar tamanho do array
typedef int* array_t;                                                           // Tipo para especificar formato do array
typedef std::tuple<int, int> loginfo_t;                                         // armazena contagem de compara��es e trocas
typedef std::mt19937 MyRNG;                                                     // Gerador de n�meros aleat�rios do tipo Mersenne Twister Random Generator

MyRNG rng;                                                                      // gerador de n�meros aleat�rios
uint32_t seed_val;                                                              // semente de gera��o de n�meros

loginfo_t insertion_sort(array_t, array_size_t);
loginfo_t insertion_sortBB(array_t, array_size_t);
loginfo_t shellsort(array_t, array_size_t);
std::tuple<int, int, int> busca_binaria(array_t, int, int, int);                // retorna uma tupla contendo <posicao, qtd de trocas, qtd de compara��es>

int main(void)
{
    // cout << __cplusplus << endl;                                             // verifica vers�o do compilador
    rng.seed(seed_val);                                                         // inicializa semente de gera��o de n�meros aleat�rios
    uniform_int_distribution<> distrib(0, INT_MAX);                             // cria gerador com distribui��o uniforme entre 0 e MAX_INT
    loginfo_t loginfo;                                                          // armazena contadores de compara��es e trocas (ver typedef acima)

    int* array = new int[MAX];                                                  // array din�mico que armazena os n�meros

    // testar com as 3 vers�es de array (aleat�rio, crescente e decrescente):
    for(auto i=0;i<MAX;i++) array[i] = distrib(rng);                         // gera n�meros aleat�rios para o array
    //for(auto i=0; i<MAX; i++) array[i] = i;                                   // gera n�meros em ordem crescente
    //for(auto i=0;i<MAX;i++) array[i] = MAX-i;                                   // gera n�meros em ordem decrescente

    cout << "Array gerado: ";
    for(auto i=0;i<MAX;i++) cout << array[i] << " ";

    // TODO: testar os outros algoritmos (insertion_sortBB e shellsort)
    loginfo = insertion_sortBB(array, MAX);

    //TODO: armazenar essas informa��es em um matriz ou hashtable

    cout << endl << "Array ordenado: ";
    for(auto i=0;i<MAX;i++) cout << array[i] << " ";

    cout << endl;
    cout << "Quantidade de trocas: " << get<0>(loginfo) << endl;
    cout << "Quantidade de comparacoes: " << get<1>(loginfo) << endl;

    // TODO: mostrar informa��es de execu��o de todos os algoritmos

    delete[] array;
    return 0;
}

// Fun��o de Inser��o Direta com Busca Linear
loginfo_t insertion_sort(array_t array, array_size_t array_size){
    int trocas = 0, comparacoes = 0;
    for(int i=1;i<array_size;i++){                                              // do segundo ao �ltimo
        auto chave = array[i];                                                  // chave a inserir no subarray ordenado
        auto j = i-1;                                                           // �ltimo elemento do subarray ordenado
        comparacoes = comparacoes + 1;
        while(j >= 0 && array[j] > chave){                                      // busca linear da direita para a esquerda no subarray ordenado
            comparacoes = comparacoes + 1;
            array[j+1] = array[j];
            j = j - 1;
            trocas = trocas + 1;
        }
        if(j+1 != i){
           array[j+1] = chave;
           trocas = trocas + 1;
       }
    }
    return make_tuple(trocas, comparacoes);                                     // retorna quantidade de opera��es
}

loginfo_t insertion_sortBB(array_t array, array_size_t array_size){
   int trocas = 0, comparacoes = 0;
   std::tuple<int, int, int> info;
   int i, local, j, k, elemento;
   for(i = 1; i < array_size; ++i) {
      j = i - 1;
      elemento = array[i];
      info = busca_binaria(array, elemento, 0, j);
      local = get<0>(info);
      trocas += get<1>(info);
      comparacoes += get<2>(info)+1;
      while (j >= local) {
         trocas++;
         array[j+1] = array[j];
         j--;
      }
      if(j+1 != i){
           array[j+1] = elemento;
           trocas = trocas + 1;
       }
   }
    return make_tuple(trocas, comparacoes);                                     // retorna quantidade de opera��es
}

// *****************************************************
//  TODO: Implementa��o dos seus algoritmos (a seguir)

// Faz busca bin�ria do 'elemento' no 'array', entre os �ndices 'inicio' e 'fim'
// retorna posi��o do elemento, quantidade de trocas e quantidade de compara��es
std::tuple<int, int, int> busca_binaria(array_t array, int elemento, int inicio, int fim)
{
    int comparacoes = 0, trocas = 0, meio = (inicio+fim)/2;

    // defina aqui sua vers�o da fun��o de busca bin�ria


    while(true)
    {
        if(inicio == fim || inicio > fim)
            if(elemento < array[meio])
                return make_tuple(meio, trocas, comparacoes);
            else
                return make_tuple(meio+1, trocas, comparacoes);
        if(elemento > array[meio])
            inicio = meio+1;
        else
            fim = meio-1;
        comparacoes++;
        meio = (inicio+fim)/2;
    }
}

loginfo_t shellsort(array_t array, array_size_t array_size)
{
    int trocas = 0, comparacoes = 0;

    // defina aqui sua vers�o da fun��o shellsort

    return make_tuple(trocas, comparacoes);                                     // retorna quantidade de opera��es
}
