#include <iostream>
using namespace std;

class Pila {
private:
    int *datos; 
    int max;  
    int tope; 
    bool band;  // indicador si la pila está vacía o llena

public:
    // determina el tamaño máximo de la pila
    Pila(int maxTam) {
        max = maxTam;  // inicia el tamaño max de la pila
        datos = new int[max]; 
        tope = 0;  
        band = true; 
    }

    // verifica si la pila está vacía
    bool pila_vacia() {
        if (tope == 0) {
            band = true;  // está vacía
        } else {
            band = false;  // no está vacía
        }
        return band;
    }

    // verifica si la pila está llena
    bool pila_llena() {
        if (tope == max) {
            band = true;  // está llena
        } else {
            band = false;  // no está llena
        }
        return band;
    }

    // el push de la pila
    void push(int dato) {
        if (pila_llena()) {
            cout << "Desbordamiento, pila llena." << endl;  
        } else {
            datos[tope] = dato; 
            tope++;  
        }
    }

    // el pop de la pila
    void pop() {
        if (pila_vacia()) {
            cout << "Subdesbordamiento, pila vacía." << endl;  
        } else {
            tope--;  // disminuye el valor de tope
            cout << "Se eliminó el elemento: " << datos[tope] << endl;  // muestra el elemento eliminado
        }
    }

    // muestra el contenido de la pila
    void mostrar_pila() {
        if (pila_vacia()) {
            cout << "La pila no tiene elementos." << endl;  
        } else {
            cout << "Contenido actual de la pila:" << endl;  
            for (int i = tope - 1; i >= 0; i--) {  // recorre los elementos desde el tope hacia abajo
                cout << "|" << datos[i] << "|" << endl;  // imprime los elementos
            }
        }
    }

    ~Pila() {
        delete[] datos;
    }
};

void mostrar_menu() {
    cout << endl;
    cout << "Menú de opciones:" << endl;
    cout << "1. Agregar/push" << endl;
    cout << "2. Remover/pop" << endl;
    cout << "3. Ver pila" << endl;
    cout << "0. Salir" << endl;
    cout << "Elige una opción: ";
}

int main() {
    int maxTam;
    cout << "Ingrese tamaño máximo de la pila: ";
    cin >> maxTam;  // el usuario ingresa el tamaño máximo de la pila

    Pila pila(maxTam);  // crea una instancia de la clase Pila con el tamaño dado
    int opcion, valor;  

    do {
        mostrar_menu(); 
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Dato a insertar: "; 
                cin >> valor;
                pila.push(valor);
                break;
            case 2:
                pila.pop();
                break;
            case 3:
                pila.mostrar_pila();
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo." << endl;
        }
    } while (opcion != 0);  // el ciclo se repite hasta que termine saliendo del programa (0)

    return 0;  // termina la ejecución del programa
}
