/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Objetivo:
    Implementar los algoritmos vistos en clase en un solo programa
    Se desea la utilizacion de Git y Github, asi como OOP.

Integrantes del equipo:
    -Angel Enrique Chavez Ponce
    -Daniela Moran
    -Diego Romo Muñoz
    -Maria Fernanda Barron
    -Noe Shaddai De Luna 
    -Jesus Alejandro Luevano

To Do List:                             Status
   -Grafo en matriz                     Listo
   -Grafo en lista                      Listo
   -Busqueda por anchura                Sin Comenzar
   -Busqueda por profundidad            En progreso =] 
   -Grafo conexo                        Sin Comenzar
   -Djikstra                            Sin Comenzar
   -Prim                                En progreso
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <climits>

using namespace std;
//TamaÃ±o del grafo como variable global
const int TAM = 10;
int nodos = 0;

void cuadros(int nodos, int grafo[TAM][TAM], char letras[]);
int minimoPeso(int clave[], bool conjuntoMST[]);

//Clase en al que encapsularemos las propiedades y metodos del objeto grafo
class Grafo {
    //PROPIEDADES
public:
    int grafo [TAM][TAM];
    int grafoPrim[TAM][TAM];

    Grafo() {
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                grafo[i][j] = 0;
                grafoPrim[i][j] = 0;
            }
        }
    }

    ~Grafo() {
        //Destructor de la clase ... Por ahora no hace nada
    }

    //METODOS


    void capturarGrafo() {
        int opcion;
        int peso;
        do {
            system("cls");
            cout << "~Capturando El Grafo~" << std::endl;
            cout << "1.-Agregar Arista" << std::endl;
            cout << "2.-Salir" << std::endl;
            cin >> opcion;
            switch (opcion) {
                case 1: {
                    int nodoInicio, nodoDestino, peso;
                        cout << "Ingrese el nodo de inicio: ";
                        cin >> nodoInicio;
                    nodoInicio--;
                        cout << "Ingrese el nodo de destino: ";
                        cin >> nodoDestino;
                    nodoDestino--;
                        cout << "Ingrese el peso de la arista: ";
                        cin >> peso;
                    agregarArista(nodoInicio, nodoDestino, peso);
                    break;
                }

                case 2: {
                        cout << "Captura del grafo terminada" << endl;
                    break;
                }
                default: {
                        cout << "Opcion Invalida" << endl;
                    break;
                }
            }
        } while (opcion != 2);
    }

    void agregarArista(int nodoInicio, int nodoDestino, int peso) {
        if (nodoInicio >= 0 && nodoInicio < TAM && nodoDestino >= 0 && nodoDestino < TAM) {
            grafo[nodoInicio][nodoDestino] = 1;
            grafo[nodoDestino][nodoInicio] = 1;
            grafoPrim[nodoInicio][nodoDestino] = peso;
            grafoPrim[nodoDestino][nodoInicio] = peso; // Añadir también la arista inversa si es un grafo no dirigido
        }
        else {
            cout << "Nodos de inicio o destino invalidos. La arista no se puede agregar." << endl;
            fflush(stdin);
            getchar();
            system("cls");
        }
    }

    void rellenarGrafo() {
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                grafo[i][j] = 0;
            }
        }
    }

    void imprimirGrafo() {
        cout << "Matriz de Adyacencia del Grafo:" << endl;
        for (int i = 0; i < TAM; ++i) {
            for (int j = 0; j < TAM; ++j) {
                cout << grafo[i][j] << " ";
            }
            cout << endl;
        }
        cout<<"Presiones una tecla para salir"<<endl;
        fflush(stdin);
        getchar();
        system("cls");
    }
    
    void recorridoProfundidad() {
    	int i,j, temporal, inicial;
    	cout<<"Dame el nodo inicial: ";
    	cin>>inicial;
    	inicial=inicial-1;
    	vector<vector<int> >grafoP(TAM);
    	//Pasamos la matriz a lista de adyacencia
    	for(i=0;i<TAM;i++){
    		for(j=0;j<TAM;j++){
    			if(grafo[i][j]==1){
    				grafoP[i].push_back(j);
				}
			}
		}
		
		bool vali;
		
	    list<int> profundo;
	    list<int>::iterator it;
	
	    stack<int> pila;
	    stack<int> copiaPila;
	
	    pila.push(inicial);
	
	    while (!pila.empty()) {
	        temporal = pila.top(); // Temporal toma el primer valor de la pila
	        pila.pop();
	        profundo.push_back(temporal); // Le asignamos a profundo el valor de la pila
	
	        for (j = 0; j < grafoP[temporal].size(); j++) {
	            // Checamos si las conexiones no están repetidas
	            it = profundo.begin();
	            vali = true;
	            while (it != profundo.end()) {
	                if (*it == grafoP[temporal][j])
	                    vali = false;
	                ++it; // Avanzar al siguiente elemento
	            }
	            copiaPila = pila;
	            while (!copiaPila.empty() && vali) {
	                if (copiaPila.top() == grafoP[temporal][j])
	                    vali = false;
	                copiaPila.pop();
	            }
	            if (vali)
	                pila.push(grafoP[temporal][j]);
	        }
	    }
	    
	    cout<<endl<<"Elementos visitados en profundidad"<<endl;
	    
	    it = profundo.begin();
	    while (it != profundo.end()) {
	        cout <<*it+1<<endl;
	        ++it; // Avanzar al siguiente elemento
	    }
		
	}
	 void crearConexo(){
    	int ar, nodo1, nodo2, cont1, contB, temp;
        char letras[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
        int matAd[100][100], contN[50], ind[100], temMa[100][100], tempCon[50], diagonal[50];
        cout << "Dame la cantidad de nodos: ";
        cin >> nodos;
        cout << "Dame la cantidad de aristas: ";
        cin >> ar;
        for (int i = 0; i < ar; i++) {
            cout << "Valor de nodo 1: ";
            cin >> nodo1;
            cout << "Valor de nodo 2: ";
            cin >> nodo2;
            matAd[nodo1 - 1][nodo2 - 1] = 1;
        	}
	}

    void conexo() {
        char letras[TAM];
        for (int i = 0; i < TAM; i++) {
            letras[i] = 'A' + i;
        }
        cuadros(nodos, grafo, letras);
    }

    vector<vector<int>> listaAdy() {
    	vector<vector<int>> listaAdyacencia(TAM);
        for (int i = 0; i < TAM; ++i) {
            for (int j = 0; j < TAM; ++j) {
                if (grafo[i][j] == 1) {
                    listaAdyacencia[i].push_back(j);
                }
            }
        }
        return listaAdyacencia;
	}

    void Prim() {
        int padre[TAM];
        int clave[TAM];
        bool conjuntoMST[TAM];

        for (int i = 0; i < TAM; i++) {
            clave[i] = INT_MAX;
            conjuntoMST[i] = false;
        }

        clave[0] = 0;
        padre[0] = -1;

        for (int contador = 0; contador < TAM - 1; contador++) {
            int u = minimoPeso(clave, conjuntoMST);
            conjuntoMST[u] = true;

            for (int v = 0; v < TAM; v++) {
                if (grafoPrim[u][v] && !conjuntoMST[v] && grafoPrim[u][v] < clave[v]) {
                    padre[v] = u;
                    clave[v] = grafoPrim[u][v];
                }
            }
        }

        for (int i = 1; i < TAM; i++) {
            cout << "Arista: " << padre[i] << " - " << i << " Peso: " << grafoPrim[i][padre[i]] << endl;
        }
    }

    void capturarGrafoPrim(){
        int opcion;
        do {
            system("cls");
            cout << "~Capturando El Grafo~" << endl;
            cout << "1.-Agregar Arista" << endl;
            cout << "2.-Salir" << endl;
            fflush(stdin);
            cin >> opcion;
            switch (opcion) {
                case 1: {
                    int nodoInicio, nodoDestino;
                    cout << "Ingrese el nodo de inicio: ";
                    fflush(stdin);
                    cin >> nodoInicio;
                    nodoInicio > 0 ? nodoInicio-- : nodoInicio = nodoInicio;
                    cout << "Ingrese el nodo de destino: ";
                    fflush(stdin);
                    cin >> nodoDestino;
                    nodoDestino > 0 ? nodoDestino-- : nodoDestino = nodoDestino;
                    agregarAristaPRIM(nodoInicio, nodoDestino);
                    break;
                }

                case 2: {
                    cout << "Captura del grafo terminada" << endl;
                    fflush(stdin);
                    getchar();
                    break;
                }
                default: {
                    cout << "Opcion Invalida" << endl;
                    fflush(stdin);
                    getchar();
                    system("cls");
                    break;
                }

            }
        }while (opcion != 2);
    }

    void agregarAristaPRIM(int nodoInicio, int nodoDestino) {
        int arista;
        system("cls");
        // Función para agregar una arista, toma como argumentos el nodo de inicio y el nodo de destino de la arista
        if (nodoInicio >= 0 && nodoInicio < TAM && nodoDestino >= 0 && nodoDestino < TAM) {
            //Marcamos la conexion
            cout << "Ingrese el valor de la arista: ";
            fflush(stdin);
            cin >> arista;
            grafoPrim[nodoInicio][nodoDestino] = arista; // Asignar el peso ingresado
            grafoPrim[nodoDestino][nodoInicio] = arista; // Añadir también la arista inversa si es un grafo no dirigido
        } else {
            cout << "Nodos de inicio o destino invalidos. La arista no se puede agregar." << endl;
            fflush(stdin);
            getchar();
            system("cls");
        }
    }
};

//Para el algo de Prim
int minimoPeso(int clave[], bool conjuntoMST[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < TAM; v++) {
        if (!conjuntoMST[v] && clave[v] < min) {
            min = clave[v];
            min_index = v;
        }
    }
    return min_index;
}

void cuadros(int nodos, int grafo[TAM][TAM], char letras[]) {
    bool visited[TAM] = { false };
    printf("Componentes Conexas:\n");

    for (int i = 0; i < nodos; i++) {
        if (!visited[i]) {
            printf("V%d={%c", i + 1, letras[i]);
            visited[i] = true;

            for (int j = 0; j < nodos; j++) {
                if (grafo[i][j] && !visited[j]) {
                    printf(",%c", letras[j]);
                    visited[j] = true;
                }
            }
            printf("}\n");
        }
    }
}

int main()
{
	int opcion;
    bool grafoCapturado = false;
    Grafo grafo;
    //incializando el grafo en ceros
    do{
    	cout<<"Bienvenido :)"<<endl<<endl;
    	cout<<"(1)-Ingresar Grafo"<<endl;
    	cout<<"(2)-Lista de Adyacencia"<<endl;
    	cout<<"(3)-Busqueda por Anchura"<<endl;
    	cout<<"(4)-Busqueda por Profundidad"<<endl;
    	cout<<"(5)-Grafo Conexo"<<endl;
    	cout<<"(6)-Grafo Dijkstra"<<endl;
    	cout<<"(7)-Verificacion de Arbol"<<endl;
    	cout<<"(8)-Algoritmo de Prim/Kruskal"<<endl;
    	cout<<"(0)-Salir"<<endl;
    	cout<<endl<<"Ingrese su opcion: ";
    	cin>>opcion;
    	switch(opcion){
    		case 1:
				grafo.rellenarGrafo();
			    grafo.capturarGrafo();
			    grafo.imprimirGrafo();
                grafoCapturado= true;
				break;
    		case 2: break;
    		case 3: break;
    		case 4:
				grafo.recorridoProfundidad();
				break;
    		case 5:
				grafo.crearConexo();
                grafo.conexo();
				break;
    		case 6: break;
    		case 7: break;
            case 8:
                if(grafoCapturado){
                    grafo.Prim();
                }
                else{
                    cout<<"Error: Grafo sin Pesos, capture los pesos del grafo en la Opcion 1"<<endl;
                    fflush(stdin);
                    getchar();
                }
                break;
    		case 9: break;
    		case 0: break;
    		default: break;
		}
    	
	}while(opcion!=0);
    
    fflush(stdin);
    getchar();
    return 0;
}
