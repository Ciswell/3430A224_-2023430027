#include <iostream>
#include <cstdlib>
#include <fstream>  

struct Nodo {
    int dato;
    Nodo *izq, *der, *padre;
    int FE;  
};

Nodo* CrearNodo(int dato, Nodo* padre) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = dato;
    nuevo->izq = nullptr;
    nuevo->der = nullptr;
    nuevo->padre = padre;
    nuevo->FE = 0;
    return nuevo;
}

void RotacionIzquierda(Nodo*& nodo) {
    Nodo* aux = nodo->der;
    nodo->der = aux->izq;
    aux->izq = nodo;
    nodo = aux;
}

void RotacionDerecha(Nodo*& nodo) {
    Nodo* aux = nodo->izq;
    nodo->izq = aux->der;
    aux->der = nodo;
    nodo = aux;
}

Nodo* EncontrarMinimo(Nodo* nodo) {
    while (nodo->izq != nullptr) {
        nodo = nodo->izq;
    }
    return nodo;
}

Nodo* EliminarAVL(Nodo*& raiz, int dato) {
    if (raiz == nullptr) {
        return raiz;
    }

    if (dato < raiz->dato) {
        raiz->izq = EliminarAVL(raiz->izq, dato);
    } else if (dato > raiz->dato) {
        raiz->der = EliminarAVL(raiz->der, dato);
    } else {
        if ((raiz->izq == nullptr) || (raiz->der == nullptr)) {
            Nodo* temp = raiz->izq ? raiz->izq : raiz->der;
            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;
            } else {
                *raiz = *temp;
            }
            delete temp;
        } else {
            Nodo* temp = EncontrarMinimo(raiz->der);
            raiz->dato = temp->dato;
            raiz->der = EliminarAVL(raiz->der, temp->dato);
        }
    }

    if (raiz == nullptr) {
        return raiz;
    }

    return raiz;
}

void InsertarAVL(Nodo*& raiz, int dato, Nodo* padre) {
    if (raiz == nullptr) {
        raiz = CrearNodo(dato, padre);
    } else {
        if (dato < raiz->dato) {
            InsertarAVL(raiz->izq, dato, raiz);
        } else if (dato > raiz->dato) {
            InsertarAVL(raiz->der, dato, raiz);
        } else {
            std::cout << "El número ya existe en el árbol.\n";
        }
    }
}

void ModificarNodo(Nodo*& raiz, int valorViejo, int valorNuevo) {
    raiz = EliminarAVL(raiz, valorViejo);
    InsertarAVL(raiz, valorNuevo, nullptr);
}

void GenerarGrafoDot(Nodo* nodo, std::ofstream& archivo) {
    if (nodo != nullptr) {
        archivo << nodo->dato << " [style=filled, fillcolor=yellow, label=\"" 
                << nodo->dato << "\"];\n";  
        if (nodo->izq != nullptr) {
            archivo << nodo->dato << " -> " << nodo->izq->dato << ";\n";
        } else {
            archivo << "null" << nodo->dato << " [shape=point];\n";
            archivo << nodo->dato << " -> null" << nodo->dato << ";\n";
        }
        
        if (nodo->der != nullptr) {
            archivo << nodo->dato << " -> " << nodo->der->dato << ";\n";
        } else {
            archivo << "null" << nodo->dato << "r [shape=point];\n";
            archivo << nodo->dato << " -> null" << nodo->dato << "r;\n";
        }
        
        GenerarGrafoDot(nodo->izq, archivo);
        GenerarGrafoDot(nodo->der, archivo);
    }
}

void GenerarGrafo(Nodo* raiz) {
    std::ofstream archivo("grafo.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para generar el grafo.\n";
        return;
    }

    archivo << "digraph G {\n";
    GenerarGrafoDot(raiz, archivo);
    archivo << "}\n";

    archivo.close();

    system("dot -Tpng -ografo.png grafo.txt");
}

void VisualizarGrafo() {
    if (system("test -f grafo.png") == 0) {
        system("gwenview grafo.png");
    } else {
        std::cerr << "No se pudo encontrar el archivo de imagen para mostrar.\n";
    }
}

void MostrarMenu(Nodo*& raiz) {
    int opcion, dato, valorViejo, valorNuevo;
    do {
        std::cout << "Menu de opciones:\n";
        std::cout << "1. Insertar número\n";
        std::cout << "2. Eliminar número\n";
        std::cout << "3. Modificar número\n";
        std::cout << "4. Generar y visualizar grafo\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                std::cout << "Ingrese el número a insertar: ";
                std::cin >> dato;
                InsertarAVL(raiz, dato, nullptr);
                break;
            case 2:
                std::cout << "Ingrese el número a eliminar: ";
                std::cin >> dato;
                EliminarAVL(raiz, dato);
                break;
            case 3:
                std::cout << "Ingrese el número a modificar: ";
                std::cin >> valorViejo;
                std::cout << "Ingrese el nuevo número: ";
                std::cin >> valorNuevo;
                ModificarNodo(raiz, valorViejo, valorNuevo);
                break;
            case 4:
                GenerarGrafo(raiz);
                VisualizarGrafo();
                break;
            case 5:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 5);
}

int main() {
    Nodo* raiz = nullptr;
    MostrarMenu(raiz);
    return 0;
}
