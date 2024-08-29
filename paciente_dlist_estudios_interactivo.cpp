#include <iostream>
#include <fstream>  // para manejar archivos
#include <string>
using namespace std;

struct Paciente {
    string nombre;
    int edad;
    float peso;
    float altura;
    Paciente* siguiente;  // puntero al siguiente paciente en la lista
};

// función para agregar un paciente al final de la lista
void encolarPaciente(Paciente*& frente, Paciente*& final, string nombre, int edad, float peso, float altura) {
    Paciente* nuevo = new Paciente{nombre, edad, peso, altura, NULL};
    if (final == NULL) {
        frente = final = nuevo;  // si la lista está vacía, este es el primer paciente
    } else {
        final->siguiente = nuevo;  // si no, lo añadimos al final
        final = nuevo;
    }
}

// función para mostrar todos los pacientes en la lista
void mostrarPacientesEnCola(Paciente* frente) {
    Paciente* temp = frente;
    if (temp == NULL) {
        cout << "no hay pacientes en la cola." << endl;
        return;
    }
    while (temp != NULL) {
        cout << "nombre: " << temp->nombre << ", edad: " << temp->edad << ", peso: " << temp->peso << " kg, altura: " << temp->altura << " m" << endl;
        temp = temp->siguiente;
    }
}

// función que evalúa el imc y devuelve una observación sobre el peso del paciente
string obtenerObservacionIMC(float imc) {
    if (imc < 18.5) {
        return "bajo peso";
    } else if (imc < 25.0) {
        return "peso normal";
    } else if (imc < 30.0) {
        return "sobrepeso";
    } else {
        return "obesidad";
    }
}

// función para calcular y mostrar el imc de cada paciente
void mostrarIMCDePacientes(Paciente* frente) {
    Paciente* temp = frente;
    if (temp == NULL) {
        cout << "no hay pacientes en la cola." << endl;
        return;
    }
    while (temp != NULL) {
        float imc = temp->peso / (temp->altura * temp->altura);  // calcula el imc
        string observacion = obtenerObservacionIMC(imc);  // obtiene la observación basada en el imc
        cout << "paciente: " << temp->nombre << ", imc: " << imc << " (" << observacion << ")" << endl;
        temp = temp->siguiente;
    }
}

// función para calcular el promedio de edad de todos los pacientes en la lista
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

// función para calcular el promedio de peso de todos los pacientes en la lista
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

// función para agregar algunos pacientes predefinidos a la lista
void agregarPacientesPredefinidos(Paciente*& frente, Paciente*& final) {
    // estos son los pacientes que estaban en paciente_dlist_estudio.cpp
    encolarPaciente(frente, final, "juan", 24, 74.4, 1.77);
    encolarPaciente(frente, final, "pedro", 35, 95.2, 1.74);
    encolarPaciente(frente, final, "maria", 19, 47.0, 1.63);
    encolarPaciente(frente, final, "laura", 28, 60.5, 1.70);
}

// función para cargar pacientes desde un archivo txt
void cargarDesdeArchivo(Paciente*& frente, Paciente*& final, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);  // abre el archivo
    if (!archivo) {
        cout << "no se pudo abrir el archivo." << endl;
        return;
    }

    string nombre;
    int edad;
    float peso, altura;

    // lee los datos del archivo y agrega cada paciente a la lista
    while (archivo >> nombre >> edad >> peso >> altura) {
        encolarPaciente(frente, final, nombre, edad, peso, altura);
    }

    archivo.close();
    cout << "datos cargados desde " << nombreArchivo << " correctamente." << endl;
}

// función que muestra el menú de opciones y ejecuta lo que el usuario elija
void mostrarMenu(Paciente*& frente, Paciente*& final) {
    int opcion;
    do {
        cout << "\nmenu de opciones:\n";
        cout << "1. mostrar pacientes en cola\n";
        cout << "2. calcular y mostrar imc de cada paciente\n";
        cout << "3. mostrar promedio de edad y peso\n";
        cout << "4. cargar datos desde archivo txt\n";  // opción para cargar datos desde un archivo
        cout << "5. salir\n";
        cout << "seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarPacientesEnCola(frente);
                break;
            case 2:
                mostrarIMCDePacientes(frente);
                break;
            case 3:
                if (frente != NULL) {
                    cout << "\npromedio de edad: " << calcularPromedioEdad(frente) << " años" << endl;
                    cout << "promedio de peso: " << calcularPromedioPeso(frente) << " kg" << endl;
                } else {
                    cout << "no hay pacientes en la cola para calcular promedios." << endl;
                }
                break;
            case 4:
                {
                    string nombreArchivo;
                    cout << "ingrese el nombre del archivo txt: ";
                    cin >> nombreArchivo;
                    cargarDesdeArchivo(frente, final, nombreArchivo);  // carga pacientes desde el archivo
                }
                break;
            case 5:
                cout << "saliendo del programa..." << endl;
                break;
            default:
                cout << "opción no válida. intente nuevamente." << endl;
        }
    } while (opcion != 5);
}

int main() {
    Paciente* frente = NULL;
    Paciente* final = NULL;

    // agregamos pacientes predefinidos al inicio
    agregarPacientesPredefinidos(frente, final);

    mostrarMenu(frente, final);  // muestra el menú al usuario

    return 0;
}
