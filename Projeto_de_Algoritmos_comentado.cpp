/* Nessa parte de grafo, fizemos a inserção de cidades no grafo Dijkistra, onde achamos o caminho mais curto da sua cidade atual
para a cidade que possuí centro. Para melhor entendimento, o jogador vai entrar com sua cidade atual, porém no cadastro das cidades
ele coloca quais cidades possuí centro ou não, então depois de falar sua localização é mostrado em quais cidades possui centro
e fica a escolha do jogador escolher qual vai ser o destino. Logo depois disso, é neesário colocar os vértices e as arestas ponderadas,
e o nosso grafo mostra o caminho mais curto para se chegar no seu destino.

Caso de teste
Código - Nome - centro
0 A S
1 B S
2 C S
3 D N
4 E N

Cidades que têm centro: 0 1 2.
Cidade atual: 0 Cidade destino: 2
Arestas e precisa terminar com -1 -1 -1

0 1 1
0 4 5
1 2 1
1 4 2
2 3 4
3 0 7
3 2 6
4 1 3
4 2 9
4 3 2
-1 -1 -1
Menor caminho: 0 4 1 2
Custo: 9

*/

#include <iostream>
#include <string>
#include <list>
#include <locale.h>
#include <stdlib.h>
#include <vector>
#include <climits>

using namespace std;

// Definição da estrutura para representar uma aresta
struct no {
    int vertice; // vértice adjacente
    int peso;    // peso da aresta
};

// Definição das estruturas de dados
struct Cidades
{
    int codigo;
    string nome;
    int peso;
    char temCentroPokemon;
    bool initialized; // Flag para indicar se a cidade foi inicializada
};

struct Pokemon
{
    string nome;
    string tipo;
    int numero;
    int posx;
    int posy;
    bool initialized; // Flag para indicar se o Pokemon foi inicializado
};

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
    vector<bool> intree(nVertices, false);
    // Vetor para armazenar as distâncias mínimas
    vector<int> distance(nVertices, INT_MAX);
    // Vetor para armazenar os pais na MST
    vector<int> parent(nVertices, -1);

    distance[codigo_atual] = 0; // Define a distância do vértice inicial como 0
    int v = codigo_atual;        // Inicia do vértice de início

    // Algoritmo de Dijkstra
    while (!intree[v]) {
        intree[v] = true; // Marca o vértice como incluído na MST

        // Itera sobre todas as arestas adjacentes ao vértice atual
        for (auto &p : adj[v]) {
            int dest = p.vertice;
            int weight = p.peso;

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
    vector<int> caminho;
    int at = codigo_final;
    while (at != -1) {
        caminho.push_back(at);
        at = parent[at];
    }

    // Imprime o menor caminho
    cout << "Menor caminho: ";
    for (int i = caminho.size() - 1; i >= 0; --i) {
        cout << caminho[i];
        if (i > 0)
            cout << " ";
    }
    cout << endl;

    // Calcula o custo do caminho
    int custoCaminho = 0;
    for (int i = caminho.size() - 1; i > 0; --i) {
        int u = caminho[i];
        int v = caminho[i - 1];
        for (auto &p : adj[u]) {
            if (p.vertice == v) {
                custoCaminho += p.peso;
                break;
            }
        }
    }

    cout << "Custo: " << custoCaminho << endl;
}

int main()
{
    // Variáveis
    int i = 0;
    int contador_cidades = 0;
    int orientado = 1;
    int codigo_atual; 
    int codigo_final;
    int u; // Vértice de origem
    int v; // Vértice de destino
    int p; // Peso

    setlocale(LC_ALL, "portuguese"); // Define o locale para usar a língua portuguesa
    int opcao;
    Cidades city[10000];
    Pokemon pokemon;
    // Variáveis para cadastrar cidade
    int u_cidade;
    string nome;
    char PokeCenter;

    city[0].initialized = false; // Inicializa a flag de cidade como falso
    pokemon.initialized = false; // Inicializa a flag de Pokemon como falso

    list<no> adj[10000];
    
    // Loop principal do programa
    do
    {
        system("cls"); // Limpa a tela do console (específico para Windows)
        cout << "Bem-vindo a sua Pokedex" << endl;
        cout << "Escolha uma das funcoes disponiveis" << endl;
        cout << "1 - Cadastrar uma cidade" << endl;
        cout << "2 - Cadastrar um Pokemon" << endl;
        cout << "3 - Imprimir informações da cidade" << endl;
        cout << "4 - Listar o Pokemon cadastrado" << endl;
        cout << "5 - Mostrar o Centro Pokemon mais próximo" << endl;
        cout << "0 - Desligar Pokedex" << endl;
        cout << "Opcao: ";
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
                   system("cls");
                   cout << "Digite o código da cidade: ";
                   cin >> u_cidade;
                   cout << "Digite o nome da cidade: ";
                   cin.ignore();
                   getline(cin, nome);
                   cout << "A cidade tem Centro Pokemon: S/N: ";
                   cin >> PokeCenter;
        
                   contador_cidades++;
        
                   // Atribui os valores lidos à estrutura da cidade
                   city[i].codigo = u_cidade;
                   city[i].nome = nome;
                   city[i].temCentroPokemon = PokeCenter;
                   city[i].initialized = true; // Marca a cidade como inicializada
        
                   cout<<"Deseja continuar cadastrando cidades? (0 - Sim / 1 - Não): ";
                   cin>>opcao;
                } while(opcao != 1);
                break;

            case 2: // Cadastro de Pokemon
                system("cls");
                cout << "Digite o nome do Pokemon: ";
                cin >> pokemon.nome;
                cout << "Digite o tipo do Pokemon: ";
                cin >> pokemon.tipo;
                cout << "Digite o numero do Pokemon: ";
                cin >> pokemon.numero;
                cout << "Digite a coordenada x do Pokemon: ";
                cin >> pokemon.posx;
                cout << "Digite a coordenada y do Pokemon: ";
                cin >> pokemon.posy;

                pokemon.initialized = true; // Marca o Pokemon como inicializado

                break;

            case 3: // Imprimir informações da cidade
                system("cls");
                if (!city[i].initialized) {
                    cout << "Ainda não foi criada nenhuma cidade :(" << endl;
                    break;
                }
                cout << "Informações da cidade cadastrada:" << endl;
                cout << "Código da cidade: " << city[i].codigo << endl;
                cout << "Nome da cidade: " << city[i].nome << endl;
                cout << "Possui centro Pokemon: " << city[i].temCentroPokemon << endl;

                break;

            case 4: // Listar o Pokemon cadastrado
                system("cls");
                if (!pokemon.initialized) {
                    cout << "Ainda não há um pokemon cadastrado :(" << endl;
                    break;
                }
                cout << "Informações do pokemon cadastrado:" << endl;
                cout << "Nome do Pokemon: " << pokemon.nome << endl;
                cout << "Tipo do Pokemon: " << pokemon.tipo << endl;
                cout << "Numero do Pokemon: " << pokemon.numero << endl;
                cout << "Pos (X) do Pokemon: " << pokemon.posx << endl;
                cout << "Pos (Y) do Pokemon: " << pokemon.posy << endl;

                break;
                
            case 5:
                system("cls");
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

            default: // Opção inválida
                system("cls");
                cout << "Opção Inválida" << endl;
                break;
        }

        // Verifica se o usuário deseja voltar ao menu principal
        cout << "Deseja voltar ao menu principal? (S/N)" << endl;
        char menu;
        cin >> menu;
        if (toupper(menu) == 'N') // Converte a entrada para maiúsculas e verifica se é 'N'
        {
            opcao = 0; // Sai do loop
        }
        
    } while (opcao != 0); // Loop continua até que opcao seja 0
    
    return 0;
}

/*
        Tema:  POKÉDEX
        
        Nomes:  DOUGLAS OTANI, NATALIA APARECIDA, PAULO HENRIQUE
        
*/
