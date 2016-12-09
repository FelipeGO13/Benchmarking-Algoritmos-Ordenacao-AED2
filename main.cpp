#include <iostream>
#include "RandomCL.h"
#include <fstream>
#include <time.h>
#include <algorithm> //inicialização do sort C++
#include <stdlib.h> //inicialização do quicksort do C
#include "ordenacao.h" //inicializaçao da biblioteca de ordenação

using namespace std;

void gera_vetor(int seed,int tamanho, unsigned long int vet[]) //função que preenche o vetor com nºs pseudo-aleatórios
{
    int i;
    RandomCL<unsigned long int> gerador(seed);
    for(i=0; i<tamanho; i++) vet[i] = gerador.nextr();
}

int cmpfunc (const void * a, const void * b) //função de comparação do quicksort do C (qsort)
{
   return ( *(int*)a - *(int*)b );
}

int main()
{
    int tamanhos[9] = {10000,30000,90000,270000,810000,2430000,7290000,21870000,65610000};
    int i,j,start,tmili;
    int t = 9; //nº de tamanhos utilizados

    ofstream textoa; //output para um arquivo de texto
    textoa.open ("resultados.txt");

    // ******************************* SORT C++ ******************************* //

   textoa << endl << "@@@@@@@@@@@@@@@@@@ SORT C++ @@@@@@@@@@@@@@@@@@" << endl;
   cout << "SORT C++";

    for(i=0;i<t;i++)
    {
        textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;

        for(j=0;j<6;j++)
        {
            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[i], vet);

            start = clock();

            std::sort(vet,vet+tamanhos[i]);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }

    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

    // **************************** FIM DO SORT C++ *************************** //

    // ****************************** QUICKSORT C ***************************** //

	textoa << endl << "@@@@@@@@@@@@@@@@ QUICKSORT C @@@@@@@@@@@@@@@@@" << endl;
    cout << "QUICKSORT C";

    for(i=0;i<t;i++)
    {
        textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;

        for(j=0;j<6;j++)
        {
            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[i], vet);

            start = clock();

            qsort(vet,tamanhos[i],sizeof(int),cmpfunc);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }

    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

    // ************************** FIM DO QUICKSORT C ************************** //

    // ******************************* HEAPSORT ******************************* //

    textoa << endl << "@@@@@@@@@@@@@@@@@ HEAPSORT @@@@@@@@@@@@@@@@@@@" << endl;
    cout << "HEAPSORT";

    for(i=0;i<t;i++)
    {
        textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;

        for(j=0;j<6;j++)
        {
            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[i], vet);

            start = clock();

            ED::Ordenacao<unsigned long int>::heapsort(vet,tamanhos[i]);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }

    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

    // **************************** FIM DO HEAPSORT *************************** //

    // ************************ QUICKSORT (PIVÔ MEDIANO) ********************** //

    textoa << endl << "@@@@@@@@@@ QUICKSORT (PIVÔ MEDIANO) @@@@@@@@@@" << endl;
    cout << "QUICKSORT (PIVO MEDIANO)";

    for(i=0;i<t;i++)
    {
        textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;

        for(j=0;j<6;j++)
        {
            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[i], vet);

            start = clock();

            ED::Ordenacao<unsigned long int>::quicks_central(vet,0,tamanhos[i]-1);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }

    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

    // ********************* FIM DO QUICKSORT (PIVÔ MEDIANO) ****************** //

    // **************************** SHELLSORT (Shell) ************************* //

    textoa << endl << "@@@@@@@@@@@@@@ SHELLSORT (Shell) @@@@@@@@@@@@@" << endl;
    cout << "SHELLSORT (Shell)";

    for(i=0;i<t;i++)
    {
        textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;

        for(j=0;j<6;j++)
        {
            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[i], vet);

            start = clock();

            ED::Ordenacao<unsigned long int>::shellsort_shell(vet, tamanhos[i]);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }

    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

    // ************************ FIM DO SHELLSORT (Shell) ********************** //

    // **************************** SHELLSORT (Knuth) ************************* //

    textoa << endl << "@@@@@@@@@@@@@@ SHELLSORT (Knuth) @@@@@@@@@@@@@" << endl;
    cout << "SHELLSORT (Knuth)";

    for(i=0;i<t;i++)
    {
        textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;

        for(j=0;j<6;j++)
        {
            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[i], vet);

            start = clock();

            ED::Ordenacao<unsigned long int>::shellsort_knuth(vet, tamanhos[i]);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }

    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

    // ************************ FIM DO SHELLSORT (Knuth) ********************** //

    // ************************** SHELLSORT (Pardons) ************************* //

    textoa << endl << "@@@@@@@@@@@@@ SHELLSORT (Pardons) @@@@@@@@@@@@" << endl;
    cout << "SHELLSORT (Pardons)";

    for(i=0;i<t;i++)
    {
        textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;

        for(j=0;j<6;j++)
        {
            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[i], vet);

            start = clock();

            ED::Ordenacao<unsigned long int>::shellsort_pardons(vet, tamanhos[i]);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }

    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

    // *********************** FIM DO SHELLSORT (Pardons) ********************* //

    // ****************************** MERGESORT ******************************* //

    textoa << endl << "@@@@@@@@@@@@@@@@@ MERGESORT @@@@@@@@@@@@@@@@@@" << endl;
    cout << "MERGESORT";

    for(i=0;i<t;i++)
    {
        textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;

        for(j=0;j<6;j++)
        {
            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[i], vet);

            start = clock();

            ED::Ordenacao<unsigned long int>::mergesort(vet, tamanhos[i]);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }

    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

	// ****************************** SMOOTHSORT *************************** //
	
	textoa << endl << "@@@@@@@@@@@@@@@@@ SMOOTHSORT @@@@@@@@@@@@@@@@@@" << endl;
    cout << "SMOOTHSORT";
    for(i=0;i<t;i++)
    {
        textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;

        for(j=0;j<6;j++)
        {

            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[0], vet);

            start = clock();

            ED::Ordenacao<unsigned long int>::smoothsort(vet, tamanhos[i]);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }

    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	
	
     // ************************** FIM DO SMOOTHSORT *********************//
	 
     // ****************************** FLASHSORT *************************** //


    textoa << endl << "@@@@@@@@@@@@@@@@@ FLASHSORT @@@@@@@@@@@@@@@@@@" << endl;
    cout << "FLASHSORT";
    for(i=0;i<t;i++)
    {
           textoa << endl << "Tamanho do vetor: " << tamanhos[i] << endl << endl;
        for(j=0;j<6;j++)
        {

            unsigned long int *vet = new unsigned long int[tamanhos[i]];
            gera_vetor(j, tamanhos[i], vet);

            start = clock();

            ED::Ordenacao<unsigned long int>::flashsort(vet, tamanhos[i]);

            tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);

            textoa << "seed(" << j << ") -> Execução em " << tmili << " milisegundos." << endl;

            delete(vet);
        }
    }


    cout << " ...... Done!" << endl << endl;
    textoa << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;


     // ************************** FIM DO FLASHSORT *********************//

    // ****************************** FLASHSORT *************************** //

    return 0;
}
