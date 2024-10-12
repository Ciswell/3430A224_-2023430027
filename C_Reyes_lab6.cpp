#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>  

#define TRUE 0
#define FALSE 1

using namespace std;

// declaraciones de funciones
void inicializar_vector_D(int D[], int M[][100], int N);
void inicializar_vector_caracter(char vector[], int N);
void dijkstra(char V[], char S[], char VS[], int D[], int M[][100], int N);
void actualizar_VS(char V[], char S[], char VS[], int N);
int elegir_vertice(char VS[], int D[], char V[], int N);
void actualizar_pesos(int D[], char VS[], int M[][100], char V[], int idx_v, int N);  
int buscar_indice_caracter(char V[], char caracter, int N);
void agrega_vertice_a_S(char S[], char vertice, int N);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_vector_entero(int vector[], int N);
void imprimir_matriz(int M[][100], int N);
void imprimir_grafo(int M[][100], char vector[], int N);

// función principal que acepta datos desde la línea de comandos
int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "uso: ./programa N matriz_de_distancias origen" << endl;
        return -1;
    }

    // se genera el número de nodos 'N' desde el primer argumento
    int N = atoi(argv[1]);

    if (N < 2) {
        cout << "el número de nodos debe ser mayor que 2." << endl;
        return -1;
    }

    // analiza los valores de la matriz de distancias a partir de los datos entregados en la línea de comandos
    int M[100][100];
    int index = 2;  // índice para recorrer argv

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            M[i][j] = atoi(argv[index]);  // convierte los argumentos a enteros
            index++;
        }
    }

    // se obtiene el vértice de origen desde el último argumento
    char origen = argv[index][0];

    // se inicializaban los vectores
    char V[N], S[N], VS[N];
    int D[N];
    inicializar_vector_caracter(V, N);
    inicializar_vector_caracter(S, N);
    inicializar_vector_caracter(VS, N);

    // se asignan los nodos desde la letra 'A'
    for (int i = 0; i < N; i++) {
        V[i] = 'A' + i;
    }

    dijkstra(V, S, VS, D, M, N);

    // se imprime los resultados
    imprimir_grafo(M, V, N);
    imprimir_vector_entero(D, N);

    return 0;
}

// esta función inicia el vector de distancias 'D' a partir de la primera fila de la matriz 'M'
void inicializar_vector_D(int D[], int M[][100], int N) {
    for (int col = 0; col < N; col++) {
        // ai hay una distancia no alcanzable (-1), la inicializamos a infinito
        if (M[0][col] == -1) {
            D[col] = INT_MAX;
        } else {
            D[col] = M[0][col];
        }
    }
}

// esta función inicia el vector de caracteres con espacios en blanco
void inicializar_vector_caracter(char vector[], int N) {
    for (int col = 0; col < N; col++) {
        vector[col] = ' ';
    }
}

// esta función busca el camino más corto
void dijkstra(char V[], char S[], char VS[], int D[], int M[][100], int N) {
    inicializar_vector_D(D, M, N);

    cout << "Matriz:" << endl;
    imprimir_matriz(M, N);
    imprimir_vector_entero(D, N);

    agrega_vertice_a_S(S, V[0], N);  // el primer vértice 'A' se añade a S
    actualizar_VS(V, S, VS, N);      // se actualiza el conjunto VS

    for (int i = 1; i < N; i++) {
        // esocge el vértice con la menor distancia y obtine su índice
        int idx_v = elegir_vertice(VS, D, V, N);
        agrega_vertice_a_S(S, V[idx_v], N);  // agrega el vértice a S usando el índice
        actualizar_VS(V, S, VS, N);          // actualiza el conjunto VS
        actualizar_pesos(D, VS, M, V, idx_v, N);  // actualiza los pesos después de elegir el vértice
    }
}

// actualiza el conjunto 'VS' basado en los vértices que ya estaban en 'S'
void actualizar_VS(char V[], char S[], char VS[], int N) {
    inicializar_vector_caracter(VS, N);
    int k = 0;

    for (int j = 0; j < N; j++) {
        if (buscar_indice_caracter(S, V[j], N) == FALSE) {  // si no está en S, lo ponemos en VS
            VS[k++] = V[j];
        }
    }
}

// busca el índice de un vértice en el vector 'V'
int buscar_indice_caracter(char V[], char caracter, int N) {
    for (int i = 0; i < N; i++) {
        if (V[i] == caracter) {
            return i;  // retorna el índice del carácter en V
        }
    }
    return -1;
}

// agrega un vértice al conjunto 'S'
void agrega_vertice_a_S(char S[], char vertice, int N) {
    for (int i = 0; i < N; i++) {
        if (S[i] == ' ') {  // busca un espacio vacío y lo reemplaza con el vértice
            S[i] = vertice;
            return;
        }
    }
}

// escoge el vértice con menor peso en 'VS' comparando los valores en 'D'
int elegir_vertice(char VS[], int D[], char V[], int N) {
    int menor = INT_MAX;  // Inicializamos menor a infinito
    int idx_vertice = -1;

    for (int i = 0; i < N; i++) {
        if (D[i] != INT_MAX && buscar_indice_caracter(VS, V[i], N) != -1) {
            if (D[i] < menor) {
                menor = D[i];
                idx_vertice = i;  // devuelve el índice
            }
        }
    }

    return idx_vertice;  // devuelve el índice del vértice con menor distancia
}

// actualiza los pesos en el vector de distancias 'D' después de elegir un vértice
void actualizar_pesos(int D[], char VS[], int M[][100], char V[], int idx_v, int N) {
    // idx_v es el índice del vértice elegido
    for (int i = 0; i < N; i++) {
        if (VS[i] != ' ') {  // si el vértice está en VS
            int idx_w = buscar_indice_caracter(V, VS[i], N);
            if (M[idx_v][idx_w] != -1) {  // si existe una conexión entre v y w
                D[idx_w] = calcular_minimo(D[idx_w], D[idx_v], M[idx_v][idx_w]);  // actualiza la distancia
            }
        }
    }
}

// calcula el valor mínimo entre dos distancias y el valor de la matriz
int calcular_minimo(int dw, int dv, int mvw) {
    if (dw == INT_MAX) return dv + mvw;  // si dw es "infinito", lo actualiza
    if (mvw == -1) return dw;            // si mvw es -1 (sin conexión)
    return min(dw, dv + mvw);            // calcula el mínimo de las dos distancias
}

// imprime el contenido del vector de distancias 'D'
void imprimir_vector_entero(int vector[], int N) {
    for (int i = 0; i < N; i++) {
        if (vector[i] == INT_MAX) {
            cout << "D[" << i << "]: INFINITO" << endl;
        } else {
            cout << "D[" << i << "]: " << vector[i] << endl;
        }
    }
}

// imprime la matriz de distancias 'M'
void imprimir_matriz(int M[][100], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

// genera un archivo 'grafo.dot' y lo convierte
void imprimir_grafo(int M[][100], char vector[], int N) {
    FILE *fp = fopen("grafo.dot", "w");
    fprintf(fp, "digraph G {\n");
    fprintf(fp, "graph [rankdir=LR]\n");
    fprintf(fp, "node [style=filled, fillcolor=yellow];\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j && M[i][j] != -1) {
                fprintf(fp, "%c -> %c [label=%d];\n", vector[i], vector[j], M[i][j]);
            }
        }
    }

    fprintf(fp, "}\n");
    fclose(fp);
    // se genera la imagen del grafo y se abre con gwenview
    system("dot -Tpng -o grafo.png grafo.dot");
    system("gwenview grafo.png &");
}
