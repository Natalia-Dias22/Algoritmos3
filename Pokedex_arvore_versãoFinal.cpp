#include <iostream>
#include <string.h>
#include <list>
#include <climits>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <queue>
#include <cmath>
using namespace std;

// Defini??o da estrutura para representar uma aresta
struct no {
    int vertice; // v?rtice adjacente
    int peso;    // peso da aresta
};

struct Cidades {
    int codigo;
    string nome;
    char temCentroPokemon;
};

// Estrutura para representar um Pokemon
typedef struct Pokemon {
    string nome;
    string tipo;
    int numero;
    int posx;
    int posy;
} Pokemon;

struct Pokedex
{
	int posx,posy;
};

// Fun??o para criar uma aresta entre os v?rtices u e v com peso p
void cria_aresta(list<no> adj[], int u, int v, int p, int orientado) {
    no x;
    x.vertice = v;
    x.peso = p;
    adj[u].push_back(x); // Adiciona a aresta na lista de adjac?ncia do v?rtice u
    if (orientado == 0) {
        x.vertice = u;
        adj[v].push_back(x); // Adiciona a aresta na lista de adjac?ncia do v?rtice v (se n?o for orientado)
    }
}

// Fun??o para calcular o menor caminho utilizando o algoritmo de Dijkstra
void dijkstra(list<no> adj[], int nVertices, int codigo_atual, int codigo_final) {
    // Vetor para rastrear os v?rtices inclu?dos na MST
    bool intree[nVertices];
    fill_n(intree, nVertices, false);
    // Vetor para armazenar as dist?ncias m?nimas
    int distance[nVertices];
    // Vetor para armazenar os pais na MST
    int parent[nVertices];

    for (int i = 0; i < nVertices; i++) {
        intree[i] = false;
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    distance[codigo_atual] = 0; // Define a dist?ncia do v?rtice inicial como 0
    int v = codigo_atual;        // Inicia do v?rtice de in?cio

    // Algoritmo de Dijkstra
    while (!intree[v]) {
        intree[v] = true; // Marca o v?rtice como inclu?do na MST

        // Itera sobre todas as arestas adjacentes ao v?rtice atual
        for (list<no>::iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
            int dest = it->vertice;
            int weight = it->peso;

            // Se o v?rtice n?o estiver na MST e a dist?ncia m?nima at? ele for atualiz?vel
            if (!intree[dest] && distance[dest] > distance[v] + weight) {
                distance[dest] = distance[v] + weight; // Atualiza a dist?ncia m?nima
                parent[dest] = v; // Atualiza o pai
            }
        }

        // Encontra o v?rtice mais pr?ximo que n?o est? na MST
        v = 0;
        int dist = INT_MAX;
        for (int u = 0; u < nVertices; ++u) {
            if (!intree[u] && dist > distance[u]) {
                dist = distance[u];
                v = u;
            }
        }
    }

    // Constr?i o vetor caminho
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

/*================FUN?OES REFERENTE ?RVORE BIN?RIA DE BUSCA===================*/
// Estrutura para o nó de uma Árvore binária
struct Arvore {
    Pokemon pokemon;
    Arvore* esquerda;
    Arvore* direita;
};

typedef Arvore* arvoreptr;

// Funçãoo para inserir um Pokemon na árvore binária mantendo a ordem alfabética pelo nome
void inserirPorNome(arvoreptr &raiz, Pokemon pokemon) {
    if (raiz == NULL){
        raiz = new Arvore;
        raiz->pokemon = pokemon;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
    }
    else if(pokemon.nome < raiz->pokemon.nome)
    	inserirPorNome(raiz->esquerda,pokemon);
    else
		inserirPorNome(raiz->direita,pokemon);
}

void inserirPorTipo(arvoreptr &raiz, Pokemon pokemon) {
    if (raiz == NULL){
        raiz = new Arvore;
        raiz->pokemon = pokemon;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
    }
    else if(pokemon.tipo < raiz->pokemon.tipo)
    	inserirPorTipo(raiz->esquerda,pokemon);
    else
		inserirPorTipo(raiz->direita,pokemon);
}

arvoreptr buscarPokemon(arvoreptr raiz, string nome){
	if(raiz == NULL)
		return NULL;
	else if(nome == raiz->pokemon.nome)
		return raiz;
	else if(nome < raiz->pokemon.nome)
		return buscarPokemon(raiz->esquerda,nome);
	else
		return buscarPokemon(raiz->direita,nome);
}

void inOrder(arvoreptr raiz){
	if(raiz != NULL){
		inOrder(raiz->esquerda);
		cout << "Nome do Pokemon: " << raiz->pokemon.nome<<endl;
		cout << "Tipo do Pokemon: " << raiz->pokemon.tipo<<endl;
		cout << "Código do Pokemon na Pokedex: " << raiz->pokemon.numero<<endl;
		cout << "Coordenadas do Pokemon: x= " << raiz->pokemon.posx <<" y= "<<raiz->pokemon.posy<<endl;
		cout << endl;
		inOrder(raiz->direita);
	}
}

void destruirArvore(arvoreptr &raiz){
	if(raiz != NULL){
		destruirArvore(raiz->esquerda);
		destruirArvore(raiz->direita);
		delete raiz;
	}
	raiz = NULL;
}

void emNivel(arvoreptr raiz, Pokedex pokedex){
	float dist,difPosX,difPosY;
	int numPokemons = 0;
	if(raiz != NULL){
		queue<arvoreptr> fila;
		fila.push(raiz);
		while(!fila.empty()){
			arvoreptr atual = fila.front();
			fila.pop();
			difPosX = pow((pokedex.posx - atual->pokemon.posx),2);
			difPosY = pow((pokedex.posy - atual->pokemon.posy),2);
			dist = sqrt(difPosX+difPosY);
			if(dist<=100)
				numPokemons++;
			if(atual->esquerda!=NULL)
				fila.push(atual->esquerda);
			if(atual->direita!=NULL)
				fila.push(atual->direita);
		}
	}
	cout << "Existem " << numPokemons << " pokémons em um raio de 100 metros da Pokedex"<<endl;
}

int main() {
    setlocale(LC_ALL, "portuguese");
    // Vari?veis
    int contador_cidades = 0;
    int orientado = 1;
    int codigo_atual;
    int codigo_final;
    int u; // V?rtice de origem
    int v; // V?rtice de destino
    int p; // Peso
    int i = 0; // Inicializa a vari?vel i
	arvoreptr arvorePorNome = NULL;
	arvoreptr arvorePorTipo = NULL;
	arvoreptr resultado;
	Pokemon pkm;
	string nomePokemon;
	Pokedex Pokedex;
	Cidades city[10000];
    list<no> adj[10000];

    // Loop principal do programa
    while (true) {
        system("cls");
        cout << "Bem-vindo a sua Pokedex" << endl;
        cout << "Escolha uma das funcoes disponiveis" << endl;
        cout << "1 - Cadastrar uma cidade" << endl;
        cout << "2 - Mostrar o Centro Pokemon mais pr?ximo" << endl;
        cout << "3 - Cadastrar um Pokemon" << endl;
        cout << "4 - Listar os Pokemons por ordem alfab?tica dos nomes" << endl;
        cout << "5 - Buscar Pok?mon pelo Nome" << endl;
        cout << "6 - Listar os Pokemons por ordem alfab?tica dos tipos" << endl;
        cout << "7 - Contar Pokemons cadastrados por tipo" << endl;
        cout << "8 - Mostrar Pokemons no alcance da Pokedex" << endl;
        cout << "0 - Desligar Pokedex" << endl;
        cout << "Opcao: ";

        int opcao;
        cin >> opcao;

        // Switch para escolher a op??o do menu
        switch (opcao) {
        
		case 0:
            system("cls");
            exit(0); // Sai do programa
            destruirArvore(arvorePorNome);
            destruirArvore(arvorePorTipo);
        
		case 1: // Cadastro de Cidade
            do {
                i++;
                cout << "Digite o c?digo da cidade: ";
                cin >> city[i].codigo;
                cout << "Digite o nome da cidade: ";
                cin.ignore();
                getline(cin, city[i].nome);
                cout << "A cidade tem Centro Pokemon: S/N: ";
                cin >> city[i].temCentroPokemon;

                contador_cidades++;

                cout << "Deseja continuar cadastrando cidades? (0 - Sim / 1 - N?o): ";
                cin >> opcao;
            } while (opcao != 1);
			break;

        case 2:
            system("cls");
            cout << "C?digo da cidade atual: ";
            cin >> codigo_atual;

            cout << "Esses s?o os c?digos das cidades que possuem Centro de Pokemon: ";
            for (int j = 1; j <= contador_cidades; j++) // In?cio do loop a partir de 1
            {
                if (city[j].temCentroPokemon == 'S') // Ajuste no ?ndice para city
                {
                    cout << city[j].codigo << " ";
                }
            }
            cout << endl;

            cout << "C?digo de destino (Cidade que possui Centro de Pokemon): ";
            cin >> codigo_final;

            cout << "Insira as arestas do grafo (origem destino peso), digite -1 -1 -1 para terminar:" << endl;
            while (true) {
                cin >> u >> v >> p;
                if (u == -1 && v == -1 && p == -1) {
                    break;
                }

                cria_aresta(adj, u, v, p, orientado); // Cria a aresta entre os v?rtices u e v com peso p
            }

            dijkstra(adj, contador_cidades, codigo_atual, codigo_final);
			break;

        case 3: // Cadastro de Pokemon
            system("cls");
            cout << "Digite o nome do Pokemon: ";
			cin >> pkm.nome;
            cout << "Digite o tipo do Pokemon: ";
            cin >> pkm.tipo;
            cout << "Digite o numero do Pokemon: ";
            cin >> pkm.numero;
            cout << "Digite a coordenada x do Pokemon: ";
            cin >> pkm.posx;
            cout << "Digite a coordenada y do Pokemon: ";
            cin >> pkm.posy;
            inserirPorNome(arvorePorNome,pkm);
            inserirPorTipo(arvorePorTipo,pkm);
			break;
		
		case 4:
            system("cls");
			inOrder(arvorePorNome);
			break;
		
		case 5:
            system("cls");
			cout << "Digite o nome do Pokemon que deseja buscar: ";
			cin >> nomePokemon;
			resultado = buscarPokemon(arvorePorNome,nomePokemon);
			if(resultado == NULL)
				cout << "Pokémon não encontrado!"<<endl;
			else
				cout << "Pokémon encontrado!"<<endl;
			break;
		
		case 6:
			system("cls");
            inOrder(arvorePorTipo);
			break;
		
        case 8:
        	cout << "Entre com a posição x da Pokedex: ";
        	cin >> Pokedex.posx;
     		cout << "Entre com a posição y da Pokedex: ";
        	cin >> Pokedex.posy;
        	emNivel(arvorePorNome,Pokedex);
        	break;
        }
        
        // Verifica se o usu?rio deseja voltar ao menu principal
        cout << "Deseja voltar ao menu principal? (S/N)" << endl;
        char menu;
        cin >> menu;
        if (toupper(menu) == 'N') // Converte a entrada para mai?sculas e verifica se ? 'N'
        {
            exit(0); // Sai do programa
            destruirArvore(arvorePorNome);
            destruirArvore(arvorePorTipo);
        }
    }
    return 0;
}

/*
    Tema:  POK?DEX
    Nomes:  DOUGLAS OTANI, NATALIA APARECIDA, PAULO HENRIQUE

*/
