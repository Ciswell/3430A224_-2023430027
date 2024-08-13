#include <iostream>
#include <string>

using namespace std;

bool esPar(int numero) {   // con esto podemos ver si el número ingresado es par o no
    return numero % 2 == 0;
}

int longitudString(const string& cadena) {
    return cadena.length();
}

int main() {
    int numeroIngresado;
    cout << "Ingrese un número: ";
    cin >> numeroIngresado;


    if (esPar(numeroIngresado)) {  // verificamos si es par o no 
        cout << "----El número----- " << numeroIngresado << " es par\n"; 
    } else {
        cout << "---El número---- " << numeroIngresado << " es impar\n";
    }

    for (int i = 1; i <= 10; ++i) { // creamos un bucle del 1 al 10, luego i va interar en todos los números verificando si son pares o no 
        if (esPar(i)) {
            cout << "El número " << i << " es par\n";
        } else {
            cout << "El número " << i << " es impar\n";
        }
    }

    string cadenaIngresada;
    cout << "Ingrese un string: ";
    cin.ignore(); 
    getline(cin, cadenaIngresada);

    int longitud =longitudString(cadenaIngresada); // determina la longitud del string 
    cout << "La longitud del string es: " << longitud << " caracteres\n";

    return 0;
}