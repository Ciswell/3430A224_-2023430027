#include <iostream>
#include <vector>
#include <fstream>
#include <climits> 
#include <cstdlib> 

class grafo {
private:
    int n; // representa el numero de nodos
    std::vector<std::vector<int>> matriz; // almacena la matriz de distancias

public:
    // constructor que inicializa el grafo con n nodos y una matriz de n x n llena de ceros
    grafo(int n) : n(n), matriz(n, std::vector<int>(n, 0)) {}

    // metodo que agrega una arista entre los nodos i y j con un peso determinado
    void agregar_arista(int i, int j, int peso) {
        matriz[i][j] = peso;  // se actualiza la matriz de distancias en ambas direcciones
        matriz[j][i] = peso;  // por que el grafo es no dirigido
    }

    // metodo que genera el archivo .dot para representar el grafo en graphviz
    void generar_graphviz(const std::string& filename) {
        std::ofstream file(filename);
        file << "graph g {\n";  //  inicia la estructura de un grafo no dirigido
        file << "graph [rankdir=lr]\n";  // la direccion de izquierda a derecha
        file << "node [style=filled fillcolor=\"#00ff005f\"]\n";  // define el estilo de los nodos
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (matriz[i][j] != 0) {
                    // integra una arista al archivo .dot con el peso correspondiente
                    file << "  " << char('a' + i) << " -- " << char('a' + j)
                         << " [label=" << matriz[i][j] << "];\n";
                }
            }
        }
        file << "}\n";  // cierra la definicion del grafo
        file.close(); 
    }

    // metodo que agrega el algoritmo de prim para encontrar el arbol de expansion minima
    std::vector<std::pair<int, int>> prim() {
        std::vector<bool> visitado(n, false);  // crea un vector para marcar los nodos visitados
        std::vector<std::pair<int, int>> arbol_minimo;  // almacena el arbol minimo
        visitado[0] = true;  //  empieza desde el primer nodo marcado como visito

        for (int edge = 0; edge < n - 1; ++edge) {
            int min = INT_MAX;
            int u = -1, v = -1;

            // busca la arista de menor peso que conecte un nodo visitado con uno no visitado
            for (int i = 0; i < n; ++i) {
                if (visitado[i]) {
                    for (int j = 0; j < n; ++j) {
                        if (!visitado[j] && matriz[i][j] && matriz[i][j] < min) {
                            min = matriz[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }
            // si se encuentra una arista valida, se agrega al arbol minimo y se marca el nodo como visitado
            if (u != -1 && v != -1) {
                arbol_minimo.push_back({u, v});
                visitado[v] = true;
            }
        }

        return arbol_minimo;  // retorna el conjunto de aristas del arbol minimo
    }

    // metodo que genera el archivo .dot del arbol de expansion minima para graphviz
    void generar_graphviz_minimo(const std::string& filename, const std::vector<std::pair<int, int>>& arbol_minimo) {
        std::ofstream file(filename);
        file << "graph g {\n";  // inicia la estructura de un grafo no dirigido
        file << "graph [rankdir=lr]\n";  // establece la direccion de izquierda a derecha
        file << "node [style=filled fillcolor=\"#00ff005f\"]\n";  // define el estilo de los nodos
        for (const auto& arista : arbol_minimo) {
            int u = arista.first;
            int v = arista.second;
            // integra la arista minima al archivo .dot
            file << "  " << char('a' + u) << " -- " << char('a' + v)
                 << " [label=" << matriz[u][v] << "];\n";
        }
        file << "}\n";  // cierra la definicion del grafo
        file.close();  
    }
};

int main() {
    int n;

    // validacion del valor de n para que sea mayor que 2
    do {
        std::cout << "ingrese el numero de nodos (n debe ser mayor que 2): ";
        std::cin >> n;
        if (n <= 2) {
            std::cout << "error: el numero de nodos debe ser mayor que 2 intente nuevamente\n";
        }
    } while (n <= 2);

    grafo grafo(n);  // se crea el objeto grafo con n nodos

    // solicita la matriz de distancias ingresada en la terminal
    std::cout << "ingrese la matriz de distancias (valores mayores o iguales a 0):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int peso;
            std::cin >> peso;
            if (peso < 0) {
                std::cout << "error: la distancia debe ser un valor no negativo intente nuevamente\n";
                --j;  // repite el ingreso del valor si es invalido
            } else {
                grafo.agregar_arista(i, j, peso);  // integra la arista a la matriz
            }
        }
    }

    // genera el archivo .dot para el grafo original
    grafo.generar_graphviz("grafo_original.dot");

    // ejecuta el algoritmo de prim para obtener el arbol minimo de expansion
    auto arbol_minimo = grafo.prim();

    // muestra el contenido del conjunto l (aristas del arbol de expansion minima)
    std::cout << "conjunto l (aristas del arbol de expansion minima):\n";
    for (const auto& arista : arbol_minimo) {
        std::cout << char('a' + arista.first) << " -- " << char('a' + arista.second)
                  << " [peso: " << grafo.prim()[0].first << "]\n";  // se imprimen las aristas
    }

    // abre el archivo .dot para el arbol de expansion minima
    grafo.generar_graphviz_minimo("grafo_minimo.dot", arbol_minimo);

    // convierte los archivos .dot a imagenes .png usando graphviz
    system("dot -tpng grafo_original.dot -o grafo_original.png");
    system("dot -tpng grafo_minimo.dot -o grafo_minimo.png");

    // abre las imagenes generadas con gwenview
    system("gwenview grafo_original.png &");
    system("gwenview grafo_minimo.png &");

    return 0;  
}

