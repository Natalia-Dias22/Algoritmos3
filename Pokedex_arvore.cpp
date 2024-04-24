#include <iostream>
#include <string.h>
#include <list>
#include <climits>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
using namespace std;

// Definição da estrutura para representar uma aresta
struct no {
    int vertice; // vértice adjacente
    int peso;    // peso da aresta
};

struct Cidades {
	int codigo;
	string nome;
	char temCentroPokemon;
};

// Estrutura para representar um Pokemon
typedef struct Pokemon {
    char nome[50];
    char tipo[20];
    int numero;
    int posx;
    int posy;
} Pokemon;

// Estrutura para o nó de uma árvore binária
typedef struct Arvore {
    Pokemon *pokemon;
    struct Arvore* esquerda;
    struct Arvore* direita;
} Arvore;

// Função para criar uma aresta entre os vértices u e v com peso p
void cria_aresta(list<no> adj[], int u, int v, int p, int orientado) {
    no x;
    x.vertice = v;
    x.peso = p;
    adj[u].push_back(x); // Adiciona a aresta na lista de adjacência do vértice u
    if (orientado == 0) {
        x.vertice = u;
        adj[v].push_back(x); // Adiciona a aresta na lista de adjacência do vértice v (se não for orientado)
    }
}

// Função para calcular o menor caminho utilizando o algoritmo de Dijkstra
void dijkstra(list<no> adj[], int nVertices, int codigo_atual, int codigo_final) {

    // Vetor para rastrear os vértices incluídos na MST
    bool intree[nVertices];
    fill_n(intree, nVertices, false);
    // Vetor para armazenar as distâncias mínimas
    int distance[nVertices];
    // Vetor para armazenar os pais na MST
    int parent[nVertices];

    for(int i=0;i<nVertices;i++){
        intree[i]=false;
        distance[i]=INT_MAX;
        parent[i]=-1;
    }

    distance[codigo_atual] = 0; // Define a distância do vértice inicial como 0
    int v = codigo_atual;        // Inicia do vértice de início

    // Algoritmo de Dijkstra
    while (!intree[v]) {
        intree[v] = true; // Marca o vértice como incluído na MST

        // Itera sobre todas as arestas adjacentes ao vértice atual
        for (list<no>::iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
            int dest = it->vertice;
            int weight = it->peso;

            // Se o vértice não estiver na MST e a distância mínima até ele for atualizável
            if (!intree[dest] && distance[dest] > distance[v] + weight) {
                distance[dest] = distance[v] + weight; // Atualiza a distância mínima
                parent[dest] = v; // Atualiza o pai
            }
        }

        // Encontra o vértice mais próximo que não está na MST
        v = 0;
        int dist = INT_MAX;
        for (int u = 0; u < nVertices; ++u) {
            if (!intree[u] && dist > distance[u]) {
                dist = distance[u];
                v = u;
            }
        }
    }

    // Constrói o vetor caminho
    int caminho[nVertices];
    int at = codigo_final;
    int index = 0;
    while (at != -1) {
        caminho[index++] = at;
        at = parent[at];
    }

    // Imprime o menor caminho
    cout << "Menor caminho: ";
    for (int i = index - 1; i >= 0; --i) {
        cout << caminho[i];
        if (i > 0)
            cout << " ";
    }
    cout << endl;

    // Calcula o custo do caminho
    int custoCaminho = 0;
    for (int i = index - 1; i > 0; --i) {
        int u = caminho[i];
        int v = caminho[i - 1];
        for (list<no>::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
            if (it->vertice == v) {
                custoCaminho += it->peso;
                break;
            }
        }
    }
    cout << "Custo: " << custoCaminho << endl;
}

/*================FUNÇOES REFERENTE ÁRVORE BINÁRIA DE BUSCA===================*/
// Função para criar um novo nó na árvore binária
Arvore* criarNo(Pokemon *pokemon) {
	Arvore* novoNo = (Arvore*)malloc(sizeof(Arvore));
    novoNo->pokemon = pokemon;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um Pokémon na árvore binária mantendo a ordem alfabética pelo nome
Arvore* inserirPorNome(Arvore* raiz, Pokemon *pokemon) {
    if (raiz == NULL) {
        return criarNo(pokemon);
    }
    // Comparar os nomes dos Pokémons para decidir em qual lado inserir
    int comparacao = strcmp(pokemon->nome, raiz->pokemon->nome);
    if (comparacao <= 0) {
        raiz->esquerda = inserir(raiz->esquerda, pokemon);
    } else if (comparacao > 0) {
        raiz->direita = inserir(raiz->direita, pokemon);
    }
    return raiz;
}

// Função para realizar o percurso em ordem (inorder traversal) e imprimir os Pokémons em ordem alfabética
void inorderPorNome(Arvore* raiz) {
    if (raiz != NULL) {
        inorder(raiz->esquerda);
        cout << "Nome: " << raiz->pokemon->nome <<endl;
        cout << "Tipo: " << raiz->pokemon->tipo <<endl;
        cout << "Código na Pokedex: " <<raiz->pokemon->numero <<endl;
        cout << "Posição: x= " << raiz->pokemon->posx <<" y= " << raiz->pokemon->posy<<endl;
        inorder(raiz->direita);
    }
}

int main()
{
	setlocale(LC_ALL,"portuguese");
    // Variáveis
    int contador_cidades = 0;
    int orientado = 1;
    int codigo_atual; 
    int codigo_final;
    int u; // Vértice de origem
    int v; // Vértice de destino
    int p; // Peso    
    Arvore* raiz = NULL; // Criar a raiz da árvore binária
    int i = 0; // Inicializa a variável i

    Cidades city[10000];
    list<no> adj[10000];
    
    // Loop principal do programa
    while (true)
    {
    	system("cls");
        cout << "Bem-vindo a sua Pokedex" << endl;
        cout << "Escolha uma das funcoes disponiveis" << endl;
        cout << "1 - Cadastrar uma cidade" << endl;
		cout << "2 - Mostrar o Centro Pokemon mais próximo" << endl;
        cout << "3 - Cadastrar um Pokemon" << endl;
		cout << "4 - Listar os Pokemons por ordem alfabética dos nome" << endl;
        cout << "5 - Buscar Pokémon pelo Nome" << endl;
        cout << "6 - Listar os Pokemons por ordem alfabética dos tipos"<<endl;
        cout << "7 - Contar Pokemons cadastrados por tipo"<<endl;
        cout << "8 - Mostrar Pokemons no alcance da Pokedex"<<endl;
        cout << "0 - Desligar Pokedex" << endl;
        cout << "Opcao: ";
        
        int opcao;
        cin >> opcao;

        // Switch para escolher a opção do menu
        switch(opcao)
        {
            case 0:
                exit(0); // Sai do programa
                break;
            case 1: // Cadastro de Cidade
                do
                {    
                   i++;
                   cout << "Digite o código da cidade: ";
                   cin >> city[i].codigo;
                   cout << "Digite o nome da cidade: ";
                   cin.ignore();
                   getline(cin, city[i].nome);
                   cout << "A cidade tem Centro Pokemon: S/N: ";
                   cin >> city[i].temCentroPokemon;
        
                   contador_cidades++;
        
                   cout<<"Deseja continuar cadastrando cidades? (0 - Sim / 1 - Não): ";
                   cin>>opcao;
                } while(opcao != 1);
                break;
            
			case 2:
				cout << "Código da cidade atual: ";
                cin >> codigo_atual;

                cout << "Esses são os códigos das cidades que possuem Centro de Pokemon: ";
                for (int j = 1; j <= contador_cidades; j++) // Início do loop a partir de 1
                {
                    if (city[j].temCentroPokemon == 'S') // Ajuste no índice para city
                    {
                        cout << city[j].codigo << " ";
                    }
                }
                cout << endl;

                cout << "Código de destino (Cidade que possui Centro de Pokemon): ";
                cin >> codigo_final;

                cout << "Insira as arestas do grafo (origem destino peso), digite -1 -1 -1 para terminar:" << endl;
                while (true)
                {
                  cin >> u >> v >> p;
                  if (u == -1 && v == -1 && p == -1)
                 {
                   break;
                 }

                 cria_aresta(adj, u, v, p, orientado); // Cria a aresta entre os vértices u e v com peso p
                }

                dijkstra(adj, contador_cidades, codigo_atual, codigo_final);

                break;

            case 3: // Cadastro de Pokemon
				Pokemon *pkm;
				pkm = new Pokemon;
				
                cout << "Digite o nome do Pokemon: ";
                cin >> pkm->nome;
                cout << "Digite o tipo do Pokemon: ";
                cin >> pkm->tipo;
                cout << "Digite o numero do Pokemon: ";
                cin >> pkm->numero;
                cout << "Digite a coordenada x do Pokemon: ";
                cin >> pkm->posx;
                cout << "Digite a coordenada y do Pokemon: ";
                cin >> pkm->posy;
                raiz = inserirPorNome(raiz,pkm);
                pkm++;
                break;

            case 4: // Listar o Pokemon cadastrado por ordem alfabética dos nomes
				cout << "Lista de Pokemons Ordenados por ordem alfabética de Nomes"<<endl;
            	inorderPorNome(raiz);
            	cout<<"/n";
                break;
            
            case 5:	//Buscar pokemon pelo nome
            	break;
            
            case 6:	// Listar o Pokemon cadastrado por ordem alfabética dos tipos
				cout << "Lista de Pokemons Ordenados por ordem alfabética de Tipos"<<endl;
            	break;
            
            case 7:
            	break;
            
            case 8:
            	break;

            default: // Opção inválida
                cout << "Opção Inválida" << endl;
                break;
        }

        // Verifica se o usuário deseja voltar ao menu principal
        cout << "Deseja voltar ao menu principal? (S/N)" << endl;
        char menu;
        cin >> menu;
        if (toupper(menu) == 'N') // Converte a entrada para maiúsculas e verifica se é 'N'
        {
                exit(0); // Sai do programa
        }    
    }
    return 0;
}

/*
        Tema:  POKÉDEX
        Nomes:  DOUGLAS OTANI, NATALIA APARECIDA, PAULO HENRIQUE
        
*/