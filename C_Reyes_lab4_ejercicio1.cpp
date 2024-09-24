#include <iostream>
#include <fstream>
#include <cstdlib>  
using namespace std;

// estructura para los nodos del árbol binario, poner aquí los campos para guardar el dato y los punteros a los hijos izquierdo y derecho.
struct Node {
    int info;
    Node* left;
    Node* right;
};

// función para crear nodos, 
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node* root = nullptr;  // el árbol empieza vacío

    // insertar un nodo en el árbol
    Node* insertNode(Node* node, int data) {
        if (node == nullptr) {
            // cuando no hay nada crea un nodo y lo devuelve
            return createNode(data);
        }

        if (data < node->info) {
            // los números más pequeños van a la izquierda
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            // los más grandes a la derecha
            node->right = insertNode(node->right, data);
        } else {
            // si el dato ya estaba en el árbol
            cout << "el nodo ya se encuentra en el árbol: " << data << endl;
        }

        return node;
    }

    // los nodos se eliminan, porque no siempre se puede tener un árbol lleno.
    Node* eliminarNodo(Node* node, int data) {
        if (node == nullptr) return node; 

        if (data < node->info) {
            node->left = eliminarNodo(node->left, data);  // elimina por la izquierda si es menor
        } else if (data > node->info) {
            node->right = eliminarNodo(node->right, data);  // elimina por la derecha si es mayor
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;  
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;  
                return temp;
            }
            //  si tiene dos hijos hay que buscar al sucesor
            Node* temp = minValueNode(node->right);
            node->info = temp->info;
            node->right = eliminarNodo(node->right, temp->info);
        }

        return node;
    }

    // se busca al nodo más pequeño
    Node* minValueNode(Node* node) {
        Node* current = node;

        // para esto va hasta lo más a la izquierda
        while (current && current->left != nullptr)
            current = current->left;

        return current;
    }

    // el recorrido en preorden
    void printPreOrder(Node* node) {
        if (node == nullptr) return;
        cout << node->info << " ";  // primero se imprime el nodo actual
        printPreOrder(node->left);  // luego el subárbol izquierdo
        printPreOrder(node->right); // y después el derecho
    }

    // el recorrido en inorden
    void printInOrder(Node* node) {
        if (node == nullptr) return;
        printInOrder(node->left);   // primero el subárbol izquierdo
        cout << node->info << " ";  // luego el nodo actual
        printInOrder(node->right);  // después el derecho
    }

    // el recorrido en posorden
    void printPostOrder(Node* node) {
        if (node == nullptr) return;
        printPostOrder(node->left);   // primero el subárbol izquierdo
        printPostOrder(node->right);  // luego el derecho
        cout << node->info << " ";    // al final el nodo actual
    }

public:
    // para insertar desde fuera de la clase llama este método que usa el privado
    void insert(int data) {
        root = insertNode(root, data);
    }

    // para eliminar también use un método público que usa el privado
    void eliminar(int data) {
        root = eliminarNodo(root, data);
    }

    // y lo mismo con modificar aunque lo que hace es eliminar e insertar
    void modificar(int valor, int nuevoValor) {
        eliminar(valor);
        insert(nuevoValor);
    }

    // métodos públicos para recorrer el árbol en varios órdenes
    void printPreOrder() {
        printPreOrder(root);
        cout << endl;
    }

    void printInOrder() {
        printInOrder(root);
        cout << endl;
    }

    void printPostOrder() {
        printPostOrder(root);
        cout << endl;
    }

    // para visualizar el árbol crean un archivo .dot y luego lo convierten a png
    void visualize() {
        ofstream file("arbol.dot");
        file << "digraph G {" << endl;
        file << "node [style=filled, fillcolor=yellow];\n";
        file << "node [shape=circle]" << endl;
        printDot(root, file);
        file << "}" << endl;
        file.close();
        system("dot -Tpng arbol.dot -o arbol.png");  // se crea el archivo png
        system("gwenview arbol.png");  // abren la imagen con gwenview
    }

private:
    // el método para generar el archivo .dot del árbol
    void printDot(Node* node, ofstream& file) {
        if (node == nullptr) return;
        if (node->left != nullptr) {
            file << node->info << " -> " << node->left->info << endl;
            printDot(node->left, file);
        }
        if (node->right != nullptr) {
            file << node->info << " -> " << node->right->info << endl;
            printDot(node->right, file);
        }
    }
};

// en el main se encargan de manejar el menú de opciones
int main() {
    Arbol arbol;
    int opcion, valor, nuevoValor;

    do {
        cout << "\nmenú de opciones:" << endl;
        cout << "1. insertar número" << endl;
        cout << "2. eliminar número" << endl;
        cout << "3. modificar número" << endl;
        cout << "4. mostrar preorden" << endl;
        cout << "5. mostrar inorden" << endl;
        cout << "6. mostrar posorden" << endl;
        cout << "7. generar grafo" << endl;
        cout << "0. salir" << endl;
        cout << "elige una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "ingrese el número a insertar: ";
                cin >> valor;
                arbol.insert(valor);
                break;
            case 2:
                cout << "ingrese el número a eliminar: ";
                cin >> valor;
                arbol.eliminar(valor);
                break;
            case 3:
                cout << "ingrese el número a modificar: ";
                cin >> valor;
                cout << "ingrese el nuevo valor: ";
                cin >> nuevoValor;
                arbol.modificar(valor, nuevoValor);
                break;
            case 4:
                cout << "recorrido preorden: ";
                arbol.printPreOrder();
                break;
            case 5:
                cout << "recorrido inorden: ";
                arbol.printInOrder();
                break;
            case 6:
                cout << "recorrido posorden: ";
                arbol.printPostOrder();
                break;
            case 7:
                arbol.visualize();
                break;
            case 0:
                cout << "saliendo del programa..." << endl;
                break;
            default:
                cout << "opción no válida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
