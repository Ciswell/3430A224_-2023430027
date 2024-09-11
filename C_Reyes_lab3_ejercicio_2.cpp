#include <iostream>
#include <string>
#include <vector>
using namespace std;

// clase contenedor donde cada contenedor tiene un id y una empresa
class Contenedor {
public:
    int id;  // bueno, este es el número identificador del contenedor
    string empresa; 

    // constructor para crear un contenedor con id y empresa
    Contenedor(int id, string empresa) {
        this->id = id;  
        this->empresa = empresa; 
    }
};

// clase área de contenedores que es básicamente una colección de pilas
class AreaContenedores {
private:
    vector<vector<Contenedor>> areas;  // aquí tenemos un vector de vectores para las áreas
    int n, m;  // n es la altura máxima y m el número de áreas disponibles

public:
    // constructor que recibe la altura máxima y el número de áreas
    AreaContenedores(int n, int m) {
        this->n = n;  
        this->m = m;  
        areas.resize(m);  
    }

    // método para agregar un contenedor en el primer área disponible
    void agregarContenedor(int id, string empresa) {
        for (int i = 0; i < m; i++) {
            if (areas[i].size() < n) {  
                areas[i].push_back(Contenedor(id, empresa));  
                cout << "contenedor " << id << " agregado al área " << i + 1 << "." << endl;
                return;  
            }
        }
        cout << "todas las áreas están llenas. no se puede agregar el contenedor." << endl;
    }

    // método para retirar un contenedor específico
    void retirarContenedor(int id) {
        for (int i = 0; i < m; i++) {  
            int j = areas[i].size() - 1;  // empezamos desde el tope de cada área
            vector<Contenedor> temporal;  // donde guardaremos temporalmente los contenedores movidos

            // buscamos el contenedor en el área "i"
            while (j >= 0) {
                if (areas[i][j].id == id) {  // si encontramos el contenedor
                    // movemos los contenedores que están encima a la lista temporal
                    while (areas[i].back().id != id) {
                        temporal.push_back(areas[i].back());  // sacamos el contenedor del área
                        cout << "moviendo temporalmente el contenedor " << areas[i].back().id
                             << " del área " << i + 1 << "." << endl;
                        areas[i].pop_back();  // lo sacamos del área para moverlo después
                    }
                    // retiramos el contenedor que queríamos
                    cout << "retirando el contenedor " << areas[i].back().id << " del área " << i + 1 << "." << endl;
                    areas[i].pop_back(); 

                    // ahora devolvemos los contenedores temporales a otra área
                    while (!temporal.empty()) {
                        // buscamos un área que tenga espacio
                        for (int k = 0; k < m; k++) {
                            if (areas[k].size() < n) {  // encontramos un área con espacio
                                areas[k].push_back(temporal.back());  // devolvemos el contenedor
                                cout << "id: " << temporal.back().id << " : moviendo el contenedor " 
                                     << temporal.back().id << " al área " << k + 1 << "." << endl;
                                temporal.pop_back();  // lo sacamos de la lista temporal
                                break;  // y seguimos con el siguiente
                            }
                        }
                    }
                    return; 
                }
                j--;  // seguimos buscando en la misma área
            }
        }
        cout << "el contenedor " << id << " no fue encontrado en ninguna área." << endl;
    }

    // método para mostrar el estado actual de las áreas
    void mostrarAreas() {
        for (int i = 0; i < m; i++) {  // iteramos sobre cada área
            cout << "área " << i + 1 << ": ";
            if (areas[i].empty()) {  
                cout << "vacía" << endl;
            } else {
                for (int j = 0; j < areas[i].size(); j++) {
                    cout << "[" << areas[i][j].id << " - " << areas[i][j].empresa << "] ";  // mostramos cada contenedor
                }
                cout << endl;
            }
        }
    }
};

int main() {
    int n, m;  
    cout << "ingrese el número máximo de contenedores por área: ";
    cin >> n;  
    cout << "ingrese el número de áreas disponibles: ";
    cin >> m;  

    AreaContenedores puerto(n, m);  // creamos el puerto con n contenedores por área y m áreas

    int opcion;  
    do {
        cout << "\nmenú de opciones:" << endl;
        cout << "1. agregar contenedor" << endl;
        cout << "2. retirar contenedor" << endl;
        cout << "3. mostrar estado de las áreas" << endl;
        cout << "0. salir" << endl;
        cout << "elige una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int id;
                string empresa;
                cout << "ingrese el id del contenedor: ";  
                cin >> id;
                cout << "ingrese el nombre de la empresa: ";  
                cin >> empresa;
                puerto.agregarContenedor(id, empresa);  
                break;
            }
            case 2: {
                int id;
                cout << "ingrese el id del contenedor a retirar: ";  
                cin >> id;
                puerto.retirarContenedor(id); 
                break;
            }
            case 3:
                puerto.mostrarAreas();  
                break;
            case 0:
                cout << "saliendo del programa..." << endl; 
                break;
            default:
                cout << "opción no válida." << endl;  
        }
    } while (opcion != 0);  // el ciclo se repite mientras la opción no sea salir (0)

    return 0; 
}
