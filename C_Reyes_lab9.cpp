#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int TABLE_SIZE = 20;

// función hash 
int H(int key) {
    return key % TABLE_SIZE;
}

// función hash secundaria para doble direccion
int H_prime(int index) {
    return (7 - (index % 7));
}

// clase de la tabla hash
class HashTable {
private:
    vector<int> V;
    vector<list<int>> L;

public:
    HashTable() : V(TABLE_SIZE, -1), L(TABLE_SIZE) {}

    // inserta un elemento usando el metodo especifico
    void insertar(int K, char metodo) {
        int D = H(K);  // la direccion inicial
        int D_original = D;
        bool colision = false;

        if (metodo == 'L') {  // prueba lineal
            int I = 0;
            while ((V[D] != -1) && (V[D] != K)) {
                colision = true;
                D = (D_original + I) % TABLE_SIZE;
                I = I + 1;
            }
            V[D] = K;
        } else if (metodo == 'C') {  // prueba cuadratica
            int I = 1;
            while ((V[D] != -1) && (V[D] != K)) {
                colision = true;
                D = (D_original + I * I) % TABLE_SIZE;
                I = I + 1;
            }
            V[D] = K;
        } else if (metodo == 'D') {  // doble hashing
            int I = 0;
            int H2 = H_prime(D_original);
            while ((V[D] != -1) && (V[D] != K)) {
                colision = true;
                D = (D_original + I * H2) % TABLE_SIZE;
                I = I + 1;
            }
            V[D] = K;
        } else if (metodo == 'E') {  // encadenamiento
            L[D].push_back(K);
        }

        // imprime el resultado
        cout << "insertado " << K << " en posicion " << D;
        if (colision) cout << " (colision resuelta desde " << D_original << " hasta " << D << ")";
        cout << endl;
    }

    // funcion de busqueda
    void buscar(int K, char metodo) {
        int D = H(K);  // posicion inicial de busqueda
        int D_original = D;
        bool encontrado = false;
        bool colision = false;
        
        if (metodo == 'L') {  // busqueda con prueba lineal
            int I = 0;
            while (V[D] != -1 && V[D] != K) {
                colision = true;
                D = (D_original + I) % TABLE_SIZE;
                I = I + 1;
            }
            encontrado = (V[D] == K);
        } else if (metodo == 'C') {  // busqueda con prueba cuadratica
            int I = 1;
            while (V[D] != -1 && V[D] != K) {
                colision = true;
                D = (D_original + I * I) % TABLE_SIZE;
                I = I + 1;
            }
            encontrado = (V[D] == K);
        } else if (metodo == 'D') {  // busqueda con doble hashing
            int I = 0;
            int H2 = H_prime(D_original);
            while (V[D] != -1 && V[D] != K) {
                colision = true;
                D = (D_original + I * H2) % TABLE_SIZE;
                I = I + 1;
            }
            encontrado = (V[D] == K);
        } else if (metodo == 'E') {  // busqueda con encadenamiento
            for (int item : L[D]) {
                if (item == K) {
                    encontrado = true;
                    break;
                }
            }
        }

        // imprime el resultado de la busqueda
        if (encontrado) {
            cout << "Elemento " << K << " encontrado en posicion " << D;
            if (colision) cout << " (colision resuelta desde " << D_original << " hasta " << D << ")";
        } else {
            cout << "Elemento " << K << " no encontrado.";
        }
        cout << endl;
    }

    // muestra el contenido de la tabla
    void mostrar() {
        cout << "tabla hash:" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " : " << V[i] << endl;
        }

        cout << "\nlistas encadenadas:" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " : ";
            for (int item : L[i]) {
                cout << item << " -> ";
            }
            cout << "NULL" << endl;
        }
    }
};

// ejecuta una prueba con el metodo especifico
void ejecutarPrueba(HashTable& ht, const vector<int>& keys, char metodo) {
    for (int K : keys) {
        ht.insertar(K, metodo);
    }
    ht.mostrar();
}

int main(int argc, char* argv[]) {
    vector<int> keys = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};

    // verifica que al menos un metodo valido fue especificado
    if (argc < 2) {
        cout << "uso: ./C_Reyes_lab9 {L|C|D|E} ..." << endl;
        cout << "L - prueba lineal\nC - prueba cuadratica\nD - doble hashing\nE - encadenamiento" << endl;
        return 1;
    }

    vector<char> metodos;
    for (int i = 1; i < argc; ++i) {
        char metodo = argv[i][0];
        if (metodo == 'L' || metodo == 'C' || metodo == 'D' || metodo == 'E') {
            metodos.push_back(metodo);
        } else {
            cout << "metodo invalido: " << metodo << endl;
            cout << "uso: ./C_Reyes_lab9 {L|C|D|E} ..." << endl;
            return 1;
        }
    }

    // ejecuta cada metodo especifico en los argumentos
    for (char metodo : metodos) {
        cout << "==== Ejecutando metodo " << metodo << " ====" << endl;
        HashTable ht;
        ejecutarPrueba(ht, keys, metodo);
        
        // prueba de busqueda para un elemento existente y uno no existente
        cout << "==== Prueba de busqueda ====" << endl;
        ht.buscar(43, metodo);  // busca un elemento que existe
        ht.buscar(99, metodo);  // busca un elemento que no existe
        cout << endl;
    }

    return 0;
}
