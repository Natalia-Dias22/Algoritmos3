#include <iostream>
#include <string>
#include <windows.h>
#include <list>
#include <locale.h>
#include <stdlib.h>

using namespace std;

struct Cidades{
    int codigo;
    string nome;
    int peso;
    char temCentroPokemon;
};

struct Pokemon{
    string nome;
    string tipo;
    int numero;
    int posx;
    int posy;
};

int main(){
	setlocale(LC_ALL,"portuguese");
    int opcao;
 	Cidades city;
 	Pokemon pokemon;
   	int peso;
   	//variáveis cidade 1
	int u;
   	string nome;
   	char PokeCenter;
 	//variáveis cidade 2
	int u2;
   	string nome2;
   	char PokeCenter2;
    list <Cidades> adjCidades[100];
    
    do{
    	system("cls");
        cout << "Bem-vindo a sua Pokedex" <<endl;
        cout << "Escolha uma das funcoes disponiveis" <<endl;
        cout << "1 - Cadastrar uma cidade" <<endl;
        cout << "2 - Cadastrar um Pokemon" <<endl;
        cout << "3 - Imprimir todas as informações"<<endl;
        cout << "4 - Buscar Pokemon" <<endl;
        cout << "5 - Listar os Pokemons cadastrados"<<endl;
        cout << "6 - Contar Pokemons por tipo" <<endl;
        cout << "7 - Rastrear Pokemons" <<endl;
        cout << "0 - Desligar Pokedex"<<endl;
        cout << "Opcao: ";
		cin >> opcao;
		
        switch(opcao){
        	case 0:
        		exit(0);
        		break;
            case 1: // Cadastro de Cidade
				           	
				system("cls");
				cout << "Dgite o codigo da cidade incial: ";
            	cin >> u;
				cout << "Dgite o nome da cidade inicial: ";
            	cin >> nome;
            	cout << "A cidade tem Centro Pokemon: S/N: ";
            	cin >> PokeCenter;
				
				cout << "Dgite o codigo da cidade destino: ";
            	cin >> u2;
				cout << "Dgite o nome da cidade destino: ";
            	cin >> nome2;
            	cout << "A cidade tem Centro Pokemon: S/N: ";
            	cin >> PokeCenter2;
            	
       			cout << "Distancia entre as cidades: ";
            	cin >> peso;
            	
            	city.codigo = u2;
            	city.nome = nome2;
            	city.temCentroPokemon = PokeCenter2;
            	city.peso = peso;
            	
            	adjCidades[u].push_back(city);

            	city.codigo = u;
            	city.nome = nome;
            	city.temCentroPokemon = PokeCenter;
            	
            	adjCidades[u2].push_back(city);
				break;
			
			case 2:
				system("cls");
				cout << "Digite o nome do Pokemon: ";
				cin >> pokemon.nome;
				cout << "Digite o tipo do Pokemon: ";
				cin >> pokemon.tipo;
				cout << "Digite a coordenada x do Pokemon: ";
				cin >> pokemon.posx;
				cout << "Digite a coordenada y do Pokemon: ";
				cin >> pokemon.posy;
				break;
			
            default:
            	cout <<"Opção Invalida"<<endl;
            	break;
        }
    }while(opcao!=0);
}