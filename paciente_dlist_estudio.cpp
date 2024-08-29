#include <iostream>
using namespace std;

struct Paciente {
    string nombre;
    int edad;
    float peso;
    float altura;
    Paciente* siguiente;
};

void encolarPaciente(Paciente*& frente, Paciente*& final, string nombre, int edad, float peso, float altura) {
    Paciente* nuevo = new Paciente{nombre, edad, peso, altura, NULL};
    if (final == NULL) {
        frente = final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }
}

void mostrarPacientesEnCola(Paciente* frente) {
    cout << "Pacientes en cola:" << endl;
    Paciente* temp = frente;
    while (temp != NULL) {
        cout << "Nombre: " << temp->nombre << ", Edad: " << temp->edad << ", Peso: " << temp->peso << " kg, Altura: " << temp->altura << " m" << endl;
        temp = temp->siguiente;
    }
}

// Función para obtener la observación basada en el IMC
string obtenerObservacionIMC(float imc) {
    if (imc < 18.5) {
        return "Bajo peso";
    } else if (imc < 25.0) {
        return "Peso normal";
    } else if (imc < 30.0) {
        return "Sobrepeso";
    } else {
        return "Obesidad";
    }
}

// Función promedio de edad
float calcularPromedioEdad(Paciente* frente) {
    int sumaEdad = 0, contador = 0;
    Paciente* temp = frente;
    while (temp != NULL) {
        sumaEdad += temp->edad;
        contador++;
        temp = temp->siguiente;
    }
    return contador == 0 ? 0 : static_cast<float>(sumaEdad) / contador;
}

// Función promedio de peso
float calcularPromedioPeso(Paciente* frente) {
    float sumaPeso = 0.0;
    int contador = 0;
    Paciente* temp = frente;
    while (temp != NULL) {
        sumaPeso += temp->peso;
        contador++;
        temp = temp->siguiente;
    }
    return contador == 0 ? 0 : sumaPeso / contador;
}

// Función para calcular el IMC 
void desencolarPaciente(Paciente*& frente, Paciente*& final) {
    if (frente == NULL) {
        cout << "La cola está vacía, no hay pacientes para atender." << endl;
        return;
    }

    Paciente* temp = frente;
    float imc = temp->peso / (temp->altura * temp->altura);
    string observacion = obtenerObservacionIMC(imc);
    cout << "Paciente atendido: " << temp->nombre << ", IMC: " << imc << " -" << observacion << "-" << endl;

    frente = frente->siguiente;
    if (frente == NULL) {
        final = NULL;
    }
    delete temp;
}

int main() {
    Paciente* frente = NULL;
    Paciente* final = NULL;

    encolarPaciente(frente, final, "Juan", 24, 74.4, 1.77);
    encolarPaciente(frente, final, "Pedro", 35, 95.2, 1.74);
    encolarPaciente(frente, final, "Maria", 19, 47.0, 1.63);
    encolarPaciente(frente, final, "Laura", 28, 60.5, 1.70);

    mostrarPacientesEnCola(frente);

    cout << "\nPromedio de edad: " << calcularPromedioEdad(frente) << " años" << endl;
    cout << "Promedio de peso: " << calcularPromedioPeso(frente) << " kg" << endl;

    cout << "\nResultados del IMC" << endl;
    while (frente != NULL) {
        desencolarPaciente(frente, final);
    }

    return 0;
}
