#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath> 
using namespace std;

// estructura que representa a un paciente, contiene su información básica
struct Paciente {
    string nombre;
    int edad;
    double altura;  // altura en metros
    double peso;    // peso en kilogramos
    double imc;     // índice de masa corporal que calcularemos más adelante
    double a1c;     // promedio de azúcar en sangre, conocido como A1C
};

// función que calcula el índice de prioridad basado en el imc y el a1c del paciente
int CalcularIndicePrioridad(const Paciente& paciente) {
    int riesgoIMC = 0;
    int riesgoA1C = 0;

    // determinamos el nivel de riesgo del imc
    if (paciente.imc >= 18.5 && paciente.imc <= 24.9) {
        riesgoIMC = 1; // rango saludable de IMC
    } else if (paciente.imc >= 25 && paciente.imc <= 29.9) {
        riesgoIMC = 2; // sobrepeso
    } else if (paciente.imc >= 30) {
        riesgoIMC = 3; // obesidad
    }

    // ahora determinamos el nivel de riesgo del a1c
    if (paciente.a1c < 5.7) {
        riesgoA1C = 1; // a1c normal
    } else if (paciente.a1c >= 5.7 && paciente.a1c <= 6.4) {
        riesgoA1C = 2; // prediabetes
    } else if (paciente.a1c >= 6.5) {
        riesgoA1C = 3; // diabetes
    }

    // retornamos la suma de ambos riesgos, cuanto mayor sea la suma, mayor es la prioridad
    return riesgoIMC + riesgoA1C;
}

// estructura de comparación para la cola de prioridad, compara la prioridad de dos pacientes
struct ComparadorPrioridad {
    bool operator()(const Paciente& p1, const Paciente& p2) {
        // los pacientes con mayor índice de prioridad deben ir primero
        return CalcularIndicePrioridad(p1) < CalcularIndicePrioridad(p2);
    }
};

// declaramos una cola de prioridad que almacenará a los pacientes según su prioridad
priority_queue<Paciente, vector<Paciente>, ComparadorPrioridad> colaPacientes;

// función para cargar los datos de los pacientes desde un archivo csv
void CargarPacientesDesdeCSV(const string& archivo) {
    ifstream file(archivo); // abrimos el archivo para lectura
    string linea;

    // verificamos si el archivo no se pudo abrir
    if (!file.is_open()) {
        cout << "error al intentar abrir el archivo.\n";
        return;
    }

    // descartamos la primera línea del archivo, ya que es el encabezado (nombre, edad, altura, etc.)
    getline(file, linea);

    // ahora leemos cada línea (cada paciente) del archivo
    while (getline(file, linea)) {
        stringstream ss(linea);
        Paciente paciente;
        string temp;

        // extraemos y asignamos cada valor del paciente (nombre, edad, altura, peso, a1c)
        getline(ss, paciente.nombre, ','); // leemos el nombre hasta la primera coma
        getline(ss, temp, ','); // leemos la edad como string
        paciente.edad = stoi(temp); // convertimos la edad a entero
        getline(ss, temp, ','); 
        paciente.altura = stod(temp); // convertimos la altura a double
        getline(ss, temp, ',');
        paciente.peso = stod(temp); // convertimos el peso a double
        getline(ss, temp, ',');
        paciente.a1c = stod(temp); // convertimos el a1c a double

        // calculamos el imc usando la fórmula peso / altura^2
        paciente.imc = paciente.peso / pow(paciente.altura, 2);

        // encolamos al paciente en la cola de prioridad
        colaPacientes.push(paciente);
    }

    file.close(); // cerramos el archivo después de haber leído todos los pacientes
    cout << "pacientes cargados desde el archivo csv.\n";
}

// función para desencolar (atender) al paciente con mayor prioridad
void DesencolarPaciente() {
    // si la cola está vacía, no hay pacientes que atender
    if (colaPacientes.empty()) {
        cout << "no hay pacientes en la cola.\n";
        return;
    }

    // obtenemos el paciente con mayor prioridad (el de arriba de la cola)
    Paciente p = colaPacientes.top();
    colaPacientes.pop(); // lo sacamos de la cola (lo atendemos)

    // mostramos la información del paciente atendido
    cout << "atendiendo a: " << p.nombre << ", edad: " << p.edad << ", imc: " << p.imc << ", a1c: " << p.a1c << "\n";
}

// función para mostrar todos los pacientes en la cola (sin alterar la cola original)
void MostrarPacientes() {
    // hacemos una copia de la cola para no modificar la original
    priority_queue<Paciente, vector<Paciente>, ComparadorPrioridad> tempQueue = colaPacientes;

    // recorremos la cola y mostramos la información de cada paciente
    while (!tempQueue.empty()) {
        Paciente p = tempQueue.top(); // obtenemos el paciente con mayor prioridad
        cout << "paciente: " << p.nombre << ", edad: " << p.edad << ", imc: " << p.imc << ", a1c: " << p.a1c << "\n";
        tempQueue.pop(); // lo sacamos de la cola temporal
    }
}

// función que muestra el menú interactivo para que el usuario seleccione una opción
void MostrarMenu() {
    cout << "\n---- menú interactivo ----\n";
    cout << "1. cargar pacientes desde csv\n";
    cout << "2. mostrar pacientes\n";
    cout << "3. atender paciente (desencolar)\n";
    cout << "4. salir\n";
    cout << "elige una opción: ";
}

int main() {
    int opcion; // variable para guardar la opción seleccionada por el usuario
    string archivoCSV = "/home/usuario/Descargas/patient_list.csv"; // ruta del archivo csv en descargas

    do {
        MostrarMenu(); // mostramos el menú de opciones
        cin >> opcion; // leemos la opción que el usuario selecciona

        // según la opción, llamamos a la función correspondiente
        switch(opcion) {
            case 1:
                // cargamos los pacientes desde el archivo csv
                CargarPacientesDesdeCSV(archivoCSV);
                break;
            case 2:
                // mostramos la lista de pacientes en la cola
                MostrarPacientes();
                break;
            case 3:
                // atendemos al paciente con mayor prioridad
                DesencolarPaciente();
                break;
            case 4:
                // mensaje de despedida cuando el usuario elige salir
                cout << "saliendo del programa.\n";
                break;
            default:
                // si el usuario ingresa una opción inválida, le mostramos un mensaje de error
                cout << "opción inválida, por favor intenta nuevamente.\n";
                break;
        }
    } while(opcion != 4); // seguimos mostrando el menú hasta que el usuario elija salir

    return 0; // finalizamos el programa
}
