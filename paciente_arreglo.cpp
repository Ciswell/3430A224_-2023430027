#include <iostream>
using namespace std;

struct Paciente {
    string nombre;
    int edad;
    float peso;
    float altura;
};

int main() {
    // este es el arreglo del codigo y donde se "almacena" la información del paciente
    Paciente pacientes[3];
    
    
    pacientes[0].nombre = "Juan";
    pacientes[0].edad = 24;
    pacientes[0].peso = 74.4;
    pacientes[0].altura = 1.77;
    
    pacientes[1].nombre = "Pedro";
    pacientes[1].edad = 35;
    pacientes[1].peso = 95.2;
    pacientes[1].altura = 1.74;
    
    pacientes[2].nombre = "Maria";
    pacientes[2].edad = 19;
    pacientes[2].peso = 47.0;
    pacientes[2].altura = 1.63;
    
    // bucle for que recorre el arreglo de pacientes y por cada iteración, se accede a los datos del pacientes y se imprimen.
    for (int i = 0; i < 3; i++) {
        cout << "nombre: " << pacientes[i].nombre << endl;
        cout << "edad: " << pacientes[i].edad << " años" << endl;
        cout << "peso: " << pacientes[i].peso << " Kg" << endl;
        cout << "altura: " << pacientes[i].altura << " metros" << endl;
        cout << "\n"; 
    }
    
    return 0;
}
