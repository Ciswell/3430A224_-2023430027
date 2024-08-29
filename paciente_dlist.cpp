#include <iostream> 
using namespace std;

struct Paciente {
    string nombre;  
    int edad;      
    float peso;    
    float altura;  
    Paciente* siguiente;  // Puntero al siguiente paciente en la cola
};

// Esta función añade un paciente a la cola, actualiza el frente y final 
void encolarPaciente(Paciente*& frente, Paciente*& final, string nombre, int edad, float peso, float altura) {
    Paciente* nuevo = new Paciente{nombre, edad, peso, altura, NULL}; // Nuevo paciente
    if (final == NULL) {  
        frente = final = nuevo;  // Los punteros apuntan al nuevo paciente
    } else {
        final->siguiente = nuevo;  // El último paciente actual apunta al nuevo paciente
        final = nuevo;  // Final se actualiza para apuntar al siguiente paciente en la cola
    }
}

// Recorre la cola desde frente hasta el final 
void imprimirPacientes(Paciente* frente) {
    Paciente* temp = frente;  // Un puntero temporal para recorrer la cola
    while (temp != NULL) {  // Hasta que no haya más pacientes en la cola continúa 
        cout << "Nombre: " << temp->nombre << endl;
        cout << "Edad: " << temp->edad << " años" << endl;
        cout << "Peso: " << temp->peso << " Kg" << endl;
        cout << "Altura: " << temp->altura << " metros" << endl;
        cout << "\n";
        temp = temp->siguiente;  // Siguiente paciente 
    }
}

// Esta función elimina el paciente que está al frente de la cola y los punteros se actualizan
void desencolarPaciente(Paciente*& frente, Paciente*& final) {
    if (frente == NULL) {  
        cout << "La cola está vacía, no hay pacientes para atender." << endl;
        return;
    }
    Paciente* temp = frente;  // Guarda el primer paciente para eliminarlo
    frente = frente->siguiente;  // Siguiente paciente
    if (frente == NULL) {  
        final = NULL;  
    }
    delete temp;  // Elimina el paciente que fue atendido
}

int main() {
    Paciente* frente = NULL;  // Puntero al frente de la cola
    Paciente* final = NULL;   // puntero al final de la cola 

    // Encolamos los pacientes
    encolarPaciente(frente, final, "Juan", 24, 74.4, 1.77);
    encolarPaciente(frente, final, "Pedro", 35, 95.2, 1.74);
    encolarPaciente(frente, final, "Maria", 19, 47.0, 1.63);
    encolarPaciente(frente, final, "Laura", 28, 60.5, 1.70);

    cout << "Cola de pacientes:" << endl;
    imprimirPacientes(frente);

    // Desencolamos
    for (int i = 0; i < 3; i++) {
        desencolarPaciente(frente, final);
    }

    cout << "\nPacientes atendidos." << endl;

    cout << "\nCola de pacientes después de atender a tres:" << endl;
    imprimirPacientes(frente);

    return 0;
}
