/**
 * @file main.cpp
 * @author Atilio G. Luiz
 * @brief Projeto Final - ED --- Arquivo de Exemplo
 * @version 0.1
 * @date 2023-06-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <fstream> // cabecalho para leitura e escrita de arquivo
#include <chrono>  // cabecalho para medicao de tempo 
#include "List.h"
using namespace std;

/** 
 * Funcao que gera arquivos binarios, cada um contendo numeros aleatorios.
 * Essa funcao recebe um array 'vetor_tam' que contem todos os tamanhos N
 * de vetores aleatorios que serao gerados. O parametro 'num_iteracoes' eh
 * o tamanho do array 'vetor_tam' 
 */
void gera_dados(const int& num_iteracoes, const int vetor_tam[]) 
{
	for(int n = 0; n < num_iteracoes; ++n) {
		// para cada tamanho n, sao gerados 5 vetores de tamanho n com numeros aleatorios
		for(int semente = 0; semente < 5; semente++) {	
			std::string nome_arquivo = "dados/random"+std::to_string(n)+"_"+std::to_string(semente)+".dat";
			ofstream fout(nome_arquivo.c_str(), ios::binary);
			srand(time(NULL)); // gera semente
			int r;
			int tamanho_vetor = vetor_tam[n];
			for(int i = 0; i < tamanho_vetor; i++) 
			{
				r = rand(); // gera numero aleatorio
				fout.write((char*) &r, sizeof(r)); // escreve numero r no arquivo binario
			}
			fout.close();
		}
	}
}

// ------------------------------------------------------------------

/*
 * Recebe um vetor de inteiros A[0..n-1] como argumento e o preenche
 * com os n inteiros contidos no arquivo binario de mesmo nome que a 
 * string nomeArquivo
 */
void ler_dados(int n, int A[], const char *nomeArquivo) 
{	
	ifstream input_file(nomeArquivo, ios::binary); // abre arquivo binario para leitura
	for (int i = 0; i < n; i++) 
	{
		input_file.read((char*) &A[i], sizeof(int)); // ler um inteiro do arquivo e guarda na posicao A[i]
	}
	input_file.close(); // fecha o arquivo de leitura
}


// ----------------------------------------------------------------------------
// Funcao Principal
int main() 
{ 
	// Os tamanhos dos vetores a serem testados estao guardados neste vetor 'tam'	
	// tamanhos reais para o projeto
	/*const int tam[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 
	                   11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 
					   20000, 21000, 22000, 23000, 24000, 25000, 26000, 27000, 28000, 
					   29000, 30000, 31000, 32000, 33000, 34000, 35000, 36000, 37000, 
					   38000, 39000, 40000, 41000, 42000, 43000, 44000, 45000, 46000, 
					   47000, 48000, 49000, 50000, 51000, 52000, 53000, 54000, 55000, 
					   56000, 57000, 58000, 59000, 60000, 61000, 62000, 63000, 64000, 
					   65000, 66000, 67000, 68000, 69000, 70000, 71000, 72000, 73000, 
					   74000, 75000, 76000, 77000, 78000, 79000, 80000, 81000, 82000, 
					   83000, 84000, 85000, 86000, 87000, 88000, 89000, 90000, 91000, 
					   92000, 93000, 94000, 95000, 96000, 97000, 98000, 99000, 100000};*/
	
	// tamanho reduzido apenas para teste
	const int tam[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 
	                   11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 
					   20000};
	
	const int TOTAL_N = sizeof(tam)/sizeof(tam[0]); // determina tamanho do vetor 'tam'
	
	// ------------------------------------------------------------
	// Etapa 1: Gerar arquivos contendo numeros aleatorios
	// Os arquivos sao gerados e salvos na pasta com nome 'dados'
	gera_dados(TOTAL_N, tam);
	
	// ------------------------------------------------------------
	// Etapa 2 - Execucao do CocktailSort
	// Para cada arquivo gerado na etapa 1, ler o arquivo e popular
	// um vetor de inteiros com os dados lidos.
	std::ofstream ofs("resultados/resultadoCocktail.txt", std::ofstream::out); // abre arquivo de resultados do cocktail
	
	for(int iteracao = 0; iteracao < TOTAL_N; iteracao++) 
	{	
		long double duracao_media_cocktail = 0.0;
		const int tamanho_vetor = tam[iteracao]; // pega o tamanho do vetor para esta iteracao
		int vetor[tamanho_vetor]; // cria vetor a ser ordenado
		
		// Para cada tamanho de vetor, a funcao gera_dados() gerou 5 vetores diferentes. 
		// Cada um usou uma semente diferente. Agora, vamos ler cada um desses vetores, 
		// Chamar o cocktail sort para ordena-los e, entao, calcular o tempo medio de 
		// execucao dessas cinco chamadas e depois salvar esse tempo medio em arquivo.
		for(int semente = 0; semente < 5; semente++) 
		{	
			string nome_arquivo = "dados/random"+std::to_string(iteracao)+"_"+std::to_string(semente)+".dat";
		
			ler_dados(tamanho_vetor, vetor, nome_arquivo.c_str());
			
			// CocktailSort ------------------------------------------------------
			// obtendo o tempo inicial
			auto ini = std::chrono::high_resolution_clock::now();
		
			CocktailSort(tamanho_vetor, vetor); // ordena o vetor usando o CocktailSort
		
			// obtendo o tempo final
			auto fim = std::chrono::high_resolution_clock::now();
		
			// obtendo a duracao total da ordenacao
			auto duracao_cocktail = std::chrono::duration_cast<std::chrono::microseconds>(fim - ini).count();
			
			duracao_media_cocktail += duracao_cocktail;
			
		}
		
		duracao_media_cocktail = duracao_media_cocktail / 5.0;
		cout << "[Cocktail] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_cocktail << " microssegundos" << endl;
		ofs << tamanho_vetor << " " << duracao_media_cocktail << "\n"; // grava no arquivo de resultados do cocktail
	}
	
	ofs.close(); // fecha arquivo de resultados do CockTail Sort
	// ------------------------------------------------------------
	
	
	// ------------------------------------------------------------
	// Etapa 3 - Execução do BubbleSort
	// Para cada arquivo gerado na etapa 1, ler o arquivo e popular
	// um vetor de inteiros com os dados lidos.
	std::ofstream ofs2("resultados/resultadoBubble.txt", std::ofstream::out ); // abre arquivo de resultados do bubblesort
	
	for(int iteracao = 0; iteracao < TOTAL_N; iteracao++) {
		
		long double duracao_media_bubble = 0.0;
		const int tamanho_vetor = tam[iteracao]; // pega o tamanho do vetor para esta iteracao
		int vetor[tamanho_vetor]; // cria vetor a ser ordenado
		
		// Para cada tamanho de vetor, a funcao gera_dados() gerou 5 vetores diferentes. 
		// Cada um usou uma semente diferente. Agora, vamos ler cada um desses vetores, 
		// Chamar o bubblesort para ordena-los e, entao, calcular o tempo medio de 
		// execucao dessas cinco chamadas e depois salvar esse tempo medio em arquivo.
		for(int semente = 0; semente < 5; semente++) 
		{	
			string nome_arquivo = "dados/random"+std::to_string(iteracao)+"_"+std::to_string(semente)+".dat";
		
			ler_dados(tamanho_vetor, vetor, nome_arquivo.c_str());
			
			// BubbleSort ---------------------------------------------------------
			// obtendo o tempo inicial
			auto ini2 = std::chrono::high_resolution_clock::now();
		
			BubbleSort(tamanho_vetor, vetor); // ordena o vetor usando o BubbleSort
		
			// obtendo o tempo final
			auto fim2 = std::chrono::high_resolution_clock::now();
		
			// obtendo a duracao total da ordenacao
			auto duracao_bubble = std::chrono::duration_cast<std::chrono::microseconds>(fim2 - ini2).count();
			
			duracao_media_bubble += duracao_bubble;			
		}	
		
		duracao_media_bubble = duracao_media_bubble / 5.0;
		cout << "[Bubble] N = " << tamanho_vetor << ", tempo medio de execucao = " << duracao_media_bubble << " microssegundos" << endl;
		ofs2 << tamanho_vetor << " " << duracao_media_bubble << "\n"; // grava no arquivo de resultados do bubble
	}
	
	ofs2.close(); // fecha arquivo de resultados do Bubble Sort
	// ------------------------------------------------------------
	
	return 0;
}
