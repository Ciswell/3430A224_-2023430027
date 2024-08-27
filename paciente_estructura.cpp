#include <iostream>

using namespace std;

struct Paciente
{  string nombre;
   int edad;
   float peso;
   float altura;
    
};


int main(){
    Paciente paciente1;
        paciente1.nombre = "Juan";
        paciente1.edad = 24;  
        paciente1.peso = 74.4 ;
        paciente1.altura = 1.77; 

    Paciente paciente2;
        paciente2.nombre = "Pedro";
        paciente2.edad = 35;  
        paciente2.peso = 95,2;
        paciente2.altura = 1.74; 

    Paciente paciente3;
        paciente3.nombre = "Maria";
        paciente3.edad = 19;  
        paciente3.peso = 47;
        paciente3.altura = 1.63; 
        
        
    cout << "nombre: " << paciente1.nombre <<
     endl;
    cout << "edad: " << paciente1.edad << " años" <<
     endl;
    cout << "peso: " << paciente1.peso << " Kg" <<
    endl;
    cout << "altura: " << paciente1.altura <<  " metros" <<
    endl;
    
    cout << "\n";

    cout << "nombre: " << paciente2.nombre <<
     endl;
    cout << "edad: " << paciente2.edad << " años" <<
     endl;
    cout << "peso: " << paciente2.peso << " Kg" <<
    endl;
    cout << "altura: " << paciente2.altura <<  " metros" <<
    endl;

        cout << "\n";

    cout << "nombre: " << paciente3.nombre <<
     endl;
    cout << "edad: " << paciente3.edad << " años" <<
     endl;
    cout << "peso: " << paciente3.peso << " Kg" <<
    endl;
    cout << "altura: " << paciente3.altura <<  " metros" <<
    endl;

    return 0;
};
